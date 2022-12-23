// SettingsDlg.cpp: 实现文件
//

#include "pch.h"
#include "Factorizer.h"
#include "SettingsDlg.h"
#include "afxdialogex.h"


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
	std::fstream fs;
	fs.open(L"config.dll", std::ios::in);
	if (!fs.is_open()) {
		MessageBox(L"Configuration file not found.", L"Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		return FALSE;
	}
	fs >> minimize >> alert;

	if (minimize) m_check1.SetCheck(BST_CHECKED);
	if (alert) m_check2.SetCheck(BST_CHECKED);

	fs.close();
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
