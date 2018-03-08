#pragma once

#include "ChatService.h"

// CPrivateMessageDlg �Ի���

class CPrivateMessageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPrivateMessageDlg)

public:
	CPrivateMessageDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CPrivateMessageDlg(const CString& title, const CString& IP_adr,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPrivateMessageDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SENDBOX };
#endif

private:
	CString mytitle;
	CString IP_adr;

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSendprivate();
};
