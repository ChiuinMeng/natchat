#include "stdafx.h"
#include "File.h"
#include "ChatService.h"
#include "MessageHeader.h"

#include <fstream>
#include <sstream>
#include <string>
#include <locale>
#include <codecvt>

// ������ȫ�ֱ��������ļ���
std::wstring g_wsSaveFilePath;

namespace inner_network
{
	std::string getFileNameFromPath(const std::wstring &filePath)
	{
		auto idx = filePath.find_last_of(L'\\');
		auto fileName = filePath.substr(idx + 1);

		// �� utf-8 ����ת��
		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;

		return converter.to_bytes(fileName);
	}

	void sendFileToIp(const std::wstring &filePath, const char* distIp)
	{

		std::ifstream fin(filePath, std::ios::in | std::ios::binary);
		std::ostringstream os;

		os << MSG_FILE << getFileNameFromPath(filePath) << "\r" << fin.rdbuf();

		std::string buf = os.str();

		SendingManager::send(distIp, MESSAGE_RECV_PORT, buf.c_str(), buf.size(), true);
	}

	void handleFileMessage(const std::string & message)
	{
		size_t fileNameEnd = message.find_first_of('\r');
		std::string fileName = message.substr(1, fileNameEnd - 1);

		// �� utf-8 ����ת��
		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;

		std::wstring wFileName = converter.from_bytes(fileName);

		// ����������Ϣ�������Ϳ���������Ϣѭ���������ļ�λ��֮��ֱ�ӷ��ز������ļ��ˡ�
		SendMessage(g_hHWnd, WM_RECEIVE_FILE, NULL, (LPARAM)wFileName.c_str());

		std::ofstream out(g_wsSaveFilePath, std::ios::out | std::ios::binary);
		out << message.substr(fileNameEnd + 1);
	}

}