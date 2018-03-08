
// natchatDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "PrivateMessageDlg.h"
#include "RefreshingDlg.h"
#include "afxwin.h"


// CnatchatDlg �Ի���
class CnatchatDlg : public CDialogEx
{
// ����
public:
	CnatchatDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NATCHAT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//HANDLE cursor_thread;
	//DWORD myownthread;
	CRect send_rect;
	CRect emotion_rect;
	bool send_started_draw = false;
	bool emotion_started_draw = false;
	bool is_cursor_hand = false;
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl M_IPList;
	afx_msg void OnNMClickIplist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnStnClickedReceivertext();
	afx_msg void OnNMDblclkIplist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRefresh();
	CPictureEx send_animation;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	CPictureEx emotion_animation;
	afx_msg void OnBnClickedChoosefile();
//	afx_msg void OnStnClickedSendani();
//	afx_msg void OnStnClickedEmotionani();
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnRecommendRefreshHistories(WPARAM wParam, LPARAM lParam);
protected:
	afx_msg LRESULT OnReceiveToc(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReceiveTic(WPARAM wParam, LPARAM lParam);
};

//void detect_cursor();
