
// natchatDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "PrivateMessageDlg.h"
#include "RefreshingDlg.h"


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
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl M_IPList;
	afx_msg void OnNMClickIplist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnStnClickedReceivertext();
	afx_msg void OnNMDblclkIplist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRefresh();
};
