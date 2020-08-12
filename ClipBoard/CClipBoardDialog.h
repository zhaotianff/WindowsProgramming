#pragma once


// CClipBoardDialog 对话框

class CClipBoardDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CClipBoardDialog)

public:
	CClipBoardDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CClipBoardDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIPBOARD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
