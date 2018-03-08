/// <summary>
/// ����ͻ���̽��ĺ������⼸���������ᴴ���µ��߳�
/// </summary>
#pragma once

#include "stdafx.h"
#include <string>

namespace inner_network
{
	/// <summary>
	/// �㲥 Tic ��udp��
	/// </summary>
	void broadcastTic(const int port);

	/// <summary>
	/// �� tcp �ظ� toc
	/// </summary>
	void sendTocTo(const char *ip);

	/// <summary>
	/// ����һ�� Tic ��Ϣ
	/// </summary>
	void handleTic(const char *msg, const char* ip);

	/// <summary>
	/// ����һ�� udp server��ѭ������ Tic
	/// </summary>
	void startTicLoop(const int port);

	/// <summary>
	/// ���� Toc ��Ϣ
	/// </summary>
	void handleToc(const std::string &msg, const char* ip);
}