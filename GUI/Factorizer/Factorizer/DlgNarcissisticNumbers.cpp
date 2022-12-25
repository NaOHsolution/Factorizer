// DlgNarcissisticNumbers.cpp: 实现文件
//

#include "pch.h"
#include "Factorizer.h"
#include "DlgNarcissisticNumbers.h"
#include "afxdialogex.h"

enum indexNarcissisticNumbers {
	narcissisticNumbersTitle, textNumber, buttonTest, textResult, resultYes, resultNo
};

CString captionNarcissisticNumbers[10];

// DlgNarcissisticNumbers 对话框

IMPLEMENT_DYNAMIC(DlgNarcissisticNumbers, CDialogEx)

DlgNarcissisticNumbers::DlgNarcissisticNumbers(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_NARCISSISTICNUMBERS, pParent)
{

}

DlgNarcissisticNumbers::~DlgNarcissisticNumbers()
{
}

void DlgNarcissisticNumbers::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_1, m_edit1);
	DDX_Control(pDX, IDC_EDIT_2, m_edit2);
}


BEGIN_MESSAGE_MAP(DlgNarcissisticNumbers, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_1, &DlgNarcissisticNumbers::OnBnClickedButton1)
END_MESSAGE_MAP()


// DlgNarcissisticNumbers 消息处理程序


BOOL DlgNarcissisticNumbers::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	std::wfstream fs;
	std::wstring buf4;
	CString path = currentPath();
	bool buf2, buf3;
	int lang;

	fs.open(path + L"config.dll", std::ios::in);
	if (!fs.is_open()) {
		MessageBox(L"Configuration file not found.", L"Fatal Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		abort();
	}
	fs >> buf2 >> buf3 >> lang;
	fs.close();
	switch (lang) {
	case english:
		fs.open(path + L"lang\\english_narcissisticnumbers.lang", std::ios::in);
		SetDlgItemText(IDC_COMBO_1, L"English");
		break;
	case simplifiedChinese:
		std::locale simplifiedChinese("zh_CN.UTF-8");
		fs.imbue(simplifiedChinese);
		fs.open(path + L"lang\\simpchinese_narcissisticnumbers.lang", std::ios::in);
		SetDlgItemText(IDC_COMBO_1, L"简体中文");
		break;
	}
	if (!fs.is_open()) {
		MessageBox(L"Cannot open language file.", L"Fatal error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		abort();
	}
	for (int i = 0; i < 6; ++i) {
		std::getline(fs, buf4, L'\n');
		captionNarcissisticNumbers[i] = buf4.c_str();
	}
	fs.close();

	SetWindowText(captionNarcissisticNumbers[narcissisticNumbersTitle]);
	SetDlgItemText(IDC_STATIC_1, captionNarcissisticNumbers[textNumber]);
	SetDlgItemText(IDC_STATIC_2, captionNarcissisticNumbers[textResult]);
	SetDlgItemText(IDC_BUTTON_1, captionNarcissisticNumbers[buttonTest]);
	m_edit1.SetWindowText(L"153");
	m_edit1.SetLimitText(9);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void DlgNarcissisticNumbers::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	std::vector<ull> num;
	ull t, s = 0;
	int n;
	std::wstringstream buf1;
	wchar_t buf2[10];

	m_edit1.GetWindowText(buf2, 10);
	buf1 << buf2;
	buf1 >> t;
	num = separate(t, 10);
	n = num.size();
	for (std::vector<ull>::iterator itr = num.begin(); itr != num.end(); ++itr) s += power(*itr, n);
	if (s == t) m_edit2.SetWindowText(captionNarcissisticNumbers[resultYes]);
	else m_edit2.SetWindowText(captionNarcissisticNumbers[resultNo]);
}
