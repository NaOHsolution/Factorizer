#pragma once

#include <fstream>
#include <sstream>
#include "functions.h"

// DlgBaseConversion 对话框

class DlgBaseConversion : public CDialogEx
{
	DECLARE_DYNAMIC(DlgBaseConversion)

public:
	DlgBaseConversion(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgBaseConversion();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BASECONVERSION };
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
	CComboBox m_combo1;
	CComboBox m_combo2;
	CEdit m_edit1;
	CEdit m_edit2;
	afx_msg void OnBnClickedButton1();
};
