#ifndef STOP_WAIT_RDT_SENDER_H
#define STOP_WAIT_RDT_SENDER_H
#include "RdtSender.h"
#include "SlideWindow.h"
#include "DataStructure.h"

class TCPRdtSen : public RdtSender
{
private:
    //窗口基序号
    int base;
    //缓冲区大小
    int N;
    //滑动窗口
    SlideWindow slideWindow;
    //是否处于等待状态
    bool waitingState;
    //下一个发送的序号
    int expectSequenceNumberSend;
    //滑动窗口大小
    int slideSize;
    //记录冗余ACK
    int tripleACK;

public:
    TCPRdtSen();
    virtual ~TCPRdtSen();

public:
    /**
	* called by application layer
	* send one Message from application layer
	* 
	* @param message a Message from application layer
	* 
	* @returns if send success, return true. return false
	*/
    bool send(const Message &message);
    /**
	* to judge the RdtSender whether in the waitingstate
	* 
	* @returns if still on waitingstste , return true. or return false
	*/
    bool getWaitingState();
    /**
	* called by application layer
	* receive one message from  application layer
	* which is sent by the RdtReceiver to response the RdtSendrt
	* @param ackPkt  a packet with a acknum
	* 
	*/
    void receive(const Packet &ackPkt);
    /**
	*set a tiemcount for the packet to judge the packet is timeout or not 
    *
	* @param seqNum  the sequence of the packet 
	* 
	*/
    void timeoutHandler(int seqNum);
};

#endif