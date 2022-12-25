// DlgBaseConversion.cpp: 实现文件
//

#include "pch.h"
#include "Factorizer.h"
#include "DlgBaseConversion.h"
#include "afxdialogex.h"

enum indexBaseConversion {
	baseConversionTitle, textBaseF, textBaseB, textTo, buttonConvert
};

CString captionBaseConversion[10];

// DlgBaseConversion 对话框

IMPLEMENT_DYNAMIC(DlgBaseConversion, CDialogEx)

DlgBaseConversion::DlgBaseConversion(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BASECONVERSION, pParent)
{

}

DlgBaseConversion::~DlgBaseConversion()
{
}

void DlgBaseConversion::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_1, m_combo1);
	DDX_Control(pDX, IDC_COMBO_2, m_combo2);
	DDX_Control(pDX, IDC_EDIT_1, m_edit1);
	DDX_Control(pDX, IDC_EDIT_2, m_edit2);
}


BEGIN_MESSAGE_MAP(DlgBaseConversion, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_1, &DlgBaseConversion::OnBnClickedButton1)
END_MESSAGE_MAP()


// DlgBaseConversion 消息处理程序


BOOL DlgBaseConversion::OnInitDialog()
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
		fs.open(path + L"lang\\english_baseconversion.lang", std::ios::in);
		break;
	case simplifiedChinese:
		std::locale simplifiedChinese("zh_CN.UTF-8");
		fs.imbue(simplifiedChinese);
		fs.open(path + L"lang\\simpchinese_baseconversion.lang", std::ios::in);
		break;
	}
	if (!fs.is_open()) {
		MessageBox(L"Cannot open language file.", L"Fatal error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		abort();
	}
	for (int i = 0; i < 5; ++i) {
		std::getline(fs, buf1, L'\n');
		captionBaseConversion[i] = buf1.c_str();
	}
	fs.close();

	SetWindowText(captionBaseConversion[baseConversionTitle]);
	SetDlgItemText(IDC_STATIC_1, captionBaseConversion[textBaseF]);
	SetDlgItemText(IDC_STATIC_2, captionBaseConversion[textBaseB]);
	SetDlgItemText(IDC_STATIC_3, captionBaseConversion[textTo]);
	SetDlgItemText(IDC_STATIC_4, captionBaseConversion[textBaseF]);
	SetDlgItemText(IDC_STATIC_5, captionBaseConversion[textBaseB]);
	SetDlgItemText(IDC_BUTTON_1, captionBaseConversion[buttonConvert]);
	m_combo1.SetCurSel(2);
	m_combo2.SetCurSel(0);
	m_edit1.SetLimitText(10);
	m_edit1.SetWindowText(L"17");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void DlgBaseConversion::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}
