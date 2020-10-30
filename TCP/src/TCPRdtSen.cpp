#include "Global.h"
#include "TCPRdtSen.h"
#include "DataStructure.h"
TCPRdtSen::TCPRdtSen() : base(1),
                         expectSequenceNumberSend(1),
                         N(Configuration::CHACE_SIZE),
                         waitingState(false),
                         slideWindow(Configuration::SLIDEWINDOW_SIZE),
                         slideSize(Configuration::SLIDEWINDOW_SIZE),
                         tripleACK(1)
{
}
TCPRdtSen::~TCPRdtSen()
{
}

bool TCPRdtSen::getWaitingState()
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

bool TCPRdtSen::send(const Message &message)
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

    //设置好待发送的包之后缓存入发送窗口
    this->slideWindow[expectSequenceNumberSend] = pkt;
    printf("--------发送方滑动窗口 发送正确之后-------------------------------\n");
    slideWindow.ShowWindow(base);
    printf("---------------------------------------------------------------------\n");
    pUtils->printPacket("发送方发送报文", pkt);

    //如果该发送的分组为滑动窗口的base分组那么启动计时器
    //只在开始的时候设置计时器
    if (base == expectSequenceNumberSend)
    {
        pns->startTimer(SENDER, Configuration::TIME_OUT, base);
    }
    pns->sendToNetworkLayer(RECEIVER, pkt);
    expectSequenceNumberSend++;
    return true;
}

void TCPRdtSen::receive(const Packet &ackPkt)
{ //发送方接受接收方返回的响应
    //计算检查和
    printf("发送方接收函数调用\n");
    int checksum = pUtils->calculateCheckSum(ackPkt);
    int rtn;
    int acknum = ackPkt.acknum;

    for (int i = base; i < expectSequenceNumberSend; i++)
    {
        if (acknum == slideWindow[i].seqnum)
        {
            rtn = 1;
        }
    }
    //接收到的是base的ack响应
    if (checksum != ackPkt.checksum)
    {
        printf("检查和不正确\n");
    }
    //如果接到的ack是下一个待接收的ack
    if (checksum == ackPkt.checksum && base + 1 == acknum)
    {
        printf("ack = base+1\n");
        pns->stopTimer(SENDER, base);
        base = acknum;
        printf("--------发送方滑动窗口 接收到正确之后-------------------------------\n");
        slideWindow.ShowWindow(base);
        printf("---------------------------------------------------------------------\n");
        //如果base已经移到了expectnum那么说明base等等已经可以休息了
        if (base == expectSequenceNumberSend)
        {
            pns->stopTimer(SENDER, base);
        }
        else
        {
            pns->startTimer(SENDER, Configuration::TIME_OUT, base);
        }
    }
    if (checksum == ackPkt.checksum && acknum == base)
    {
        printf("ack = base\n");
        tripleACK++;
        if (tripleACK == 4)
        {
            printf("快速重传函数调用\n");
            //只有base会有计时器所以当超时的就是base超时
            pns->stopTimer(SENDER, base);
            pns->startTimer(SENDER, Configuration::TIME_OUT, base);
            for (int i = base; i < expectSequenceNumberSend; i++)
            {
                pns->sendToNetworkLayer(RECEIVER, this->slideWindow[i]);
                printf("第%d个包", i);
                pUtils->printPacket("", this->slideWindow[i]);
                printf("\n");
            }
            tripleACK = 1;
        }
    }
    if (checksum == ackPkt.checksum && rtn && expectSequenceNumberSend == acknum)
    {
        pns->stopTimer(SENDER, base);
        base = acknum;
        base = expectSequenceNumberSend;
        printf("--------发送方滑动窗口 接收到正确之后-------------------------------\n");
        slideWindow.ShowWindow(base);
        printf("---------------------------------------------------------------------\n");
    }
}
void TCPRdtSen::timeoutHandler(int seqNum)
{
    printf("超时函数调用\n");
    //只有base会有计时器所以当超时的就是base超时
    pns->startTimer(SENDER, Configuration::TIME_OUT, base);
    for (int i = base; i < expectSequenceNumberSend; i++)
    {
        pns->sendToNetworkLayer(RECEIVER, this->slideWindow[i]);
        printf("第%d个包", i);
        pUtils->printPacket("", this->slideWindow[i]);
        printf("\n");
    }
}
