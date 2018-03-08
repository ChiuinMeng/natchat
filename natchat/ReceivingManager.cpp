#include "stdafx.h"
#include "ReceivingManager.h"
#include "MessageHeader.h"
#include "TicToc.h"
#include "File.h"

#include "Resource.h"

#include "ChatService.h"

namespace inner_network
{
	void ReceivingManager::initReceivingManager(const int receivingPort)
	{
		//�����׽���
		SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (slisten == INVALID_SOCKET)
		{
			printErrorAndExit(L"�޷���������Socket");
		}

		//��IP�Ͷ˿�
		sockaddr_in sin;
		sin.sin_family = AF_INET;
		sin.sin_port = htons(receivingPort);
		sin.sin_addr.S_un.S_addr = INADDR_ANY;
		if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
		{
			printErrorAndExit(L"�޷��󶨽����˿ڣ�");
		}

		//��ʼ����
		if (listen(slisten, 5) == SOCKET_ERROR)
		{
			printErrorAndExit(L"�޷���ʼ����");
		}

		// ��ʼѭ��������Ϣ
		ReceivingManager::receivingThread = std::thread(ReceivingManager::startReceivingLoop, slisten);
		receivingThread.detach();
	}

	void handleMessage(std::string msg, sockaddr_in addr)
	{
		// ��ȡip
		char ip_buf[20]; // ʹ�� inet_ntop ������ inet_ntoa ����֤��ȫ
		inet_ntop(AF_INET, &addr.sin_addr, ip_buf, sizeof(ip_buf));

		if (msg[0] == MSG_REGULAR)
		{
			History history;
			history.isPrivate = false;
			history.message = msg.substr(1);
			history.senderName = getUserNameFromIp(ip_buf);
			history.time = std::chrono::system_clock::now();
			{
				std::lock_guard<std::mutex> lk(g_HistoryMutex);
				g_Histories.push_back(history);
			}
			PostMessage(g_hHWnd, WM_RECOMMEND_REFRESH_HISTORIES, NULL, NULL);
		}
		else if (msg[0] == MSG_TOC)
		{
			handleToc(msg, ip_buf);
		}
		else if (msg[0] == MSG_PRIVATE)
		{
			History history;
			history.isPrivate = true;
			history.message = msg.substr(1);
			history.senderName = getUserNameFromIp(ip_buf);
			history.time = std::chrono::system_clock::now();
			{
				std::lock_guard<std::mutex> lk(g_HistoryMutex);
				g_Histories.push_back(history);
			}
			PostMessage(g_hHWnd, WM_RECOMMEND_REFRESH_HISTORIES, NULL, NULL);
		}
		else if (msg[0] == MSG_FILE)
		{
			// �����������߳�ֱ���������ļ�
			handleFileMessage(msg);
		}
	}

	void ReceivingManager::startReceivingLoop(SOCKET sListen)
	{
		std::string res;

		//ѭ����������
		SOCKET sClient;
		sockaddr_in remoteAddr;
		int nAddrlen = sizeof(remoteAddr);
		char buffer[255];
		while (true)
		{
			// �ȴ�����
			sClient = accept(sListen, (SOCKADDR *)&remoteAddr, &nAddrlen);
			if (sClient == INVALID_SOCKET)
			{
				PostMessage(g_hHWnd, WM_RECEIVE_MESSAGE_ERROR, 0, (LPARAM)"�޷�������������");
			}

			//��������
			while (true)
			{
				int ret = recv(sClient, buffer, 255, 0);
				if (ret > 0)
				{
					buffer[ret] = '\0';
					res.append(buffer);
					if (res[res.size() - 1] == '\f')
					{
						// �Ѿ�������β
						res.pop_back();
						break;
					}
				}
			}

			handleMessage(std::move(res), remoteAddr);
		}
	}

}