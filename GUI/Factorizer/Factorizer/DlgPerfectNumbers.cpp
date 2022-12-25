// DlgPerfectNumbers.cpp: 实现文件
//

#include "pch.h"
#include "Factorizer.h"
#include "DlgPerfectNumbers.h"
#include "afxdialogex.h"


// DlgPerfectNumbers 对话框

IMPLEMENT_DYNAMIC(DlgPerfectNumbers, CDialogEx)

DlgPerfectNumbers::DlgPerfectNumbers(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PERFECTNUMBERS, pParent)
{

}

DlgPerfectNumbers::~DlgPerfectNumbers()
{
}

void DlgPerfectNumbers::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_1, m_edit1);
	DDX_Control(pDX, IDC_EDIT_2, m_edit2);
	DDX_Control(pDX, IDC_EDIT_3, m_edit3);
	DDX_Control(pDX, IDC_EDIT_4, m_edit4);
	DDX_Control(pDX, IDC_EDIT_5, m_edit5);
}


BEGIN_MESSAGE_MAP(DlgPerfectNumbers, CDialogEx)
END_MESSAGE_MAP()


// DlgPerfectNumbers 消息处理程序
