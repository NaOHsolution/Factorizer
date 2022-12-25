#pragma once

#include <fstream>
#include <sstream>
#include <locale>
#include "functions.h"

// GCDLCMDlg 对话框

class GCDLCMDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GCDLCMDlg)

public:
	GCDLCMDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~GCDLCMDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GCDLCM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
		if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return TRUE;
		else
			return CDialog::PreTranslateMessage(pMsg);
	}
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	CEdit m_edit1;
	CEdit m_edit2;
	CEdit m_edit3;
	CEdit m_edit4;
};
