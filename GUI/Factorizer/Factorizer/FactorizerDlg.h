
// FactorizerDlg.h: 头文件
//

#pragma once

#define PRIME_FACTORS false
#define ALL_FACTORS true

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

typedef unsigned long long ull;

struct threadInfo {
	HWND main;

	CProgressCtrl* progress;
	CMyListCtrl* list;
	CButton* button1;
	CButton* button2;
	CStatusBar* status;

	std::vector<ull> numbers;

	bool type;

	bool minimize;
	bool alert;
};

UINT threadFunc(LPVOID lpParam);

// CFactorizerDlg 对话框
class CFactorizerDlg : public CDialogEx
{
// 构造
public:
	CFactorizerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FACTORIZER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	CWinThread* pThread;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
		if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return TRUE;
		else
			return CDialog::PreTranslateMessage(pMsg);
	}
public:
	CStatusBar m_status;
	afx_msg void OnBnClickedButton1();
	CProgressCtrl m_progress1;
	CMyListCtrl m_list1;
	afx_msg void OnAboutAbout();
	CButton m_radio1;
	CButton m_radio2;
	CButton m_radio3;
	CEdit m_edit1;
	CMFCEditBrowseCtrl m_browse1;
	CMFCEditBrowseCtrl m_browse2;
	CButton m_button2;
	CButton m_button1;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedButton2();

	bool minimizeWhenComputing;
	bool alertWhenDone;
	afx_msg void OnToolsCalculator();
	afx_msg void OnOptionsOptions();
	afx_msg void OnOptionsAbout();
	afx_msg void OnToolsOpenincommandprompt();
};
