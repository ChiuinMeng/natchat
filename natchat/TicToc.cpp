#include "stdafx.h"

#include <cstring>

#include "TicToc.h"
#include "ChatService.h"
#include "Resource.h"
#include "MessageHeader.h"

namespace inner_network
{
	void handleTic(std::string msg, const char* ip)
	{
		{
			std::lock_guard<std::mutex> lk(l_AllUserMutex);
			l_AllUser[ip] = msg.substr(1);
		}

		sendTocTo(ip);
		// ��֤�ڴ氲ȫ����������� send
		SendMessage(AfxGetMainWnd()->m_hWnd, IDC_RECEIVE_TIC, NULL, (LPARAM)ip);
	}

	void sendTocTo(const char *ip)
	{
		char bufferOut[128];
		bufferOut[0] = MSG_TOC;
		int res = gethostname(bufferOut + 1, 127);
		assert(res == 0);

		l_pSendingManager->send(ip, MESSAGE_RECV_PORT, bufferOut, strlen(bufferOut));
	}

	void sendBroadcastError(const char* msg)
	{
			SendMessage(AfxGetMainWnd()->m_hWnd, IDC_BROADCAST_TIC_ERROR, NULL, (LPARAM)msg);
	}

	void broadcastTic()
	{
		SOCKET sock;
		if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
		{
			return sendBroadcastError("ˢ��ʧ�ܣ��޷������㲥 socket");
		}

		int ret;

		//�����׽���Ϊ�㲥����,�����͹㲥��Ϣ
		bool so_broadcast = true;
		ret = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&so_broadcast, sizeof(so_broadcast));
		if (ret < 0) 
		{
			closesocket(sock);
			return sendBroadcastError("ˢ��ʧ�ܣ�setsockopt SO_SNDBUF error");
		}

		//�����׽��� ���ͻ�����2K
		const int nSendBuf = 2 * 1024;
		ret = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char *)&nSendBuf, sizeof(int));
		if (ret < 0)
		{
			closesocket(sock);
			return sendBroadcastError("ˢ��ʧ�ܣ�setsockopt SO_SNDBUF error");
		}

		char bufferOut[128];
		bufferOut[0] = MSG_TIC;
		ret = gethostname(bufferOut + 1, 127);
		assert(ret == 0);

		struct sockaddr_in addr;
		int addr_len = sizeof(addr);
		ret = sendto(sock, bufferOut, strlen(bufferOut), 0, (struct sockaddr *)&addr, addr_len);
		if (ret != SOCKET_ERROR) 
		{
			sendBroadcastError("ˢ��ʧ�ܣ�send error");
		}
		closesocket(sock);
	}

}