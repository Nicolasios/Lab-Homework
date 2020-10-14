#pragma once
#include "Config.h"
#include <iostream>
#include <string>
#include "Server.h"
#include "Config.h"
#include <winsock2.h>
#include<WS2tcpip.h>
#include <algorithm>
#include<fstream>
#pragma comment(lib, "Ws2_32.lib")

#pragma warning(disable:4996)

using namespace std;
const string HTML("html");
const string AUDIO("au");
const string JPG("jpg");
char HugeBuffer[1000000000];

Server::Server(void)
{
	this->recvBuf = new char[Config::BUFFERLENGTH]; //��ʼ�����ܻ�����
	this->recvType = new char[Config::FILETYPELENGTH]; //��ʼ���ļ����滺����
	memset(this->recvBuf, '\0', Config::BUFFERLENGTH);
	memset(this->recvType, '\0', Config::FILETYPELENGTH);
}

int Server::WinsockStartup() {
	WSADATA wsaData;
	WORD socketVersion = MAKEWORD(2, 0);
	int rtn = WSAStartup(socketVersion, &wsaData);
	if (rtn != 0) {
		cout << "Init WSA failed" << endl;
		WSACleanup();
		return -1;
	}
	cout << "Init WSA success!" << endl;
	return 0;
}

int Server::ServerStartup() {
	this->srvSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->srvSocket == INVALID_SOCKET) {
		cout << "Server socket create error!" << endl;
		WSACleanup();
		return -1;
	}
	cout << "Server socket create success!" << endl;

	//���ö˿ںź�IP
	this->srvAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	this->srvAddr.sin_port = htons(Config::PORT);
	this->srvAddr.sin_family = AF_INET;
	//��socket�ͷ�������IP�Ͷ˿�
	int rtn = bind(this->srvSocket, (LPSOCKADDR)&(this->srvAddr), sizeof(this->srvAddr));
	if (rtn == SOCKET_ERROR) {
		cout << "Server socket bind error!\n";
		closesocket(this->srvSocket);
		WSACleanup();
		return -1;
	}

	cout << "Server socket bind success!\n";
	return 0;
}

int Server::ListenStartup() {
	int rtn = listen(this->srvSocket, Config::MAXCONNECTION);
	if (rtn == SOCKET_ERROR) {
		cout << "Server socket listen error!\n";
		closesocket(this->srvSocket);
		WSACleanup();
		return -1;
	}

	cout << "Server socket listen success!\n";
	return 0;
}

void Server::recvMessage(SOCKET socket) {
	int pos_1, pos_2;
	string getresponse,name;
	string str_1;
	int receivedBytes = recv(socket, this->recvBuf, Config::BUFFERLENGTH, 0);
	cout << "recv data:" << endl;
	cout << this->recvBuf << endl;
	if (receivedBytes == SOCKET_ERROR || receivedBytes == 0) {
		cout << "received message error!" << endl;
		return;
	}
	else {
		this->recvBuf[receivedBytes] = '\0';
		getresponse = this->recvBuf;

		//todo
		//ʵ���ܵ�����������������յ�����ʲô�����ļ�������
		//�洢��Server���recvType��
		//�˴�������string��ʵ�֣�����չʾ��Ϊѭ��ʵ��
		pos_1 = getresponse.find_first_of('/');
		str_1 = getresponse.substr(pos_1 + 1);
		pos_2 = str_1.find_first_of(' ');
		name = str_1.substr(0, pos_2);
		//for (counter = 5; counter < receivedBytes; counter++) {
		//	if (this->recvBuf[counter] != ' ') {
		//		this->recvType[counter-5] = this->recvBuf[counter];
		//	}
		//	else {
		//		break;
		//	}
		//}
		memcpy(this->recvType,(char*)name.c_str(),name.length());
		cout << "\n\n"<<this->recvType<<"\n\n" << endl;
	}
}

void Server::sendMessage(SOCKET socket) {
	string end("\r\n\r\n0");
	int length = 0;
	string responseHeader;
	string responseFileName;
	fstream file;
	string responseType;
	//��ȡ�����ļ�������������,��������Ӧ������
	responseFileName = this->recvType;
	file.open(responseFileName.c_str(),ios::binary||ios::in);
	//��ȡ�����ļ�����
	if (file.is_open()) {
		cout << "sdsad";
	}
	memset(HugeBuffer, '\0', 1000000000);
	file.read(HugeBuffer, 1000000000);
	file.close();
	file.open(responseFileName.c_str(),ios::binary||ios::in);
	length = strlen(HugeBuffer);
	//������Ӧ����ͷ��
	switch (this->getType(responseFileName))
	{
	case 1:
		responseType = "text/html"; break;
	case 2:
		responseType = "audio/basic"; break;
	case 3:
		responseType = "image/jpeg"; break;
	}
	char buf[512];
	snprintf(buf, 512, "HTTP / 1.1 200 OK\r\nContent-Type:%s; charset = UTF-8\r\nServer: TYhttp_v1.0.1\r\nContent-Length:%d\r\n\r\n", responseType.c_str(),length);
	responseHeader = buf;

	int rtn = send(socket, responseHeader.c_str(),responseHeader.length(),0);
	if (rtn == SOCKET_ERROR) {
		cout << "Send to client failed!" << endl;
		return;
	}
	char sendbuf[1024];
	memset(sendbuf, '\0',1024);
	int times = length / 1024 + 1; 
	int stop=1024;
	while (times != 0) {
		file.read(sendbuf,1024);
		file.seekg(stop, ios::beg);
		stop += 1024;
		int rtn = send(socket, sendbuf, strlen(sendbuf), 0);
		if (rtn == SOCKET_ERROR) {
			cout << "Send to client failed!" << endl;
			return;
		}
		//send(socket, end.c_str(), sizeof(end.c_str()), 0);
		times--;
	}
	cout << "send data:" << endl;
	cout << responseHeader << endl;
	return;
}

SOCKET Server::ConnectStartup() {
	sockaddr_in addrClient;
	int nClinetAddrLen = sizeof(addrClient);
	SOCKET socketClient = accept(this->srvSocket, (sockaddr*)&addrClient, &nClinetAddrLen);
	if (SOCKET_ERROR == socketClient) {
		printf("Accept faild");
		return socketClient;
	}
}

int Server::Loop() {
	while (true) {
		cout << "Listenning......" << endl;
		SOCKET socketClient = ConnectStartup();
		this->recvMessage(socketClient);
		this->sendMessage(socketClient);
		closesocket(socketClient);
	}
}

int Server::getType(string fileName) {
	//��ȡ�ļ���׺
	int pos = fileName.find_last_of('.');
	string fileType;
	fileType = fileName.substr(pos + 1);
	if(fileType==HTML){
		return 1;
	}
	else if (fileType == AUDIO) {
		return 2;
	}
	else if (fileType == JPG) {
		return 3;
	}
	else {
		return 0;
	}
}

Server::~Server() {
	//�ͷŽ��ܻ�����
	if (this->recvBuf != NULL) {
		delete this->recvBuf;
		this->recvBuf = NULL;
	}
	//�ر�server socket
	if (this->srvSocket != NULL) {
		closesocket(this->srvSocket);
		this->srvSocket = NULL;
	}
	if (this->recvType != NULL) {
		delete this->recvType;
		this->recvType = NULL;
	}

	WSACleanup(); //����winsock ���л���
}