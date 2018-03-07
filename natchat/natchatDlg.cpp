
// natchatDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "natchat.h"
#include "natchatDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CnatchatDlg �Ի���



CnatchatDlg::CnatchatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NATCHAT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CnatchatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPLIST, M_IPList);
}

BEGIN_MESSAGE_MAP(CnatchatDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CLICK, IDC_IPLIST, &CnatchatDlg::OnNMClickIplist)
	ON_NOTIFY(NM_DBLCLK, IDC_IPLIST, &CnatchatDlg::OnNMDblclkIplist)
	ON_BN_CLICKED(IDC_REFRESH, &CnatchatDlg::OnBnClickedRefresh)
END_MESSAGE_MAP()


// CnatchatDlg ��Ϣ�������

BOOL CnatchatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	M_IPList.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	M_IPList.SetExtendedStyle(M_IPList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// Ϊ�б���ͼ�ؼ��������   
	M_IPList.InsertColumn(0, _T("HOST"), LVCFMT_CENTER, rect.Width() / 2, 0);
	M_IPList.InsertColumn(1, _T("IP"), LVCFMT_CENTER, rect.Width() / 2, 1);

	// ���б���ͼ�ؼ��в����б���������б������ı�   
	M_IPList.InsertItem(0, _T("Java"));
	M_IPList.SetItemText(0, 1, _T("192.168.1.6"));
	M_IPList.InsertItem(1, _T("C"));
	M_IPList.SetItemText(1, 1, _T("192.168.1.7"));
	M_IPList.InsertItem(2, _T("C#"));
	M_IPList.SetItemText(2, 1, _T("192.168.1.8"));
	M_IPList.InsertItem(3, _T("C++"));
	M_IPList.SetItemText(3, 1, _T("192.168.1.4"));
	M_IPList.InsertItem(3, _T("C++"));
	M_IPList.SetItemText(3, 1, _T("192.168.1.4"));
	M_IPList.InsertItem(4, _T("C++"));
	M_IPList.SetItemText(4, 1, _T("192.168.1.4"));
	M_IPList.InsertItem(5, _T("C++"));
	M_IPList.SetItemText(5, 1, _T("192.168.1.4"));
	M_IPList.InsertItem(6, _T("C++"));
	M_IPList.SetItemText(6, 1, _T("192.168.1.4"));
	M_IPList.InsertItem(7, _T("C++"));
	M_IPList.SetItemText(7, 1, _T("192.168.1.4"));
	M_IPList.InsertItem(8, _T("C++"));
	M_IPList.SetItemText(8, 1, _T("192.168.1.4"));
	M_IPList.InsertItem(9, _T("C++"));
	M_IPList.SetItemText(9, 1, _T("192.168.1.4"));
	M_IPList.InsertItem(10, _T("C++"));
	M_IPList.SetItemText(10, 1, _T("192.168.1.4"));
	M_IPList.InsertItem(11, _T("C++"));
	M_IPList.SetItemText(11, 1, _T("192.168.1.4"));
	M_IPList.InsertItem(12, _T("C++"));
	M_IPList.SetItemText(12, 1, _T("192.168.1.4"));
	M_IPList.InsertItem(13, _T("C++"));
	M_IPList.SetItemText(13, 1, _T("192.168.1.4"));
	M_IPList.InsertItem(14, _T("C++"));
	M_IPList.SetItemText(14, 1, _T("192.168.1.4"));
	M_IPList.InsertItem(15, _T("C++"));
	M_IPList.SetItemText(15, 1, _T("192.168.1.4"));
	M_IPList.InsertItem(16, _T("C++"));
	M_IPList.SetItemText(16, 1, _T("192.168.1.4"));
	M_IPList.InsertItem(17, _T("C++"));
	M_IPList.SetItemText(17, 1, _T("192.168.1.4"));
	M_IPList.InsertItem(18, _T("C++"));
	M_IPList.SetItemText(18, 1, _T("192.168.1.4"));
	M_IPList.InsertItem(19, _T("C++"));
	M_IPList.SetItemText(19, 1, _T("192.168.1.4"));
	M_IPList.InsertItem(20, _T("C++"));
	M_IPList.SetItemText(20, 1, _T("192.168.1.4"));


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CnatchatDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CnatchatDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CnatchatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CnatchatDlg::OnNMClickIplist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString hostName;    // ѡ��host�������ַ���   
	CString IPName;    // ѡ��IP�������ַ���   
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;

	if (-1 != pNMListView->iItem)        // ���iItem����-1����˵�����б��ѡ��   
	{
		// ��ȡ��ѡ���б����һ��������ı�   
		hostName = M_IPList.GetItemText(pNMListView->iItem, 0);
		IPName = M_IPList.GetItemText(pNMListView->iItem, 1);
		// ��ʾ
		SetDlgItemText(IDC_RECRIVERHOST, hostName);
		SetDlgItemText(IDC_RECRIVERIP, IPName);
	}
	else {
		SetDlgItemText(IDC_RECRIVERHOST, L"");
		SetDlgItemText(IDC_RECRIVERIP, L"");
	}
	*pResult = 0;
}



void CnatchatDlg::OnNMDblclkIplist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;
	CString hostName;
	CString head = L"Private Message To ";

	if (-1 != pNMListView->iItem) {
		hostName = M_IPList.GetItemText(pNMListView->iItem, 0);
		CPrivateMessageDlg pm(head + hostName + L":");
		pm.DoModal();
	}
	*pResult = 0;
}


void CnatchatDlg::OnBnClickedRefresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRefreshingDlg rfd;
	rfd.DoModal();
}
