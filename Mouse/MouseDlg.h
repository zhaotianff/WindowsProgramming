
// MouseDlg.h: 头文件
//

#pragma once


// CMouseDlg 对话框
class CMouseDlg : public CDialogEx
{
// 构造
public:
	CMouseDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOUSE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

public:
	BOOL capture;
	HWND m_hWndPrevious;
	HPEN hOldPen;
	HDC hdc;
	HBRUSH hOldBrush;
	HPEN hPen;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
