
// FactorizerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Factorizer.h"
#include "FactorizerDlg.h"
#include "afxdialogex.h"
#include "SettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

threadInfo Info;

ull primes[100] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

std::vector<std::pair<ull, short>> factorize(ull t) {
	std::vector<std::pair<ull, short>> res;
	std::wstring buf;
	short cnt = 0;

	for (int i = 0; i < 25; ++i) {
		ull p = primes[i];
		if (t % p == 0) {
			cnt = 0;
			while (t % p == 0) t /= p, ++cnt;
			res.push_back(std::pair<ull, short>(p, cnt));
		}
		if (t == 1) return res;
	}
	ull f = 102, dest = t / 97;
	while (f - 1 <= dest) {
		if (t % (f - 1) == 0) {
			cnt = 0;
			while (t % (f - 1) == 0) t /= (f - 1), ++cnt;
			res.push_back(std::pair<ull, short>(f - 1, cnt));
			dest = t / (f - 1);
		}
		if (t % (f + 1) == 0) {
			cnt = 0;
			while (t % (f + 1) == 0) t /= (f + 1), ++cnt;
			res.push_back(std::pair<ull, short>(f + 1, cnt));
			dest = t / (f + 1);
		}

		f += 6;
	}

	if (t != 1) res.push_back(std::pair<ull, short>(t, 1));
	return res;
}

std::vector<ull> factors(ull t) {
	std::vector<ull> res;

	for (ull i = 1; i <= sqrt(t); ++i) {
		if (t % i == 0) {
			res.push_back(i);
			if (i * i != t) res.push_back(t / i);
		}
	}
	std::sort(res.begin(), res.end());

	return res;
}

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
	fs.open(L"config.dll", std::ios::in);
	if (!fs.is_open()) {
		MessageBox(L"Configuration file not found.", L"Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		return FALSE;
	}
	fs >> minimizeWhenComputing >> alertWhenDone;
	fs.close();

	m_progress1.SetRange(0, 99);
	m_radio1.SetCheck(BST_CHECKED);
	m_radio3.SetCheck(BST_CHECKED);
	m_list1.SetView(LVS_REPORT);
	m_list1.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_list1.InsertColumn(0, L"ID", LVS_ALIGNLEFT, 30);
	m_list1.InsertColumn(1, L"Number", LVS_ALIGNLEFT, 150);
	m_list1.InsertColumn(2, L"Result", LVS_ALIGNLEFT, 80);
	m_list1.InsertColumn(3, L"Detail", LVS_ALIGNLEFT, 2500);

	m_status.Create(this);
	m_status.SetIndicators(nID, 3);
	m_status.SetPaneInfo(0, 0, SBPS_NORMAL, 100);
	m_status.SetPaneInfo(1, 1, SBPS_NORMAL, 100);
	m_status.SetPaneInfo(2, 2, SBPS_NORMAL, 250);
	GetClientRect(&rect);
	m_status.MoveWindow(0, rect.bottom - 30, rect.right, 30);
	
	m_status.SetPaneText(0, L"Status");
	m_status.SetPaneText(1, L"Ready.");

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
	m_progress1.SetRange(0, 100);

	if (m_radio1.GetCheck() == BST_CHECKED) {
		m_edit1.GetWindowText(buf2);
		buf3 = buf2.GetString();
		if (buf3.empty()) {
			m_button1.EnableWindow(true);
			m_button2.EnableWindow(true);
			MessageBox(L"Please enter a number.", L"Number error", MB_OK | MB_APPLMODAL | MB_ICONERROR);
			return;
		}
		while (!buf3.empty() && buf3.front() == L' ') buf3.erase(0, 1);
		while (!buf3.empty() && buf3.back() == L' ') buf3.erase(buf3.size() - 1, 1);
		for (int i = 0; i < buf3.size(); ++i) {
			if (buf3[i] < L'0' || buf3[i] > L'9') {
				m_button1.EnableWindow(true);
				m_button2.EnableWindow(true);
				MessageBox(L"Please enter a number.", L"Number error", MB_OK | MB_APPLMODAL | MB_ICONERROR);
				return;
			}
		}
		buf1 << buf2.GetString();
		buf1 >> t;
		if (t == 0ull) {
			m_button1.EnableWindow(true);
			m_button2.EnableWindow(true);
			MessageBox(L"Please enter a positive whole number.", L"Number error", MB_OK | MB_APPLMODAL | MB_ICONERROR);
			return;
		}
		if (buf1.fail()) {
			m_button1.EnableWindow(true);
			m_button2.EnableWindow(true);
			MessageBox(L"Please enter a number less than 18,446,744,073,709,551,616.", L"Number error", MB_OK | MB_APPLMODAL | MB_ICONERROR);
			return;
		}
		Info.numbers.push_back(t);
	}
	else {
		m_status.SetPaneText(1, L"Reading file...");
		m_browse1.GetWindowText(buf2);
		fs.open(buf2.GetString(), std::ios::in);
		if (!fs.is_open()) {
			m_button1.EnableWindow(true);
			m_button2.EnableWindow(true);
			m_status.SetPaneText(1, L"Ready.");
			MessageBox(L"Cannot open external file.", L"File error", MB_OK | MB_APPLMODAL | MB_ICONERROR);
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
			m_status.SetPaneText(1, L"Ready.");
			MessageBox(L"The external file contains no numbers within range.", L"Warning", MB_OK | MB_APPLMODAL | MB_ICONWARNING);
			return;
		}
		m_status.SetPaneText(1, L"Ready.");
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
	pInfo->status->SetPaneText(1, L"Computing...");
	if (pInfo->minimize) ShowWindow(pInfo->main, SW_MINIMIZE);
	if (pInfo->type == PRIME_FACTORS) {
		for (std::vector<ull>::iterator itr0 = pInfo->numbers.begin(); itr0 != pInfo->numbers.end(); ++itr0, ++id) {
			resultp.clear();
			wss.clear();
			wss.str(L"");
			resultp = factorize(*itr0);

			for (std::vector<std::pair<ull, short>>::iterator itr = resultp.begin(); itr != resultp.end(); ++itr) {
				wss << itr->first;
				if (itr->second != 1) wss << "^" << itr->second;
				if (itr + 1 != resultp.end()) wss << " x ";
			}
			_i64tow_s(id, buf1, 50, 10);
			pInfo->list->InsertItem(id, buf1);
			_i64tow_s(*itr0, buf1, 50, 10);
			pInfo->list->SetItemText(id - 1, 1, buf1);
			if (*itr0 == 1) pInfo->list->SetItemText(id - 1, 2, L"-");
			else if (resultp.size() == 1 && resultp.begin()->second == 1) pInfo->list->SetItemText(id - 1, 2, L"Prime");
			else pInfo->list->SetItemText(id - 1, 2, L"Composite");
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
			_i64tow_s(id, buf1, 50, 10);
			pInfo->list->InsertItem(id - 1, buf1);
			_i64tow_s(*itr0, buf1, 50, 10);
			pInfo->list->SetItemText(id - 1, 1, buf1);
			if (*itr0 == 1) pInfo->list->SetItemText(id - 1, 2, L"-");
			else if (resultf.size() == 2) pInfo->list->SetItemText(id - 1, 2, L"Prime");
			else pInfo->list->SetItemText(id - 1, 2, L"Composite");
			pInfo->list->SetItemText(id - 1, 3, wss.str().c_str());

			pInfo->progress->SetPos(id * 100 / pInfo->numbers.size());
		}
	}

	if (pInfo->minimize) ShowWindow(pInfo->main, SW_NORMAL);
	pInfo->progress->SetState(100);
	pInfo->button1->EnableWindow(true);
	pInfo->button2->EnableWindow(true);
	pInfo->status->SetPaneText(1, L"Ready.");

	if (pInfo->alert) MessageBox(pInfo->main, L"Computation completed.", L"Factorizer", MB_OK | MB_APPLMODAL | MB_ICONINFORMATION);
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
	m_status.SetPaneText(1, L"Writing to file...");

	m_browse2.GetWindowText(buf1);
	fs.open(buf1.GetString(), std::ios::out);
	if (!fs.is_open()) {
		m_button1.EnableWindow(true);
		m_button2.EnableWindow(true);
		m_status.SetPaneText(1, L"Ready.");
		MessageBox(L"Cannot open output file.", L"File error", MB_OK | MB_APPLMODAL | MB_ICONERROR);
		return;
	}
	if (m_list1.GetItemCount() == 0) {
		m_button1.EnableWindow(true);
		m_button2.EnableWindow(true);
		m_status.SetPaneText(1, L"Ready.");
		MessageBox(L"There are no results to output.", L"Warning", MB_OK | MB_APPLMODAL | MB_ICONWARNING);
		return;
	}

	for (int i = 0; i < m_list1.GetItemCount(); ++i) {
		fs << m_list1.GetItemText(i, 1).GetString() << L" (" << m_list1.GetItemText(i, 2).GetString() << L"): " << m_list1.GetItemText(i, 3).GetString() << std::endl;
	}
	fs << std::endl;

	m_button1.EnableWindow(true);
	m_button2.EnableWindow(true);
	fs.close();
	m_status.SetPaneText(1, L"Ready.");
	MessageBox(L"Output completed.", L"Factorizer", MB_OK | MB_APPLMODAL | MB_ICONINFORMATION);
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
	dlg.DoModal();

	std::wfstream fs;
	fs.open(L"config.dll", std::ios::in);
	if (!fs.is_open()) {
		MessageBox(L"Configuration file not found.", L"Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		return;
	}
	fs >> minimizeWhenComputing >> alertWhenDone;
	fs.close();
}


void CFactorizerDlg::OnOptionsAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg dlg;
	dlg.DoModal();
}


void CFactorizerDlg::OnToolsOpenincommandprompt()
{
	// TODO: 在此添加命令处理程序代码
	system(".\\cmdFactorizer.exe");
}
