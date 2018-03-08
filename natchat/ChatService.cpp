#include "stdafx.h"
#include "ChatService.h"
#include "MessageHeader.h"
#include "ReceivingManager.h"
#include "TicToc.h"

#include <string>
#include <winsock2.h>
#include <thread>

using namespace inner_network;

void initNetworkAndThreads()
{
	//��ʼ��WSA
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		printErrorAndExit(L"�޷���ʼ�� Socket");
	}

	// ��ʼ��������
	l_pSendingManager = std::unique_ptr<SendingManager>(new SendingManager);

	//TODO: ɾ������
	::broadcastTic();
}

std::string getUserNameFromIp(const std::string& ip)
{
	std::unique_lock<std::mutex> lk(l_AllUserMutex);
	return l_AllUser[ip];
}

std::vector<std::pair<std::string, std::string>> getUsers()
{
	using namespace std;
	unique_lock<mutex> lk(l_AllUserMutex);
	using item_type = pair<string, string>;
	vector<item_type> res;
	res.reserve(l_AllUser.size());
	for (const item_type &item : l_AllUser)
	{
		res.push_back(item);
	}
	return res;
}

void SendMessageToIp(const char * message, const char * ip)
{
	std::string msg;
	msg.reserve(strlen(message) + 1); // ����һλ�������Ϣ����
	msg[0] = inner_network::MSG_PRIVATE;
	msg += message;
	l_pSendingManager->send(ip, MESSAGE_RECV_PORT, msg.c_str(), msg.size());
}

void broadcastTic()
{
	std::thread ticThread(inner_network::broadcastTic);
	ticThread.detach();
}
