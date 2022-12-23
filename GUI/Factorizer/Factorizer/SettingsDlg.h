#pragma once

#include <fstream>
#include <string>

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

public:
	bool minimize;
	bool alert;
	CButton m_check1;
	CButton m_check2;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
