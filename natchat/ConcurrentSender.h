#pragma once

#include <future>

namespace inner_network
{
	/// <summary>
	/// ����һ���̷߳���buffer
	/// </summary>
	class ConcurrentSender
	{
	public:
		/// <summary>
		/// ��ʼ����������һ���߳���������ʼ��������
		/// </summary>
		/// <param name="address">Ŀ��ip��ַ</param>
		/// <param name="port">Ŀ��˿�</param>
		/// <param name="buffer">Ҫ���͵����ݣ�һ���Է��꣩</param>
		/// <param name="bufferSize">�������ݵĴ�С</param>
		/// <param name="isSendingFile">���͵��Ƿ����ļ�</param>
		ConcurrentSender(const char* address, const int port, const char* buffer, const size_t bufferSize,
			bool isSendingFile = false);
		~ConcurrentSender();

		/// <summary>
		/// ����Ƿ������
		/// </summary>
		/// <returns>��ɷ���true������false</returns>
		bool checkDone();

		/// <summary>
		/// ������ǰ�̣߳�ֱ����ɴ��䡣ֻ�ܵ���һ�Σ������׳��쳣
		/// </summary>
		void waitDone();

		/// <summary>
		/// ��ǰ������Ƿ����ļ�
		/// </summary>
		/// <returns></returns>
		bool isSendingFile()
		{
			return this->isSendingFile;
		}
	private:
		char* buffer;
		size_t bufferSize;
		std::future<bool> future;
		std::string address;
		int port;
		bool isSendingFile;

		bool startSend();
	};

}