#include "Global.h"
#include "SRRdtReceiver.h"
#include "DataStructure.h"
SRRdtReceiver::SRRdtReceiver() : base(1),
                                 maxSequence(1),
                                 N(Configuration::CHACE_SIZE),
                                 slideWindow(Configuration::SLIDEWINDOW_SIZE),
                                 slideSize(Configuration::SLIDEWINDOW_SIZE)
{
    flags = vector<int>(Configuration::CHACE_SIZE);
    //初始化数组标记
    for (int i = 0; i < Configuration::CHACE_SIZE; i++)
    {
        flags[i] = 0;
    }
}

SRRdtReceiver::~SRRdtReceiver()
{
}

//sr接收方不管是丢包还是出错都不执行操作
void SRRdtReceiver::receive(const Packet &packet)
{
    //检查校验和是否正确
    int checknum = pUtils->calculateCheckSum(packet);
    if (checknum == packet.checksum)
    {
        pUtils->printPacket("接收方正确接收到发送方的报文", packet);
        //基于标记设置接收方滑动窗口标记
        //0表示未接收 1表示接受
        this->slideWindow[packet.seqnum] = packet;
        this->flags[packet.seqnum] = 1;
        printf("---------------------Receiver Window  Before Receive ACk-----------------\n");
        slideWindow.ShowWindow(base);
        if (packet.seqnum > maxSequence)
        {
            maxSequence = packet.seqnum;
            printf("此时最大序号为%d\n", maxSequence);
        }
        for (; base <= maxSequence; base++)
        {
            if (this->flags[base] == 0)
            {
                break;
            }
            else
            { //在按顺序接收后上交
                // Message msg;
                // memcpy(msg.data, packet.payload, sizeof(packet.payload));
                // pns->delivertoAppLayer(RECEIVER, msg);
                printf("按照顺序向上递交报文序号:%d\n", base);
                Message msg;
                memcpy(msg.data, this->slideWindow[base].payload, sizeof(slideWindow[base].payload));
                pns->delivertoAppLayer(RECEIVER, msg);
            }
        }
        printf("---------------------Receiver Window  After Receive ACK---------------\n");
        slideWindow.ShowWindow(base);
        //发送相应的报文，发送确认好，发送检查和
        Packet ackpacket;
        ackpacket.acknum = packet.seqnum;
        ackpacket.seqnum = -1;
        ackpacket.checksum = pUtils->calculateCheckSum(ackpacket);
        pUtils->printPacket("接收方发送正确报文", ackpacket);
        pns->sendToNetworkLayer(SENDER, ackpacket);
    }
}