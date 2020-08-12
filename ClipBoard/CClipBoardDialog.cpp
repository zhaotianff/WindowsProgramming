// CClipBoardDialog.cpp: 实现文件
//

#include "pch.h"
#include "ClipBoard.h"
#include "CClipBoardDialog.h"
#include "afxdialogex.h"


// CClipBoardDialog 对话框

IMPLEMENT_DYNAMIC(CClipBoardDialog, CDialogEx)

CClipBoardDialog::CClipBoardDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLIPBOARD_DIALOG, pParent)
{

}

CClipBoardDialog::~CClipBoardDialog()
{
}

void CClipBoardDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CClipBoardDialog, CDialogEx)
END_MESSAGE_MAP()


// CClipBoardDialog 消息处理程序
