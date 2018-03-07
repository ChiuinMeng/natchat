#pragma once
#include "afxwin.h"
#include "PictureEx.h"


// CRefreshingDlg �Ի���

class CRefreshingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRefreshingDlg)

public:
	CRefreshingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRefreshingDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REFRESH };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CPictureEx refreshing_img;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
