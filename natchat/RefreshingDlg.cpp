// RefreshingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "natchat.h"
#include "RefreshingDlg.h"
#include "afxdialogex.h"


// CRefreshingDlg �Ի���

IMPLEMENT_DYNAMIC(CRefreshingDlg, CDialogEx)

CRefreshingDlg::CRefreshingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_REFRESH, pParent)
{

}

CRefreshingDlg::~CRefreshingDlg()
{
}

BOOL CRefreshingDlg::OnInitDialog() {
	CRect rect;
	GetDlgItem(IDC_REFRESHING)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	refreshing_img.Create(NULL, WS_CHILD | WS_VISIBLE | SS_ENHMETAFILE, rect, this, 1234);
	if (refreshing_img.Load(_T(".\\loading.gif"))) {
		//refreshing_img.SetBkColor(RGB(255, 255, 255));
		refreshing_img.SetPaintRect(&rect);
		refreshing_img.MoveWindow(&rect, TRUE);
		refreshing_img.Draw();
	}

	SetTimer(1, 5000, NULL);
	return TRUE;
}

void CRefreshingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REFRESHING, refreshing_img);
}


BEGIN_MESSAGE_MAP(CRefreshingDlg, CDialogEx)

	ON_WM_TIMER()
END_MESSAGE_MAP()


// CRefreshingDlg ��Ϣ�������


void CRefreshingDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 1:
		// ����յ�IDΪ1�Ķ�ʱ������Ϣ    
		EndDialog(0);
		break;
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}
