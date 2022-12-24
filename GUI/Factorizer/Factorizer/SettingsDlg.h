#pragma once

#include <fstream>
#include <string>
#include <locale>

// SettingsDlg 对话框

class SettingsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SettingsDlg)

public:
	SettingsDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SettingsDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTINGS };
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
	bool minimize;
	bool alert;
	int lang;
	CButton m_check1;
	CButton m_check2;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CComboBox m_combo1;
	afx_msg void OnBnClickedCancel();
};
