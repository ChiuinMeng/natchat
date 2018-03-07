#pragma once

#include <thread>
#include <mutex>  
#include <condition_variable>  
#include <memory>
#include <queue>

#include "ConcurrentSender.h"

namespace inner_network
{
	/// <summary>
	/// ����Socket��Ϣ���͵���
	/// </summary>
	class SendingManager
	{
	private:
		/// <summary>
		/// ����������Ϣ���ͺͶ��й�����߳�
		/// </summary>
		std::thread sendingThread;

		mutable std::mutex mut;
		std::queue<std::shared_ptr<ConcurrentSender>> sendingQueue;
		std::condition_variable dataCond;

		void startLoop();

	public:
		SendingManager()
			:sendingThread(&SendingManager::startLoop, this)
		{
		}
		~SendingManager() {}

		/// <summary>
		/// ��ָ��Ŀ�귢�����ݣ���������Ͷ��У�
		/// </summary>
		/// <param name="address"></param>
		/// <param name="port"></param>
		/// <param name="buffer"></param>
		/// <param name="bufferSize"></param>
		void send(const char* address, int port, const char* buffer, size_t bufferSize);
	};

}