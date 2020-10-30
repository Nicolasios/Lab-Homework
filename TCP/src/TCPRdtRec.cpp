#include "Global.h"
#include "TCPRdtRec.h"
#include "DataStructure.h"
TCPRdtRec::TCPRdtRec() : expectSequenceNumberRcvd(1)
{ //初始状态下,上次发送的确认序号为-1，使得当第一个接受的数据包出错时
    //该确认把报文的确认号为-1
    lastAckPkt.acknum = -1;
    lastAckPkt.checksum = 0;
    lastAckPkt.seqnum = -1;
    for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++)
    {
        lastAckPkt.payload[i] = '.';
    }
    lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}

TCPRdtRec::~TCPRdtRec()
{
}

void TCPRdtRec::receive(const Packet &packet)
{
    //首先检查校验和是否正确
    int checknum = pUtils->calculateCheckSum(packet);

    if (checknum == packet.checksum && this->expectSequenceNumberRcvd == packet.seqnum)
    {
        pUtils->printPacket("接收方正确收到发送方的报文", packet);
        //在tcp数据包中解析出数据包传递给上层应用
        Message msg;
        memcpy(msg.data, packet.payload, sizeof(packet.payload));
        pns->delivertoAppLayer(RECEIVER, msg);

        //发送相应报文部分，发送确认号，发送检查和
        //发送的确认报文是接收到的下一个
        lastAckPkt.acknum = packet.seqnum + 1; //确认号等于收到的报文号
        lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
        pUtils->printPacket("接收方发送正确报文", lastAckPkt);
        pns->sendToNetworkLayer(SENDER, lastAckPkt);

        this->expectSequenceNumberRcvd = this->expectSequenceNumberRcvd + 1;
    }
    else
    {
        if (checknum != packet.checksum)
        { //校验和不正确，重新发送上次的确认报文
            pUtils->printPacket("接收方没有正确的收到发送方的报文,数据校验错误", packet);
        }
        else
        { //报文序号不正确，重新发送上次的
            pUtils->printPacket("接收方没有正确收到发送方的报文,报文序号不对", packet);
        }
        pUtils->printPacket("接收方重新发送上次的确认报文", lastAckPkt);
        //调用模拟网络环境，通过网络层重新发送上次确认的报文
        pns->sendToNetworkLayer(SENDER, lastAckPkt);
    }
}