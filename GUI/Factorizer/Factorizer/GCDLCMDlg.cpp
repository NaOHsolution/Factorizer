// GCDLCMDlg.cpp: 实现文件
//

#include "pch.h"
#include "Factorizer.h"
#include "GCDLCMDlg.h"
#include "afxdialogex.h"

enum indexGCDLCM {
	GCDLCMTitle, textFirstNumber, textSecondNumber, buttonCompute, groupResult, textGCD, textLCM
};
CString captionGCDLCM[10];

// GCDLCMDlg 对话框

IMPLEMENT_DYNAMIC(GCDLCMDlg, CDialogEx)

GCDLCMDlg::GCDLCMDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GCDLCM, pParent)
{

}

GCDLCMDlg::~GCDLCMDlg()
{
}

void GCDLCMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT4, m_edit3);
	DDX_Control(pDX, IDC_EDIT5, m_edit4);
}


BEGIN_MESSAGE_MAP(GCDLCMDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_1, &GCDLCMDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// GCDLCMDlg 消息处理程序


BOOL GCDLCMDlg::OnInitDialog()
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
		MessageBox(L"Cannot open configuration file.", L"Fatal error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		abort();
	}
	fs >> buf2 >> buf3 >> lang;
	fs.close();
	switch (lang) {
	case english:
		fs.open(path + L"lang\\english_GCDLCM.lang", std::ios::in);
		break;
	case simplifiedChinese:
		std::locale simplifiedChinese("zh_CN.UTF-8");
		fs.imbue(simplifiedChinese);
		fs.open(path + L"lang\\simpchinese_GCDLCM.lang", std::ios::in);
		break;
	}
	if (!fs.is_open()) {
		MessageBox(L"Cannot open language file.", L"Fatal error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		abort();
	}
	for (int i = 0; i < 7; ++i) {
		std::getline(fs, buf1, L'\n');
		captionGCDLCM[i] = buf1.c_str();
	}
	SetWindowText(captionGCDLCM[GCDLCMTitle]);
	SetDlgItemText(IDC_STATIC_1, captionGCDLCM[textFirstNumber]);
	SetDlgItemText(IDC_STATIC_2, captionGCDLCM[textSecondNumber]);
	SetDlgItemText(IDC_STATIC_4, captionGCDLCM[textGCD]);
	SetDlgItemText(IDC_STATIC_5, captionGCDLCM[textLCM]);
	SetDlgItemText(IDC_STATIC_3, captionGCDLCM[groupResult]);
	SetDlgItemText(IDC_BUTTON_1, captionGCDLCM[buttonCompute]);
	m_edit1.SetLimitText(9);
	m_edit2.SetLimitText(9);
	m_edit1.SetWindowText(L"2");
	m_edit2.SetWindowText(L"8");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void GCDLCMDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	ull x, y, res;
	CString buf1;
	std::wstringstream buf2;
	wchar_t buf3[30];

	m_edit1.GetWindowText(buf1);
	buf2 << buf1.GetString() << L" ";
	m_edit2.GetWindowText(buf1);
	buf2 << buf1.GetString();
	buf2 >> x >> y;
	res = gcd(x, y);
	_ui64tow_s(res, buf3, 30, 10);
	m_edit3.SetWindowText(buf3);
	_ui64tow_s(x * y / res, buf3, 30, 10);
	m_edit4.SetWindowText(buf3);
}
