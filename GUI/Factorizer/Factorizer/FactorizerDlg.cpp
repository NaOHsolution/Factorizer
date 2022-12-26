
// FactorizerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Factorizer.h"
#include "FactorizerDlg.h"
#include "SettingsDlg.h"
#include "GCDLCMDlg.h"
#include "DlgNarcissisticNumbers.h"
#include "DlgPerfectNumbers.h"
#include "DlgBaseConversion.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

threadInfo Info;

enum indexFactorizer {
	factorizerTitle, inputGroup, radioDirect, radioExternal, groupType, radioPrime, radioAll, buttonStart, groupResult, 
	listColumnNumber, listColumnResult, listColumnDetail, listPrime, listComposite, textOutput, buttonOutput, statusStatus, 
	statusReady, statusComputation, statusReading, statusWriting, boxWarning, boxNumberError, boxFileError, boxNotANumber, 
	boxZero, boxOutOfRange, boxInputEmpty, boxInputFileEmpty, boxInputFileNotFound, boxOutputFileNotFound, boxComplete,
	boxOutputComplete, boxOutputEmpty, menuTools, menuCommandLine, menuCalculator, menuOptions, menuOptions2, menuAbout,
	menuGCDLCM, menuBaseConversion, menuNarcissisticNumbers, menuPerfectNumbers, statusToolsRunning, boxNoExternalPrimeLibrary
};
enum indexAbout {
	aboutTitle, line1, line2, buttonOK
};


CString caption[60];
CString captionAbout[10];

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CFactorizerDlg 对话框



CFactorizerDlg::CFactorizerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FACTORIZER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFactorizerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_1, m_progress1);
	DDX_Control(pDX, IDC_LIST_1, m_list1);
	DDX_Control(pDX, IDC_RADIO_1, m_radio1);
	DDX_Control(pDX, IDC_RADIO_2, m_radio2);
	DDX_Control(pDX, IDC_RADIO_3, m_radio3);
	DDX_Control(pDX, IDC_EDIT_1, m_edit1);
	DDX_Control(pDX, IDC_MFCEDITBROWSE_1, m_browse1);
	DDX_Control(pDX, IDC_MFCEDITBROWSE_2, m_browse2);
	DDX_Control(pDX, IDC_BUTTON_2, m_button2);
	DDX_Control(pDX, IDC_BUTTON_1, m_button1);
}

BEGIN_MESSAGE_MAP(CFactorizerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_1, &CFactorizerDlg::OnBnClickedButton1)
	ON_COMMAND(ID_ABOUT_ABOUT, &CFactorizerDlg::OnAboutAbout)
	ON_BN_CLICKED(IDC_RADIO_1, &CFactorizerDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO_2, &CFactorizerDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON_2, &CFactorizerDlg::OnBnClickedButton2)
	ON_COMMAND(ID_TOOLS_CALCULATOR, &CFactorizerDlg::OnToolsCalculator)
	ON_COMMAND(ID_OPTIONS_OPTIONS, &CFactorizerDlg::OnOptionsOptions)
	ON_COMMAND(ID_OPTIONS_ABOUT, &CFactorizerDlg::OnOptionsAbout)
	ON_COMMAND(ID_TOOLS_OPENINCOMMANDPROMPT, &CFactorizerDlg::OnToolsOpenincommandprompt)
	ON_COMMAND(ID_TOOLS_GCDLC, &CFactorizerDlg::OnToolsGcdlc)
	ON_COMMAND(ID_TOOLS_NARCISSISTICNUMBERS32784, &CFactorizerDlg::OnToolsNarcissisticnumbers32784)
	ON_COMMAND(ID_TOOLS_PERFECTNUMBERS32783, &CFactorizerDlg::OnToolsPerfectnumbers32783)
	ON_COMMAND(ID_TOOLS_BASECONVERSION, &CFactorizerDlg::OnToolsBaseconversion)
END_MESSAGE_MAP()


// CFactorizerDlg 消息处理程序

BOOL CFactorizerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	UINT nID[] = { 1, 2, 3 };
	CRect rect = { 0 };
	std::wfstream fs;
	std::wstring buf1;
	CMenu* menu;
	CMenu* subMenu;
	CString path = currentPath();

	fs.imbue(std::locale("zh_CN.UTF-8"));
	fs.open(path + L"config.dll", std::ios::in);
	if (!fs.is_open()) {
		MessageBox(L"Cannot open configuration file.", L"Fatal error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		abort();
	}
	fs >> minimizeWhenComputing >> alertWhenDone >> lang >> useExternal;
	if (useExternal) fs >> externalPath;
	fs.close();

	switch (lang) {
	case english:
		fs.open(path + L"lang\\english_factorizer.lang", std::ios::in);
		break;
	case simplifiedChinese:
		std::locale simplifiedChinese("zh_CN.UTF-8");
		fs.imbue(simplifiedChinese);
		fs.open(path + L"lang\\simpchinese_factorizer.lang", std::ios::in);
		break;
	}
	if (!fs.is_open()) {
		MessageBox(L"Cannot open language file.", L"Fatal error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		abort();
	}
	if (!fs.is_open()) {
		MessageBox(L"Cannot open language file.", L"Fatal error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		abort();
	}
	for (int i = 0; i < 46; ++i) {
		std::getline(fs, buf1, L'\n');
		caption[i] = buf1.c_str();
	}
	fs.close();

	m_progress1.SetRange(0, 99);
	m_radio1.SetCheck(BST_CHECKED);
	m_radio3.SetCheck(BST_CHECKED);
	m_list1.SetView(LVS_REPORT);
	m_list1.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_list1.InsertColumn(0, L"ID", LVS_ALIGNLEFT, 30);
	m_list1.InsertColumn(1, caption[listColumnNumber], LVS_ALIGNLEFT, 150);
	m_list1.InsertColumn(2, caption[listColumnResult], LVS_ALIGNLEFT, 100);
	m_list1.InsertColumn(3, caption[listColumnDetail], LVS_ALIGNLEFT, 2500);
	SetDlgItemText(IDC_STATIC_1, caption[inputGroup]);
	SetDlgItemText(IDC_STATIC_2, caption[groupType]);
	SetDlgItemText(IDC_STATIC_3, caption[groupResult]);
	SetDlgItemText(IDC_STATIC_6, caption[textOutput]);
	SetDlgItemText(IDC_RADIO_1, caption[radioDirect]);
	SetDlgItemText(IDC_RADIO_2, caption[radioExternal]);
	SetDlgItemText(IDC_RADIO_3, caption[radioPrime]);
	SetDlgItemText(IDC_RADIO_4, caption[radioAll]);
	SetDlgItemText(IDC_BUTTON_1, caption[buttonStart]);
	SetDlgItemText(IDC_BUTTON_2, caption[buttonOutput]);
	SetWindowText(caption[factorizerTitle]);
	m_edit1.SetLimitText(30);
	m_edit1.SetWindowText(L"2");

	menu = AfxGetApp()->m_pMainWnd->GetMenu();
	menu->ModifyMenu(0, MF_BYPOSITION, ID_FILE_SAVE, caption[menuTools]);
	menu->ModifyMenu(1, MF_BYPOSITION, ID_FILE_SAVE, caption[menuOptions]);
	subMenu = menu->GetSubMenu(0);
	subMenu->ModifyMenu(0, MF_BYPOSITION, ID_TOOLS_OPENINCOMMANDPROMPT, caption[menuCommandLine]);
	subMenu->ModifyMenu(1, MF_BYPOSITION, ID_TOOLS_CALCULATOR, caption[menuCalculator]);
	subMenu->ModifyMenu(3, MF_BYPOSITION, ID_TOOLS_GCDLC, caption[menuGCDLCM]);
	subMenu->ModifyMenu(4, MF_BYPOSITION, ID_TOOLS_BASECONVERSION, caption[menuBaseConversion]);
	subMenu->ModifyMenu(5, MF_BYPOSITION, ID_TOOLS_NARCISSISTICNUMBERS32784, caption[menuNarcissisticNumbers]);
	subMenu->ModifyMenu(6, MF_BYPOSITION, ID_TOOLS_PERFECTNUMBERS32783, caption[menuPerfectNumbers]);
	subMenu = menu->GetSubMenu(1);
	subMenu->ModifyMenu(0, MF_BYPOSITION, ID_OPTIONS_OPTIONS, caption[menuOptions2]);
	subMenu->ModifyMenu(2, MF_BYPOSITION, ID_OPTIONS_ABOUT, caption[menuAbout]);

	m_status.Create(this);
	m_status.SetIndicators(nID, 3);
	m_status.SetPaneInfo(0, 0, SBPS_NORMAL, 75);
	m_status.SetPaneInfo(1, 1, SBPS_NORMAL, 175);
	m_status.SetPaneInfo(2, 2, SBPS_NORMAL, 175);
	GetClientRect(&rect);
	m_status.MoveWindow(0, rect.bottom - 30, rect.right, 30);
	
	m_status.SetPaneText(0, caption[statusStatus]);
	m_status.SetPaneText(1, caption[statusReady]);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFactorizerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFactorizerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFactorizerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFactorizerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_button1.EnableWindow(false);
	m_button2.EnableWindow(false);
	Info.numbers.clear();

	std::wstringstream buf1;
	std::wstring buf3;
	std::wfstream fs;
	CString buf2;
	ull t;
	
	buf1.str(L"");
	UpdateData(false);
	Info.progress = &m_progress1;
	Info.list = &m_list1;
	Info.button1 = &m_button1;
	Info.button2 = &m_button2;
	Info.main = m_hWnd;
	Info.status = &m_status;
	Info.minimize = minimizeWhenComputing;
	Info.alert = alertWhenDone;
	Info.external = useExternal;
	if (useExternal) {
		Info.path = externalPath;
		fs.open(externalPath, std::ios::in);
		if (!fs.is_open()) {
			MessageBox(caption[boxNoExternalPrimeLibrary], caption[boxFileError], MB_ICONWARNING | MB_OK | MB_APPLMODAL);
			Info.external = false;
		}
		else fs.close();
	}
	m_progress1.SetRange(0, 100);

	if (m_radio1.GetCheck() == BST_CHECKED) {
		m_edit1.GetWindowText(buf2);
		buf3 = buf2.GetString();
		if (buf3.empty()) {
			m_button1.EnableWindow(true);
			m_button2.EnableWindow(true);
			MessageBox(caption[boxInputEmpty], caption[boxNumberError], MB_OK | MB_APPLMODAL | MB_ICONERROR);
			return;
		}
		while (!buf3.empty() && buf3.front() == L' ') buf3.erase(0, 1);
		while (!buf3.empty() && buf3.back() == L' ') buf3.erase(buf3.size() - 1, 1);
		for (int i = 0; i < buf3.size(); ++i) {
			if (buf3[i] < L'0' || buf3[i] > L'9') {
				m_button1.EnableWindow(true);
				m_button2.EnableWindow(true);
				MessageBox(caption[boxNotANumber], caption[boxNumberError], MB_OK | MB_APPLMODAL | MB_ICONERROR);
				return;
			}
		}
		buf1 << buf2.GetString();
		buf1 >> t;
		if (t == 0ull) {
			m_button1.EnableWindow(true);
			m_button2.EnableWindow(true);
			MessageBox(caption[boxZero], caption[boxNumberError], MB_OK | MB_APPLMODAL | MB_ICONERROR);
			return;
		}
		if (buf1.fail()) {
			m_button1.EnableWindow(true);
			m_button2.EnableWindow(true);
			MessageBox(caption[boxOutOfRange], caption[boxNumberError], MB_OK | MB_APPLMODAL | MB_ICONERROR);
			return;
		}
		Info.numbers.push_back(t);
	}
	else {
		m_status.SetPaneText(1, caption[statusReading]);
		m_browse1.GetWindowText(buf2);
		fs.open(buf2.GetString(), std::ios::in);
		if (!fs.is_open()) {
			m_button1.EnableWindow(true);
			m_button2.EnableWindow(true);
			m_status.SetPaneText(1, caption[statusReady]);
			MessageBox(caption[boxInputFileNotFound], caption[boxFileError], MB_OK | MB_APPLMODAL | MB_ICONERROR);
			return;
		}
		while (!fs.eof()) {
			buf1.clear();
			buf1.str(L"");
			fs >> buf3;
			buf1 << buf3;
			buf1 >> t;
			if (!buf1.fail()) Info.numbers.push_back(t);
		}
		fs.close();
		if (Info.numbers.empty()) {
			m_button1.EnableWindow(true);
			m_button2.EnableWindow(true);
			m_status.SetPaneText(1, caption[statusReady]);
			MessageBox(caption[boxInputFileEmpty], caption[boxWarning], MB_OK | MB_APPLMODAL | MB_ICONWARNING);
			return;
		}
		m_status.SetPaneText(1, caption[statusReady]);
	}
	if (m_radio3.GetCheck() == BST_CHECKED) Info.type = PRIME_FACTORS;
	else Info.type = ALL_FACTORS;

	UpdateData(true);
	m_list1.DeleteAllItems();
	pThread = AfxBeginThread(threadFunc, &Info);
}

UINT threadFunc(LPVOID lpParam) {
	threadInfo* pInfo = (threadInfo*)lpParam;
	std::vector<std::pair<ull, short>> resultp;
	std::vector<ull> resultf;
	std::wstringstream wss;
	wchar_t buf1[50];
	int id = 1;

	pInfo->progress->SetPos(0);
	pInfo->status->SetPaneText(1, caption[statusComputation]);
	if (pInfo->minimize) ShowWindow(pInfo->main, SW_MINIMIZE);
	if (pInfo->type == PRIME_FACTORS) {
		for (std::vector<ull>::iterator itr0 = pInfo->numbers.begin(); itr0 != pInfo->numbers.end(); ++itr0, ++id) {
			resultp.clear();
			wss.clear();
			wss.str(L"");
			resultp = factorize(*itr0, pInfo->external, pInfo->path);

			for (std::vector<std::pair<ull, short>>::iterator itr = resultp.begin(); itr != resultp.end(); ++itr) {
				wss << itr->first;
				if (itr->second != 1) wss << "^" << itr->second;
				if (itr + 1 != resultp.end()) wss << " x ";
			}
			_ui64tow_s(id, buf1, 50, 10);
			pInfo->list->InsertItem(id, buf1);
			_ui64tow_s(*itr0, buf1, 50, 10);
			pInfo->list->SetItemText(id - 1, 1, buf1);
			if (*itr0 == 1) pInfo->list->SetItemText(id - 1, 2, L"-");
			else if (resultp.size() == 1 && resultp.begin()->second == 1) pInfo->list->SetItemText(id - 1, 2, caption[listPrime]);
			else pInfo->list->SetItemText(id - 1, 2, caption[listComposite]);
			if (*itr0 == 1) pInfo->list->SetItemText(id - 1, 3, L"-");
			else pInfo->list->SetItemText(id - 1, 3, wss.str().c_str());

			pInfo->progress->SetPos(id * 100 / pInfo->numbers.size());
		}
	}
	else if (pInfo->type == ALL_FACTORS) {
		for (std::vector<ull>::iterator itr0 = pInfo->numbers.begin(); itr0 != pInfo->numbers.end(); ++itr0, ++id) {
			resultf.clear();
			wss.clear();
			wss.str(L"");
			resultf = factors(*itr0);

			for (std::vector<ull>::iterator itr = resultf.begin(); itr != resultf.end(); ++itr) {
				wss << *itr;
				if (itr + 1 != resultf.end()) wss << ", ";
			}
			_ui64tow_s(id, buf1, 50, 10);
			pInfo->list->InsertItem(id - 1, buf1);
			_ui64tow_s(*itr0, buf1, 50, 10);
			pInfo->list->SetItemText(id - 1, 1, buf1);
			if (*itr0 == 1) pInfo->list->SetItemText(id - 1, 2, L"-");
			else if (resultf.size() == 2) pInfo->list->SetItemText(id - 1, 2, caption[listPrime]);
			else pInfo->list->SetItemText(id - 1, 2, caption[listComposite]);
			pInfo->list->SetItemText(id - 1, 3, wss.str().c_str());

			pInfo->progress->SetPos(id * 100 / pInfo->numbers.size());
		}
	}

	if (pInfo->minimize) ShowWindow(pInfo->main, SW_NORMAL);
	pInfo->progress->SetState(100);
	pInfo->button1->EnableWindow(true);
	pInfo->button2->EnableWindow(true);
	pInfo->status->SetPaneText(1, caption[statusReady]);

	if (pInfo->alert) MessageBox(pInfo->main, caption[boxComplete], caption[factorizerTitle], MB_OK | MB_APPLMODAL | MB_ICONINFORMATION);
	return 0;
}

void CAboutDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CFactorizerDlg::OnAboutAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg dlg;
	dlg.DoModal();
}


void CFactorizerDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_edit1.EnableWindow(true);
	m_browse1.EnableWindow(false);
}


void CFactorizerDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_edit1.EnableWindow(false);
	m_browse1.EnableWindow(true);
}


void CFactorizerDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	std::wstringstream wss;
	std::wfstream fs;
	CString buf1;

	m_button1.EnableWindow(false);
	m_button2.EnableWindow(false);
	m_status.SetPaneText(1, caption[statusWriting]);

	m_browse2.GetWindowText(buf1);
	if (lang == simplifiedChinese) fs.imbue(std::locale("zh_CN.UTF-8"));
	fs.open(buf1.GetString(), std::ios::out);
	if (!fs.is_open()) {
		m_button1.EnableWindow(true);
		m_button2.EnableWindow(true);
		m_status.SetPaneText(1, caption[statusReady]);
		MessageBox(caption[boxOutputFileNotFound], caption[boxFileError], MB_OK | MB_APPLMODAL | MB_ICONERROR);
		return;
	}
	if (m_list1.GetItemCount() == 0) {
		m_button1.EnableWindow(true);
		m_button2.EnableWindow(true);
		m_status.SetPaneText(1, caption[statusReady]);
		MessageBox(caption[boxOutputEmpty], caption[boxWarning], MB_OK | MB_APPLMODAL | MB_ICONWARNING);
		return;
	}

	for (int i = 0; i < m_list1.GetItemCount(); ++i) {
		fs << m_list1.GetItemText(i, 1).GetString() << L" (" << m_list1.GetItemText(i, 2).GetString() << L"): " << m_list1.GetItemText(i, 3).GetString() << std::endl;
	}
	fs << std::endl;

	m_button1.EnableWindow(true);
	m_button2.EnableWindow(true);
	fs.close();
	m_status.SetPaneText(1, caption[statusReady]);
	MessageBox(caption[boxOutputComplete], caption[factorizerTitle], MB_OK | MB_APPLMODAL | MB_ICONINFORMATION);
}


void CFactorizerDlg::OnToolsCalculator()
{
	// TODO: 在此添加命令处理程序代码
	system("calc");
}


void CFactorizerDlg::OnOptionsOptions()
{
	// TODO: 在此添加命令处理程序代码
	SettingsDlg dlg;
	m_status.SetPaneText(2, caption[statusToolsRunning]);
	dlg.DoModal();
	m_status.SetPaneText(2, L"");
}


void CFactorizerDlg::OnOptionsAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg dlg;
	m_status.SetPaneText(2, caption[statusToolsRunning]);
	dlg.DoModal();
	m_status.SetPaneText(2, L"");
}


void CFactorizerDlg::OnToolsOpenincommandprompt()
{
	// TODO: 在此添加命令处理程序代码
	system(currentPath() + ".\\cmdFactorizer.exe");
}


BOOL CAboutDlg::OnInitDialog()
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
		fs.open(path + L"lang\\english_about.lang", std::ios::in);
		break;
	case simplifiedChinese:
		std::locale simplifiedChinese("zh_CN.UTF-8");
		fs.imbue(simplifiedChinese);
		fs.open(path + L"lang\\simpchinese_about.lang", std::ios::in);
		break;
	}
	if (!fs.is_open()) {
		MessageBox(L"Cannot open language file.", L"Fatal error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		abort();
	}
	for (int i = 0; i < 4; ++i) {
		std::getline(fs, buf1, L'\n');
		captionAbout[i] = buf1.c_str();
	}
	fs.close();
	SetWindowText(captionAbout[aboutTitle]);
	SetDlgItemText(IDC_STATIC_4, captionAbout[line1]);
	SetDlgItemText(IDC_STATIC_5, captionAbout[line2]);
	SetDlgItemText(IDOK, captionAbout[buttonOK]);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CFactorizerDlg::OnToolsGcdlc()
{
	// TODO: 在此添加命令处理程序代码
	GCDLCMDlg dlg;
	m_status.SetPaneText(2, caption[statusToolsRunning]);
	dlg.DoModal();
	m_status.SetPaneText(2, L"");
}


void CFactorizerDlg::OnToolsNarcissisticnumbers32784()
{
	// TODO: 在此添加命令处理程序代码
	DlgNarcissisticNumbers dlg;
	m_status.SetPaneText(2, caption[statusToolsRunning]);
	dlg.DoModal();
	m_status.SetPaneText(2, L"");
}


void CFactorizerDlg::OnToolsPerfectnumbers32783()
{
	// TODO: 在此添加命令处理程序代码
	DlgPerfectNumbers dlg;
	m_status.SetPaneText(2, caption[statusToolsRunning]);
	dlg.DoModal();
	m_status.SetPaneText(2, L"");
}


void CFactorizerDlg::OnToolsBaseconversion()
{
	// TODO: 在此添加命令处理程序代码
	DlgBaseConversion dlg;
	m_status.SetPaneText(2, caption[statusToolsRunning]);
	dlg.DoModal();
	m_status.SetPaneText(2, L"");
}
