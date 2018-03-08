
// natchatDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "natchat.h"
#include "natchatDlg.h"
#include "afxdialogex.h"

#include "ChatService.h"

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
	DDX_Control(pDX, IDC_SENDANI, send_animation);
	DDX_Control(pDX, IDC_EMOTIONANI, emotion_animation);
}

BEGIN_MESSAGE_MAP(CnatchatDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CLICK, IDC_IPLIST, &CnatchatDlg::OnNMClickIplist)
	ON_NOTIFY(NM_DBLCLK, IDC_IPLIST, &CnatchatDlg::OnNMDblclkIplist)
	ON_BN_CLICKED(IDC_REFRESH, &CnatchatDlg::OnBnClickedRefresh)
	ON_WM_MOUSEMOVE()
//	ON_WM_SETCURSOR()
ON_BN_CLICKED(IDC_CHOOSEFILE, &CnatchatDlg::OnBnClickedChoosefile)
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
	CDialogEx::SetBackgroundColor(RGB(255, 255, 255));
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	M_IPList.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	M_IPList.SetExtendedStyle(M_IPList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// Ϊ�б���ͼ�ؼ��������   
	M_IPList.InsertColumn(0, _T("HOSTNAME"), LVCFMT_CENTER, rect.Width() / 2, 0);
	M_IPList.InsertColumn(1, _T("IP"), LVCFMT_CENTER, rect.Width() / 2, 1);

	// ���б���ͼ�ؼ��в����б���������б������ı�   
	M_IPList.InsertItem(0, _T("MYSELF"));
	M_IPList.SetItemText(0, 1, _T("192.168.1.4"));
	M_IPList.InsertItem(1, _T("C"));
	M_IPList.SetItemText(1, 1, _T("192.168.1.6"));

	CRect send_rect;
	GetDlgItem(IDC_SENDANI)->GetWindowRect(&send_rect);
	ScreenToClient(&send_rect);
	//send_animation.Create(NULL, WS_CHILD | WS_VISIBLE | SS_ENHMETAFILE, CRect(0, 0, 100, 100), this, 1234);
	if (send_animation.Load(_T("F:\\code\\natchat\\natchat\\send.gif"))) {
		//refreshing_img.SetBkColor(RGB(255, 255, 255));
		send_animation.SetPaintRect(&send_rect);
		send_animation.MoveWindow(&send_rect, TRUE);
		//send_animation.Draw();
		//send_animation.Stop();
	}

	CRect emotion_rect;
	GetDlgItem(IDC_EMOTIONANI)->GetWindowRect(&emotion_rect);
	ScreenToClient(&emotion_rect);
	//send_animation.Create(NULL, WS_CHILD | WS_VISIBLE | SS_ENHMETAFILE, CRect(0, 0, 100, 100), this, 1234);
	if (emotion_animation.Load(_T("F:\\code\\natchat\\natchat\\emoji.gif"))) {
		//refreshing_img.SetBkColor(RGB(255, 255, 255));
		emotion_animation.SetPaintRect(&emotion_rect);
		emotion_animation.MoveWindow(&emotion_rect, TRUE);
		//emotion_animation.Draw();
		//emotion_animation.Stop();
	}

	// �洢�����ھ��
	g_hHWnd = AfxGetMainWnd()->m_hWnd;

	initNetworkAndThreads();

	//cursor_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(cursor_thread), NULL, 0, &myownthread);

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


void CnatchatDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	GetDlgItem(IDC_SENDANI)->GetWindowRect(&send_rect);
	//ScreenToClient(&send_rect);
	GetDlgItem(IDC_EMOTIONANI)->GetWindowRect(&emotion_rect);
	//ScreenToClient(&emotion_rect);
	POINT cur_point;
	GetCursorPos(&cur_point);
	//ScreenToClient(&cur_point);

	bool do_second_judge = true;

	if (send_rect.PtInRect(cur_point))
	{
		if (!send_started_draw) {
			send_animation.Draw();
			send_started_draw = true;
		}
		//if (!is_cursor_hand) {
			::SetCursor(LoadCursor(NULL, IDC_HAND));
			is_cursor_hand = true;
		//}
		do_second_judge = false;
	}
	else {
		if (send_started_draw) {
			send_animation.Stop();
			send_started_draw = false;
		}
		if (is_cursor_hand) {
			::SetCursor(LoadCursor(NULL, IDC_ARROW));
			is_cursor_hand = false;
		}
	}


	if (do_second_judge) {
		if (emotion_rect.PtInRect(cur_point))
		{
			if (!emotion_started_draw) {
				emotion_animation.Draw();
				emotion_started_draw = true;
			}
			if (!is_cursor_hand) {
				::SetCursor(LoadCursor(NULL, IDC_HAND));
				is_cursor_hand = true;
			}
		}
		else {
			if (emotion_started_draw) {
				emotion_animation.Stop();
				emotion_started_draw = false;
			}
			if (is_cursor_hand) {
				::SetCursor(LoadCursor(NULL, IDC_ARROW));
				is_cursor_hand = false;
			}

		}
	}
	

	
	CDialogEx::OnMouseMove(nFlags, point);
}




void CnatchatDlg::OnBnClickedChoosefile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFile = _T("");

	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("All Files (*.*)|*.*||"), NULL);

	if (dlgFile.DoModal())
	{
		strFile = dlgFile.GetPathName();
		SetDlgItemText(IDC_SELECTEDFILE, strFile);
	}
}
