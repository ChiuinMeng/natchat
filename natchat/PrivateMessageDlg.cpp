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

CPrivateMessageDlg::CPrivateMessageDlg(const CString& title, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SENDBOX, pParent)
{
	mytitle = title;
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
END_MESSAGE_MAP()


// CPrivateMessageDlg ��Ϣ�������


void CPrivateMessageDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(0);
}
