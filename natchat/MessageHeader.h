#pragma once

// ���ļ��洢������Ϣ����Ϣͷ������������Ϣ����

namespace inner_network
{
	constexpr char MSG_REGULAR = 0x01;
	constexpr char MSG_FILE = 0x02;
	constexpr char MSG_PRIVATE = 0x03;

	// �����������Ϣ���ڿͻ��˼����
	constexpr char MSG_TIC = 0x11; // ���ˢ�°�ť�Ŀͻ���Ⱥ������Ϣ
	constexpr char MSG_TOC = 0x12; // �յ��ϸ���Ϣ�Ŀͻ�����Ŀ�귢�ʹ���Ϣ
	constexpr char MSG_BYE = 0x13; // �˳�ʱ�������ͻ��˷��ʹ���Ϣ
}