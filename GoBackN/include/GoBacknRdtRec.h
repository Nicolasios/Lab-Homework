#ifndef STOP_WAIT_RDT_RECEIVER_H
#define STOP_WAIT_RDT_RECEIVER_H
#include "RdtReceiver.h"
#include "DataStructure.h"
#define GBNWindowSize 5
#define MAX 16
class GoBacknRdtRec : public RdtReceiver
{
private:
    int expectSequenceNumberRcvd; //期待到手的下一个报文序号
    Packet lastAckPkt;            //上次发送的确认报文
public:
    GoBacknRdtRec();
    virtual ~GoBacknRdtRec();

public:
    void receive(const Packet &Packet); //接受报文，将被NetWorkService调用
};

#endif