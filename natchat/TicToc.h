/// <summary>
/// ����ͻ���̽��ĺ������⼸���������ᴴ���µ��߳�
/// </summary>
#pragma once

#include "stdafx.h"
#include <string>

namespace inner_network
{
	void broadcastTic();

	void sendTocTo(const std::string ip);

	void handleTic(std::string msg, sockaddr_in addr);
}