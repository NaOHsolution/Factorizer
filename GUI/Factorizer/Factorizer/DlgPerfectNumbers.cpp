// DlgPerfectNumbers.cpp: 实现文件
//

#include "pch.h"
#include "Factorizer.h"
#include "DlgPerfectNumbers.h"
#include "afxdialogex.h"

enum indexPerfectNumbers {
	perfectNumbersTitle, groupPerfectNumbers, textNumber, buttonTest, textResult, groupFriendlyNumbers, textFirstNumber, 
	textSecondNumber, resultYes, resultNo, resultSameNumber, resultUndefined
};

CString captionPerfectNumbers[15];

// DlgPerfectNumbers 对话框

IMPLEMENT_DYNAMIC(DlgPerfectNumbers, CDialogEx)

DlgPerfectNumbers::DlgPerfectNumbers(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PERFECTNUMBERS, pParent)
{

}

DlgPerfectNumbers::~DlgPerfectNumbers()
{
}

void DlgPerfectNumbers::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_1, m_edit1);
	DDX_Control(pDX, IDC_EDIT_2, m_edit2);
	DDX_Control(pDX, IDC_EDIT_3, m_edit3);
	DDX_Control(pDX, IDC_EDIT_4, m_edit4);
	DDX_Control(pDX, IDC_EDIT_5, m_edit5);
}


BEGIN_MESSAGE_MAP(DlgPerfectNumbers, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_3, &DlgPerfectNumbers::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, &DlgPerfectNumbers::OnBnClickedButton4)
END_MESSAGE_MAP()


// DlgPerfectNumbers 消息处理程序


BOOL DlgPerfectNumbers::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	std::wfstream fs;
	std::wstring buf1;
	bool buf2, buf3;
	int lang;
	CString path = currentPath();

	fs.open(path + L"config.dll", std::ios::in);
	if (!fs.is_open()) {
		MessageBox(L"Configuration file not found.", L"Fatal Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		abort();
	}
	fs >> buf2 >> buf3 >> lang;
	fs.close();

	switch (lang) {
	case english:
		fs.open(path + L"lang\\english_perfectnumbers.lang", std::ios::in);
		SetDlgItemText(IDC_COMBO_1, L"English");
		break;
	case simplifiedChinese:
		std::locale simplifiedChinese("zh_CN.UTF-8");
		fs.imbue(simplifiedChinese);
		fs.open(path + L"lang\\simpchinese_perfectnumbers.lang", std::ios::in);
		SetDlgItemText(IDC_COMBO_1, L"简体中文");
		break;
	}
	if (!fs.is_open()) {
		MessageBox(L"Cannot open language file.", L"Fatal error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		abort();
	}
	for (int i = 0; i < 12; ++i) {
		std::getline(fs, buf1, L'\n');
		captionPerfectNumbers[i] = buf1.c_str();
	}
	fs.close();

	SetWindowText(captionPerfectNumbers[perfectNumbersTitle]);
	SetDlgItemText(IDC_STATIC_1, captionPerfectNumbers[groupPerfectNumbers]);
	SetDlgItemText(IDC_STATIC_2, captionPerfectNumbers[textNumber]);
	SetDlgItemText(IDC_STATIC_3, captionPerfectNumbers[textResult]);
	SetDlgItemText(IDC_STATIC_4, captionPerfectNumbers[groupFriendlyNumbers]);
	SetDlgItemText(IDC_STATIC_5, captionPerfectNumbers[textFirstNumber]);
	SetDlgItemText(IDC_STATIC_6, captionPerfectNumbers[textSecondNumber]);
	SetDlgItemText(IDC_STATIC_7, captionPerfectNumbers[textResult]);
	SetDlgItemText(IDC_BUTTON_3, captionPerfectNumbers[buttonTest]);
	SetDlgItemText(IDC_BUTTON_4, captionPerfectNumbers[buttonTest]);
	m_edit1.SetLimitText(9);
	m_edit1.SetWindowText(L"6");
	m_edit3.SetLimitText(9);
	m_edit3.SetWindowText(L"220");
	m_edit4.SetLimitText(9);
	m_edit4.SetWindowText(L"284");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void DlgPerfectNumbers::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	std::wstringstream buf1;
	std::vector<ull> f;
	CString buf2;
	ull t, s = 0;

	m_edit1.GetWindowText(buf2);
	buf1 << buf2.GetString();
	buf1 >> t;
	if (t == 0) {
		m_edit2.SetWindowText(captionPerfectNumbers[resultUndefined]);
		return;
	}
	f = factors(t);
	for (std::vector<ull>::iterator itr = f.begin(); itr + 1 != f.end(); ++itr) s += *itr;
	if (s == t) m_edit2.SetWindowText(captionPerfectNumbers[resultYes]);
	else m_edit2.SetWindowText(captionPerfectNumbers[resultNo]);
}


void DlgPerfectNumbers::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	std::wstringstream buf1;
	std::vector<ull> f1, f2;
	CString buf2;
	ull t1, t2, s1 = 0, s2 = 0;

	m_edit3.GetWindowText(buf2);
	buf1 << buf2.GetString() << L" ";
	m_edit4.GetWindowText(buf2);
	buf1 << buf2.GetString();
	buf1 >> t1 >> t2;
	if (t1 == 0 || t2 == 0) {
		m_edit5.SetWindowText(captionPerfectNumbers[resultUndefined]);
		return;
	}
	if (t1 == t2) {
		m_edit5.SetWindowText(captionPerfectNumbers[resultSameNumber]);
		return;
	}
	f1 = factors(t1), f2 = factors(t2);
	for (std::vector<ull>::iterator itr = f1.begin(); itr + 1 != f1.end(); ++itr) s1 += *itr;
	for (std::vector<ull>::iterator itr = f2.begin(); itr + 1 != f2.end(); ++itr) s2 += *itr;
	if (s1 == t2 && s2 == t1) m_edit5.SetWindowText(captionPerfectNumbers[resultYes]);
	else m_edit5.SetWindowText(captionPerfectNumbers[resultNo]);
}
