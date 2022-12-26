// DlgBaseConversion.cpp: 实现文件
//

#include "pch.h"
#include "Factorizer.h"
#include "DlgBaseConversion.h"
#include "afxdialogex.h"

enum indexBaseConversion {
	baseConversionTitle, textBaseF, textBaseB, textTo, buttonConvert, boxError, boxInvalidSymbol
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
	ON_CBN_SELCHANGE(IDC_COMBO_1, &DlgBaseConversion::OnCbnSelchangeCombo1)
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
		MessageBox(L"Cannot open configuration file.", L"Fatal Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
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
	for (int i = 0; i < 7; ++i) {
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
	m_combo1.SetCurSel(8);
	m_combo2.SetCurSel(0);
	m_edit1.SetLimitText(19);
	m_edit1.SetWindowText(L"17");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void DlgBaseConversion::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString buf1;
	std::vector<ull> number, result;
	std::wstring buf2, buf3;
	int from = m_combo1.GetCurSel() + 2, to = m_combo2.GetCurSel() + 2;

	m_edit1.GetWindowText(buf1);
	buf3 = buf1.GetString();
	for (int i = 0; i < buf3.size(); ++i) {
		if (buf3[i] >= L'0' && buf3[i] <= L'9') {
			if (buf3[i] - L'0' > from) {
				MessageBox(captionBaseConversion[boxInvalidSymbol], captionBaseConversion[boxError], MB_OK | MB_ICONERROR | MB_APPLMODAL);
				return;
			}
			number.push_back(ull(buf3[i] - L'0'));
		}
		else if (buf3[i] >= L'a' && buf3[i] <= L'z') {
			if (buf3[i] - L'a' + 10 > from) {
				MessageBox(captionBaseConversion[boxInvalidSymbol], captionBaseConversion[boxError], MB_OK | MB_ICONERROR | MB_APPLMODAL);
				return;
			}
			number.push_back(ull(buf3[i] - L'a' + 10));
		}
		else {
			MessageBox(captionBaseConversion[boxInvalidSymbol], captionBaseConversion[boxError], MB_OK | MB_ICONERROR | MB_APPLMODAL);
			return;
		}
	}
	result = convert(number, from, to);
	for (std::vector<ull>::iterator itr = result.begin(); itr != result.end(); ++itr) {
		if (*itr < 10ull) buf2 += (wchar_t(*itr) + L'0');
		else if (10ull <= *itr < 36ull) buf2 += (wchar_t(*itr - 10) + L'a');
	}
	m_edit2.SetWindowText(buf2.c_str());
}


void DlgBaseConversion::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int r = m_combo1.GetCurSel() + 2;
	CString buf1, buf2;
	int len = int(64 * log(2) / log(r));
	m_edit1.GetWindowText(buf1);
	if (buf1.GetLength() > len) {
		for (int i = 0; i < len; ++i) buf2.AppendChar(buf1[i]);
	}
	else buf2 = buf1;
	m_edit1.SetWindowText(buf2);
	m_edit1.SetLimitText(len);
}
