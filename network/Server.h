#pragma once
#include <winsock2.h>
#include <list>
#include <string>

using namespace std;
//��������

class Server {
private:
	SOCKET srvSocket;		//������socket
	char* recvBuf;			//���ջ�����
	char* recvType;         //���������ļ�����
	sockaddr_in srvAddr;	//��������ip��ַ

protected:
	virtual void recvMessage(SOCKET socket);
	virtual void sendMessage(SOCKET socket);
	virtual SOCKET ConnectStartup();
	virtual int getType(string fileName);
public:
	Server();

	virtual ~Server();

	//��ʼ��Winsock
	virtual int WinsockStartup();  

	//��ʼ��Server����������SOCKET���󶨵�IP��PORT
	virtual int ServerStartup();  

	//��ʼ�����ͻ�������
	virtual int ListenStartup();



	//ѭ���ȴ�
	virtual int Loop();
};