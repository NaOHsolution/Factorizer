#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

ull power(ull b, int e);
std::vector<ull> separate(ull t, int r);

// DlgNarcissisticNumbers 对话框

class DlgNarcissisticNumbers : public CDialogEx
{
	DECLARE_DYNAMIC(DlgNarcissisticNumbers)

public:
	DlgNarcissisticNumbers(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgNarcissisticNumbers();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NARCISSISTICNUMBERS };
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
	CEdit m_edit1;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	CEdit m_edit2;
};
