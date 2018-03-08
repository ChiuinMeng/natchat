#pragma once

#include <string>
#include <chrono>
#include <list>
#include <algorithm>
#include <memory>
#include <winsock2.h>
#include <map>
#include <locale>
#include <codecvt>

#include "SendingManager.h"
#include "Resource.h"
#include "MessageHeader.h"

#pragma comment(lib,"ws2_32.lib")

struct History
{
	/// <summary>
	/// �����ߵļ������
	/// </summary>
	std::string senderName;

	/// <summary>
	/// ����ʱ��
	/// </summary>
	std::chrono::time_point<std::chrono::system_clock> time;

	/// <summary>
	/// ��Ϣ����
	/// </summary>
	std::string message;

	/// <summary>
	/// �Ƿ���˽����Ϣ
	/// </summary>
	bool isPrivate;
};

/// <summary>
/// ������Ϣ����ʷ��¼
/// </summary>
extern std::list<History> g_Histories;
/// <summary>
/// ����ʷ��¼�������ڷ���֮ǰ��Ҫ�����������Է�ֹ��������
/// </summary>
extern std::mutex g_HistoryMutex;

/// <summary>
/// ���е��û���keyΪip��valueΪ�������
/// </summary>
extern std::map<std::string, std::string> l_AllUser;
/// <summary>
/// ���û��б����
/// </summary>
extern std::mutex l_AllUserMutex;

/// <summary>
/// �� ip ��ַ��ȡ����������˹��̻�����������������������ڣ�ֱ�ӷ��� ip
/// </summary>
std::string getUserNameFromIp(const std::string& ip);

/// <summary>
/// ��ȡ���е��û��������������ʽ�� ip���û���
/// </summary>
std::vector<std::pair<std::string, std::string>> getUsers();

/// <summary>
/// ������Ϣ�Ķ˿ڣ��������ͻ��˷�����Ϣʱָ���˶˿�
/// </summary>
const int MESSAGE_RECV_PORT = 7001;

/// <summary>
/// ���� udp ��Ϣ�Ķ˿ڣ����� TicToc
/// </summary>
const int BROADCAST_RECV_PORT = 7002;

/// <summary>
/// ��ָ���� ip ������Ϣ
/// </summary>
void SendMessageToIp(const char* message, const char* ip);

/// <summary>
/// ��ָ���� ip Ⱥ����Ϣ��collection ����ӵ�� cbegin �� cend ������ÿ��Ԫ�ض���һ��ip���ַ�����c_str��
/// </summary>
template <typename COLLECTION>
void BroadcastMessageToIps(const char* message, const COLLECTION collection)
{
	std::string msg;
	msg.reserve(strlen(message) + 1); // ����һλ�������Ϣ����
	msg += inner_network::MSG_REGULAR;
	msg += message;
	for (auto iter = collection.cbegin(); iter != collection.cend(); ++iter)
	{
		inner_network::SendingManager::send(*iter, MESSAGE_RECV_PORT, msg.c_str(), msg.size());
	}
}

/// <summary>
/// ��ʼ��������̣߳���Ҫ�������ڵ� Create �������
/// </summary>
void initNetworkAndThreads();

/// <summary>
/// �㲥��Ϣ���Ӷ�������������
/// </summary>
void refreshUserList();

/// <summary>
/// ���ɴ���Ի����˳�����
/// </summary>
void printErrorAndExit(const wchar_t* errMsg);

/// <summary>
/// �����ھ��
/// </summary>
extern HWND g_hHWnd;

/// <summary>
/// ��ĳ��ip����pathָ�����ļ����ļ������з���Ȩ�ޣ�
/// </summary>
void sendFileToIp(const wchar_t *filePath, const wchar_t* distIp);

/// <summary>
/// cstring ת��Ϊ string
/// </summary>
static void cstring2string(CString & src, std::string & dst) {
	wchar_t  * str = src.GetBuffer();
	dst = std::wstring_convert<std::codecvt_utf8<wchar_t> >().to_bytes(str);
	//dst.assign(wstr.begin(), wstr.end());
}