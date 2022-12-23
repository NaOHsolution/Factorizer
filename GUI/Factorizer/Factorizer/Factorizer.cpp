
// Factorizer.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "Factorizer.h"
#include "FactorizerDlg.h"
#include "SettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFactorizerApp

BEGIN_MESSAGE_MAP(CFactorizerApp, CWinApp)
END_MESSAGE_MAP()

// CFactorizerApp 构造

CFactorizerApp::CFactorizerApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CFactorizerApp 对象

CFactorizerApp theApp;


// CFactorizerApp 初始化

BOOL CFactorizerApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CFactorizerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

void CMyListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rcItem(lpDrawItemStruct->rcItem), rcItem2;
	int nItem = lpDrawItemStruct->itemID;
	int offset = 5;
	COLORREF clrTextSave, clrBkSave;
	static _TCHAR szBuff[2048];//这里是你要显示的字符串长度，想多长有多长
	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT | LVIF_STATE;//LVIF_IMAGE   |
	lvi.iItem = nItem;
	lvi.iSubItem = 0;
	lvi.pszText = szBuff;
	lvi.cchTextMax = sizeof(szBuff);
	lvi.stateMask = 0xFFFF;
	GetItem(&lvi);

	BOOL bSelected = (lvi.state & LVIS_SELECTED);
	CRect rcAllLabels;
	GetItemRect(nItem, rcAllLabels, LVIR_BOUNDS);
	if (bSelected) {
		clrTextSave = pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		clrBkSave = pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
		pDC->FillRect(rcAllLabels, &CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
	}
	else {
		clrTextSave = pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
		clrBkSave = pDC->SetBkColor(::GetSysColor(COLOR_WINDOW));
		pDC->FillRect(rcAllLabels, &CBrush(::GetSysColor(COLOR_WINDOW)));
	}
	GetItemRect(nItem, rcItem, LVIR_LABEL);
	rcItem2 = rcItem;
	rcItem2.left += offset;
	rcItem2.right += offset;
	pDC->DrawText(szBuff, -1, rcItem2, DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER | DT_END_ELLIPSIS);

	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH;
	for (int nColumn = 1; GetColumn(nColumn, &lvc); nColumn++) {
		rcItem.left = rcItem.right;
		rcItem.right += lvc.cx;
		rcItem2 = rcItem;
		rcItem2.left += offset;
		rcItem2.right += offset;

		int nRetLen = GetItemText(nItem, nColumn, szBuff, sizeof(szBuff));
		if (nRetLen == 0)
			continue;
		UINT nJustify = DT_LEFT;
		switch (lvc.fmt & LVCFMT_JUSTIFYMASK) {
		case   LVCFMT_RIGHT:
			nJustify = DT_RIGHT;
			break;
		case   LVCFMT_CENTER:
			nJustify = DT_CENTER;
			break;
		default:
			break;
		}
		pDC->DrawText(szBuff, -1, rcItem2, nJustify | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER | DT_END_ELLIPSIS);// DT_END_ELLIPSIS可以实现文字显示不开后的...效果
	}
	if (lvi.state & LVIS_FOCUSED) pDC->DrawFocusRect(rcAllLabels);
	if (bSelected) {
		pDC->SetTextColor(clrTextSave);
		pDC->SetBkColor(clrBkSave);
	}
}
