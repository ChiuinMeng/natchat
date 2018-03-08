#include "stdafx.h"
#include "SendingManager.h"
#include "Resource.h"
#include "ChatService.h"

namespace inner_network
{
	void SendingManager::startLoop()
	{
		while (true)
		{
			std::shared_ptr<ConcurrentSender> ptr;
			{
				// �����̹߳���Ķ��дӶ�ȡ��һ�� Sender
				std::unique_lock<std::mutex> lk(SendingManager::mut);
				SendingManager::dataCond.wait(lk, [&] {return !SendingManager::sendingQueue.empty(); });
				ptr = SendingManager::sendingQueue.front();
				SendingManager::sendingQueue.pop();
			}
			// ����֮����ִ�� Sender����ֹ��ִ��ʱ�������в��������߳�
			bool success = ptr->waitDone();
			if (success)
			{
				// ֻ�д�������ļ���ʱ��Żᷢ��֪ͨ
				if (ptr->isSendingFile())
				{
					PostMessage(g_hHWnd, IDC_SEND_FILE_DONE, 0, 0);
				}

			}
			else
			{
				auto msg = (LPARAM)"����ʧ��";
				if (ptr->isSendingFile())
				{
					// ��ֹ����ʧЧ���ڷ��ʹ���Ϣ��ʱ�������̣߳������ͷ� SocketException �е� string �ڴ�
					SendMessage(g_hHWnd, IDC_SEND_FILE_ERROR, 0, msg);
				}
				else
				{
					SendMessage(g_hHWnd, IDC_SEND_MESSAGE_ERROR, 0, msg);
				}
			}
		}

	}

	void SendingManager::send(const char * address, int port, const char * buffer, size_t bufferSize, bool isFile)
	{
		std::lock_guard<std::mutex> lk(SendingManager::mut);
		SendingManager::sendingQueue.emplace(new ConcurrentSender(address, port, buffer, bufferSize, isFile));
		SendingManager::dataCond.notify_one();
	}

}