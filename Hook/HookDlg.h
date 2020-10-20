
// HookDlg.h: 头文件
//

#pragma once

typedef BOOL (*SetHook)();
typedef BOOL(*UnSetHook)();


// CHookDlg 对话框
class CHookDlg : public CDialogEx
{
// 构造
public:
	CHookDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOOK_DIALOG };
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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();

private:
	SetHook m_fSetHook;
	UnSetHook m_fUnSetHook;
public:
	afx_msg void OnBnClickedButton2();
};
