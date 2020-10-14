#pragma once
#include <winsock2.h>
#include <list>
#include <string>

using namespace std;
//服务器类

class Server {
private:
	SOCKET srvSocket;		//服务器socket
	char* recvBuf;			//接收缓冲区
	char* recvType;         //接收请求文件类型
	sockaddr_in srvAddr;	//服务器端ip地址

protected:
	virtual void recvMessage(SOCKET socket);
	virtual void sendMessage(SOCKET socket);
	virtual SOCKET ConnectStartup();
	virtual int getType(string fileName);
public:
	Server();

	virtual ~Server();

	//初始化Winsock
	virtual int WinsockStartup();  

	//初始化Server，包括创建SOCKET，绑定到IP和PORT
	virtual int ServerStartup();  

	//开始监听客户端请求
	virtual int ListenStartup();



	//循环等待
	virtual int Loop();
};