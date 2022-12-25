#pragma once


// DlgPerfectNumbers 对话框

class DlgPerfectNumbers : public CDialogEx
{
	DECLARE_DYNAMIC(DlgPerfectNumbers)

public:
	DlgPerfectNumbers(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgPerfectNumbers();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PERFECTNUMBERS };
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
	CEdit m_edit2;
	CEdit m_edit3;
	CEdit m_edit4;
	CEdit m_edit5;
};
