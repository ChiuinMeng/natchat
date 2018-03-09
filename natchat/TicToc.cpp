#include "stdafx.h"

#include <cstring>
#include <WinSock2.h>

#include "TicToc.h"
#include "ChatService.h"
#include "Resource.h"
#include "MessageHeader.h"

#pragma comment(lib,"ws2_32.lib")

// ����ȫ�ֱ���
std::map<std::string, std::string> l_AllUser;
std::mutex l_AllUserMutex;

namespace inner_network
{
	void handleTic(const char *msg, const char* ip)
	{
		{
			std::lock_guard<std::mutex> lk(l_AllUserMutex);
			l_AllUser[ip] = msg + 1;
		}

		sendTocTo(ip);
		// ��֤�ڴ氲ȫ����������� send
		SendMessage(g_hHWnd, WM_RECEIVE_TIC, NULL, (LPARAM)ip);
	}

	void handleToc(const std::string& msg, const char * ip)
	{
		std::lock_guard<std::mutex> lk(l_AllUserMutex);
		l_AllUser[ip] = msg.substr(1);

		PostMessage(g_hHWnd, WM_RECEIVE_TOC, NULL, NULL);
	}

	void startTicLoop(const int port)
	{
		WSADATA wsdata;
		//����SOCKET�⣬�汾Ϊ2.0  
		WSAStartup(0x0202, &wsdata);

		static constexpr int BUFLEN = 512;

		SOCKET s;
		struct sockaddr_in server, si_other;
		int slen, recv_len;
		char buf[BUFLEN];

		memset(&server, 0, sizeof(server));
		memset(&si_other, 0, sizeof(si_other));

		slen = sizeof(si_other);

		//Create a socket
		if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
		{
			printErrorAndExit(L"�޷�����Udp Server");
		}

		//Prepare the sockaddr_in structure
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = 0;
		server.sin_port = htons(port);

		si_other.sin_family = AF_INET;
		si_other.sin_addr.s_addr = INADDR_BROADCAST;
		si_other.sin_port = htons(5050);

		//�����׽���Ϊ�㲥����,�����͹㲥��Ϣ
		bool so_broadcast = true;
		int ret = setsockopt(s, SOL_SOCKET, SO_BROADCAST, (char *)&so_broadcast, sizeof(so_broadcast));
		if (ret < 0)
		{
			printErrorAndExit(L"�޷����׽�����Ϊ�㲥����");
		}

		//Bind
		if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
		{
			printErrorAndExit(L"�޷���Udp�˿�");
		}

		//keep listening for data
		while (true)
		{
			//clear the buffer by filling null, it might have previously received data
			memset(buf, '\0', BUFLEN);

			//try to receive some data, this is a blocking call
			if ((recv_len = recvfrom(s, buf, BUFLEN - 1, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
			{
				PostMessage(g_hHWnd, WM_RECEIVE_TIC_ERROR, NULL, (LPARAM)"�޷���ȡTIC����");
				continue;
			}

			if (buf[0] == MSG_TIC)
			{
				char ip_buf[20]; // ʹ�� inet_ntop ������ inet_ntoa ����֤��ȫ
				inet_ntop(AF_INET, &si_other.sin_addr, ip_buf, sizeof(ip_buf));
				handleTic(buf, ip_buf);
			}
		}

		closesocket(s);
	}

	void sendTocTo(const char *ip)
	{
		char bufferOut[128];
		bufferOut[0] = MSG_TOC;
		int res = gethostname(bufferOut + 1, 127);
		//assert(res == 0);

		SendingManager::send(ip, MESSAGE_RECV_PORT, bufferOut, strlen(bufferOut));
	}

	void sendBroadcastError(const char* msg)
	{
		SendMessage(g_hHWnd, WM_BROADCAST_TIC_ERROR, NULL, (LPARAM)msg);
	}

	void broadcastTic(const int port)
	{
		WSADATA wsdata;
		//����SOCKET�⣬�汾Ϊ2.0  
		WSAStartup(0x0202, &wsdata);

		SOCKET sock;
		if ((sock = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)) < 0)
		{
			return sendBroadcastError("ˢ��ʧ�ܣ��޷������㲥 socket");
		}

		int ret;

		char bufferOut[128];
		bufferOut[0] = MSG_TIC;
		ret = gethostname(bufferOut + 1, 127);
		//assert(ret == 0);

		struct sockaddr_in addr;
		memset(&addr, 0, sizeof(addr));
		addr.sin_port = htons(port);
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = INADDR_BROADCAST;
		//inet_pton(AF_INET, "192.168.1.3", (void *)&(addr.sin_addr));

		bool opt = true;
		//���ø��׽���Ϊ�㲥���ͣ�  
		setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char FAR *)&opt, sizeof(opt));

		int addr_len = sizeof(addr);
		ret = sendto(sock, bufferOut, strlen(bufferOut), 0, (struct sockaddr *)&addr, addr_len);
		if (ret == SOCKET_ERROR)
		{
			sendBroadcastError("ˢ��ʧ�ܣ�send error");
		}

		Sleep(500);
		closesocket(sock);
	}

}