// SettingsDlg.cpp: 实现文件
//

#include "pch.h"
#include "Factorizer.h"
#include "SettingsDlg.h"
#include "afxdialogex.h"

enum indexSettings {
	settingsTitle, groupComputation, checkMinimize, checkAlert, buttonConfirm, buttonCancel, groupAppearance, textLanguage,
	hintLanguage, checkUseExternal, boxError, boxCannotOpenExternalFile
};

CString captionSettings[20];

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
	DDX_Control(pDX, IDC_COMBO_1, m_combo1);
	DDX_Control(pDX, IDC_CHECK_3, m_check3);
	DDX_Control(pDX, IDC_MFCEDITBROWSE_1, m_browse1);
}


BEGIN_MESSAGE_MAP(SettingsDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &SettingsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CANCEL, &SettingsDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK_3, &SettingsDlg::OnBnClickedCheck3)
END_MESSAGE_MAP()


// SettingsDlg 消息处理程序


BOOL SettingsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	std::wfstream fs;
	std::wstring buf1;
	CString path = currentPath();

	fs.open(path + L"config.dll", std::ios::in);
	if (!fs.is_open()) {
		MessageBox(L"Cannot open configuration file.", L"Fatal Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		abort();
	}
	fs >> minimize >> alert >> lang >> useExternal;
	if (useExternal) {
		fs.imbue(std::locale("zh_CN.UTF-8"));
		fs >> externalPath;
	}
	fs.close();
	
	if (minimize) m_check1.SetCheck(BST_CHECKED);
	if (alert) m_check2.SetCheck(BST_CHECKED);
	if (useExternal) {
		m_check3.SetCheck(BST_CHECKED);
		m_browse1.SetWindowText(externalPath.c_str());
	}
	else m_browse1.EnableWindow(false);
	
	switch (lang) {
	case english:
		fs.open(path + L"lang\\english_settings.lang", std::ios::in);
		m_combo1.SetCurSel(english);
		break;
	case simplifiedChinese:
		std::locale simplifiedChinese("zh_CN.UTF-8");
		fs.imbue(simplifiedChinese);
		fs.open(path + L"lang\\simpchinese_settings.lang", std::ios::in);
		m_combo1.SetCurSel(languages::simplifiedChinese);
		break;
	}
	if (!fs.is_open()) {
		MessageBox(L"Cannot open language file.", L"Fatal error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		abort();
	}
	for (int i = 0; i < 12; ++i) {
		std::getline(fs, buf1, L'\n');
		captionSettings[i] = buf1.c_str();
	}
	fs.close();

	SetWindowText(captionSettings[settingsTitle]);
	SetDlgItemText(IDC_STATIC_1, captionSettings[groupComputation]);
	SetDlgItemText(IDC_CHECK_1, captionSettings[checkMinimize]);
	SetDlgItemText(IDC_CHECK_2, captionSettings[checkAlert]);
	SetDlgItemText(IDOK, captionSettings[buttonConfirm]);
	SetDlgItemText(IDC_CANCEL, captionSettings[buttonCancel]);
	SetDlgItemText(IDC_STATIC_2, captionSettings[groupAppearance]);
	SetDlgItemText(IDC_STATIC_3, captionSettings[textLanguage]);
	SetDlgItemText(IDC_STATIC_4, captionSettings[hintLanguage]);
	SetDlgItemText(IDC_CHECK_3, captionSettings[checkUseExternal]);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void SettingsDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	std::wfstream fs;
	FILE* f;
	CString buf1;
	CString path = currentPath();

	if (m_check1.GetCheck() == BST_CHECKED) minimize = true;
	else minimize = false;
	if (m_check2.GetCheck() == BST_CHECKED) alert = true;
	else alert = false;
	if (m_check3.GetCheck() == BST_CHECKED) {
		useExternal = true;
		m_browse1.GetWindowText(buf1);
		externalPath = buf1.GetString();
	}
	else useExternal = false;
	switch (m_combo1.GetCurSel()) {
	case english:
		lang = english;
		break;
	case simplifiedChinese:
		lang = simplifiedChinese;
		break;
	}
	if (useExternal) {
		fs.open(externalPath, std::ios::in);
		if (!fs.is_open()) {
			MessageBox(captionSettings[boxCannotOpenExternalFile], captionSettings[boxError], MB_OK | MB_ICONERROR | MB_APPLMODAL);
			fs.close();
			return;
		}
		fs.close();
	}

	fs.open((path + L"config.dll"), std::ios::out);
	fs << minimize << std::endl << alert << std::endl << lang << std::endl << useExternal << std::endl;
	if (useExternal) {
		fs.imbue(std::locale("zh_CN.UTF-8"));
		fs << externalPath << std::endl;
	}
	fs.close();

	CDialogEx::OnOK();
}


void SettingsDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void SettingsDlg::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_check3.GetCheck() == BST_CHECKED) m_browse1.EnableWindow(true);
	else m_browse1.EnableWindow(false);
}
