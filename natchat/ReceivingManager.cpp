#include "stdafx.h"
#include "ReceivingManager.h"
#include "MessageHeader.h"

#include "Resource.h"

#include "ChatService.h"

namespace inner_network
{
	ReceivingManager::ReceivingManager(const int receivingPort)
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
		receivingThread = std::thread(&ReceivingManager::startReceivingLoop, this, slisten);
	}


	ReceivingManager::~ReceivingManager()
	{
	}

	void handleMessage(std::string msg, sockaddr_in addr)
	{
		if (msg[0] == MSG_REGULAR)
		{
			History history;
			history.isPrivate = false;
			history.message = msg.substr(1);
			std::unique_lock<std::mutex> lk1(g_AllUserMutex);
			char ip_buf[20]; // ʹ�� inet_ntop ������ inet_ntoa ����֤��ȫ
			inet_ntop(AF_INET, &addr.sin_addr, ip_buf, sizeof(ip_buf));
			history.message = g_AllUser[ip_buf];
			history.time = std::chrono::system_clock::now();
			std::unique_lock<std::mutex> lk2(g_HistoryMutex);
			g_Histories.push_back(history);
		}
		else if (msg[0] == MSG_TIC)
		{

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
				PostMessage(AfxGetMainWnd()->m_hWnd, IDC_RECEIVE_MESSAGE_ERROR, 0, (LPARAM)"�޷�������������");
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

	void printErrorAndExit(const wchar_t* errMsg)
	{
		MessageBox(AfxGetMainWnd()->m_hWnd, errMsg, L"��ʼ������", MB_OK);
		exit(0);
	}

}