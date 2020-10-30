#ifndef STOP_WAIT_RDT_RECEIVER_H
#define STOP_WAIT_RDT_RECEIVER_H
#include "RdtReceiver.h"
#include "DataStructure.h"
#include "SlideWindow.h"
#define GBNWindowSize 5
#define MAX 16
class SRRdtReceiver : public RdtReceiver
{
private:
    //窗口基序号
    int base;
    //缓冲区大小
    int N;
    //接收方最大序号的分组
    int maxSequence;
    //滑动窗口
    SlideWindow slideWindow;
    //滑动窗口大小
    int slideSize;
    //标记该分组是否接收，初值都为0
    vector<int> flags;

public:
    SRRdtReceiver();
    virtual ~SRRdtReceiver();

public:
    void receive(const Packet &Packet); //接受报文，将被NetWorkService调用
};

#endif