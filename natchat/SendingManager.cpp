#include "stdafx.h"
#include "SendingManager.h"
#include "SocketException.h"
#include "Resource.h"

namespace inner_network
{
	void SendingManager::startLoop()
	{
		while (true)
		{
			std::shared_ptr<ConcurrentSender> ptr;
			{
				// �����̹߳���Ķ��дӶ�ȡ��һ�� Sender
				std::unique_lock<std::mutex> lk(this->mut);
				this->dataCond.wait(lk, [this] {return !this->sendingQueue.empty(); });
				ptr = this->sendingQueue.front();
				this->sendingQueue.pop();
			}
			// ����֮����ִ�� Sender����ֹ��ִ��ʱ�������в��������߳�
			try
			{
				ptr->waitDone();
				// ֻ�д�������ļ���ʱ��Żᷢ��֪ͨ
				if (ptr->isSendingFile())
				{
					PostMessage(AfxGetMainWnd()->m_hWnd, IDC_SEND_FILE_DONE, 0, 0);
				}
			}
			catch (SocketException& e) 
			{
				auto msg = (LPARAM)e.what();
				if (ptr->isSendingFile())
				{
					// ��ֹ����ʧЧ���ڷ��ʹ���Ϣ��ʱ�������̣߳������ͷ� SocketException �е� string �ڴ�
					SendMessage(AfxGetMainWnd()->m_hWnd, IDC_SEND_FILE_ERROR, 0, msg);
				}
				else
				{
					SendMessage(AfxGetMainWnd()->m_hWnd, IDC_SEND_MESSAGE_ERROR, 0, msg);
				}
			}
		}

	}

	void SendingManager::send(const char * address, int port, const char * buffer, size_t bufferSize)
	{
		std::lock_guard<std::mutex> lk(this->mut);
		this->sendingQueue.emplace(address, port, buffer, bufferSize);
		this->dataCond.notify_one();
	}

}