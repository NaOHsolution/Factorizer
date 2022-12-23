// Factorizer.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

typedef unsigned long long ull;

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// CFactorizerApp:
// 有关此类的实现，请参阅 Factorizer.cpp
//

class CFactorizerApp : public CWinApp
{
public:
	CFactorizerApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CFactorizerApp theApp;

class CMyListCtrl : public CListCtrl {
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};