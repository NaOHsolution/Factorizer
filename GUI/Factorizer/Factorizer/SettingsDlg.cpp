// SettingsDlg.cpp: 实现文件
//

#include "pch.h"
#include "Factorizer.h"
#include "SettingsDlg.h"
#include "afxdialogex.h"

enum indexSettings {
	settingsTitle, groupComputation, checkMinimize, checkAlert, buttonConfirm, buttonCancel
};

CString captionSettings[50];

// SettingsDlg 对话框

IMPLEMENT_DYNAMIC(SettingsDlg, CDialogEx)

SettingsDlg::SettingsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETTINGS, pParent)
{

}

SettingsDlg::~SettingsDlg()
{
}

void SettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_1, m_check1);
	DDX_Control(pDX, IDC_CHECK_2, m_check2);
}


BEGIN_MESSAGE_MAP(SettingsDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &SettingsDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// SettingsDlg 消息处理程序


BOOL SettingsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	std::wfstream fs;
	std::wstring buf1;
	fs.open(L"config.dll", std::ios::in);
	if (!fs.is_open()) {
		MessageBox(L"Configuration file not found.", L"Fatal Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		abort();
	}
	fs >> minimize >> alert;

	if (minimize) m_check1.SetCheck(BST_CHECKED);
	if (alert) m_check2.SetCheck(BST_CHECKED);

	fs.close();
	fs.open(L"lang\\english_settings.lang", std::ios::in);
	if (!fs.is_open()) {
		MessageBox(L"Cannot open language file.", L"Fatal error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		abort();
	}
	for (int i = 0; i < 6; ++i) {
		if (fs.eof()) {
			MessageBox(L"Language file corrupted.", L"Fatal error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
			abort();
		}
		std::getline(fs, buf1);
		captionSettings[i] = buf1.c_str();
	}
	fs.close();

	SetWindowText(captionSettings[settingsTitle]);
	SetDlgItemText(IDC_STATIC_1, captionSettings[groupComputation]);
	SetDlgItemText(IDC_CHECK_1, captionSettings[checkMinimize]);
	SetDlgItemText(IDC_CHECK_2, captionSettings[checkAlert]);
	SetDlgItemText(IDOK, captionSettings[buttonConfirm]);
	SetDlgItemText(IDC_CANCEL, captionSettings[buttonCancel]);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void SettingsDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_check1.GetCheck() == BST_CHECKED) minimize = true;
	else minimize = false;
	if (m_check2.GetCheck() == BST_CHECKED) alert = true;
	else alert = false;
	std::wfstream fs;
	fs.open(L"config.dll", std::ios::out);
	fs << minimize << std::endl << alert << std::endl;
	fs.close();

	CDialogEx::OnOK();
}
