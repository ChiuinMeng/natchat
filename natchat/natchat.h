
// natchat.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CnatchatApp: 
// �йش����ʵ�֣������ natchat.cpp
//

class CnatchatApp : public CWinApp
{
public:
	CnatchatApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CnatchatApp theApp;
