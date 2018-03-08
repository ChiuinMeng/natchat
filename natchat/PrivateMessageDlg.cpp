// PrivateMessageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "natchat.h"
#include "PrivateMessageDlg.h"
#include "afxdialogex.h"


// CPrivateMessageDlg �Ի���

IMPLEMENT_DYNAMIC(CPrivateMessageDlg, CDialogEx)

CPrivateMessageDlg::CPrivateMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SENDBOX, pParent) {

}

CPrivateMessageDlg::CPrivateMessageDlg(const CString& title, const CString& IP_adr, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SENDBOX, pParent)
{
	mytitle = title;
	this->IP_adr = IP_adr;
}

CPrivateMessageDlg::~CPrivateMessageDlg()
{
}

BOOL CPrivateMessageDlg::OnInitDialog()
{
	this->SetWindowTextW(L"Private Message");
	this->SetDlgItemTextW(IDC_PRIVATETEXT, mytitle);
	return TRUE;
}


void CPrivateMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPrivateMessageDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CANCEL, &CPrivateMessageDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SENDPRIVATE, &CPrivateMessageDlg::OnBnClickedSendprivate)
END_MESSAGE_MAP()


// CPrivateMessageDlg ��Ϣ�������


void CPrivateMessageDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(0);
}


void CPrivateMessageDlg::OnBnClickedSendprivate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString message;
	GetDlgItemText(IDC_PRIVATEEDIT, message);
	std::string msg, ip;
	cstring2string(message, msg);
	cstring2string(IP_adr, ip);
	SendMessageToIp(msg.c_str(), ip.c_str());
	EndDialog(0);
}
