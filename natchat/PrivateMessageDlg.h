#pragma once


// CPrivateMessageDlg �Ի���

class CPrivateMessageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPrivateMessageDlg)

public:
	CPrivateMessageDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CPrivateMessageDlg(const CString& title, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPrivateMessageDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SENDBOX };
#endif

private:
	CString mytitle;

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedCancel();
};
