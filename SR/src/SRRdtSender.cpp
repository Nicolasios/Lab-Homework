#include "Global.h"
#include "SRRdtSender.h"
#include "DataStructure.h"
SRRdtSender::SRRdtSender() : base(1),
                             expectSequenceNumberSend(1),
                             N(Configuration::CHACE_SIZE),
                             waitingState(false),
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
SRRdtSender::~SRRdtSender()
{
}

bool SRRdtSender::getWaitingState()
{
    if (expectSequenceNumberSend < base + slideSize)
    {
        this->waitingState = false;
    }
    else
    {
        this->waitingState = true;
    }
    return this->waitingState;
}

bool SRRdtSender::send(const Message &message)
{
    getWaitingState();
    printf("发送方发送函数调用\n");
    //处于等待状态则不执行操作
    if (this->waitingState == true)
    {
        return false;
    }
    //创建一个新的以待通过message输入信息
    //设置pkt的基础信息
    Packet pkt;
    //初值化都是-1，知道receiver发送回来修改
    pkt.acknum = -1;
    pkt.seqnum = this->expectSequenceNumberSend;
    memcpy(pkt.payload, message.data, sizeof(message.data));
    pkt.checksum = pUtils->calculateCheckSum(pkt);

    //设置标记
    this->flags[expectSequenceNumberSend] = Configuration::SENT_NOT_ACK;
    //设置好待发送的包之后缓存入发送窗口
    this->slideWindow[expectSequenceNumberSend] = pkt;
    pUtils->printPacket("发送方发送报文", pkt);

    printf("---------Sender  Window After Send-------------\n");
    slideWindow.ShowWindow(base);
    //为每个分组都开启计时器
    pns->startTimer(SENDER, Configuration::TIME_OUT, expectSequenceNumberSend);
    pns->sendToNetworkLayer(RECEIVER, pkt);
    expectSequenceNumberSend++;
    return true;
}

void SRRdtSender::receive(const Packet &ackPkt)
{ //发送方接受接收方返回的响应
    //计算检查和
    printf("发送方接收函数调用\n");
    int checksum = pUtils->calculateCheckSum(ackPkt);
    int rtn = 0;

    int acknum = ackPkt.acknum;
    //接收到的是base的ack响应
    for (int i = base; i < expectSequenceNumberSend; i++)
    {
        if (acknum == slideWindow[i].seqnum)
        {
            rtn = 1;
        }
    }
    if (checksum != ackPkt.checksum)
    {
        printf("检查和不正确\n");
    }
    if (checksum == ackPkt.checksum && rtn)
    { //base向前移动 直到遇到第一个SENT_NOT_ACK或者到达末尾
        pns->stopTimer(SENDER, acknum);
        this->flags[acknum] = Configuration::SENT_AND_ACK;
        for (; base < expectSequenceNumberSend; base++)
        {
            if (this->flags[base] == Configuration::SENT_NOT_ACK)
            {
                break;
            }
        }
        printf("---------Sender  Window After Receive-------------\n");
        slideWindow.ShowWindow(base);
    }
}

void SRRdtSender::timeoutHandler(int seqNum)
{
    printf("超时函数调用\n");
    //谁超时就重传谁
    pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
    printf("重新发送的序号:%d\n", seqNum);
    pns->sendToNetworkLayer(RECEIVER, this->slideWindow[seqNum]);
}
