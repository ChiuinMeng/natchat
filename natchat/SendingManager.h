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
	/// ����Socket��Ϣ����
	/// </summary>
	namespace SendingManager
	{
		/// <summary>
		/// ����������Ϣ���ͺͶ��й�����߳�
		/// </summary>
		static std::thread sendingThread;

		static std::mutex mut;
		static std::queue<std::shared_ptr<ConcurrentSender>> sendingQueue;
		static std::condition_variable dataCond;

		void startLoop();

		static void initSendingManager()
		{
			sendingThread = std::thread(startLoop);
			sendingThread.detach();
		}

		/// <summary>
		/// ��ָ��Ŀ�귢�����ݣ���������Ͷ��У�
		/// </summary>
		/// <param name="address"></param>
		/// <param name="port"></param>
		/// <param name="buffer"></param>
		/// <param name="bufferSize"></param>
		void send(const std::string address, int port, const char* buffer, size_t bufferSize, bool isFile = false);
	};

}