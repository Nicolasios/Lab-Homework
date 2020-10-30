#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

struct Configuration
{

	/**
	定义各层协议Payload数据的大小（字节为单位）
	*/
	static const int PAYLOAD_SIZE = 21;
	/**
	定义滑动窗口大小
	*/
	static const int SLIDEWINDOW_SIZE = 4;
	/**
	定义缓冲窗口大小
	*/
	static const int CHACE_SIZE = 200;
	/**
	定时器时间
	*/
	static const int TIME_OUT = 30;
	/**
	发送但是没有被确认
	*/
	static const int SENT_NOT_ACK = 1;
	/**
	发送已经确认
	 */
	static const int SENT_AND_ACK = 2;
};

/**
	第五层应用层的消息
*/
struct Message
{
	char data[Configuration::PAYLOAD_SIZE]; //payload

	Message();
	Message(const Message &msg);
	virtual Message &operator=(const Message &msg);
	virtual ~Message();

	virtual void print();
};

/**
	第四层运输层报文段
*/
struct Packet
{
	int seqnum;								   //序号
	int acknum;								   //确认号
	int checksum;							   //校验和
	char payload[Configuration::PAYLOAD_SIZE]; //payload

	Packet();
	Packet(const Packet &pkt);
	virtual Packet &operator=(const Packet &pkt);
	virtual bool operator==(const Packet &pkt) const;
	virtual ~Packet();

	virtual void print();
};

#endif
