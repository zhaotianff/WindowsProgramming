
// KeyBoardDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "KeyBoard.h"
#include "KeyBoardDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CKeyBoardDlg 对话框



CKeyBoardDlg::CKeyBoardDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KEYBOARD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeyBoardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKeyBoardDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CKeyBoardDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CKeyBoardDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CKeyBoardDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CKeyBoardDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CKeyBoardDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CKeyBoardDlg 消息处理程序

BOOL CKeyBoardDlg::OnInitDialog()
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
	ShowLockStatus();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CKeyBoardDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CKeyBoardDlg::OnPaint()
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
HCURSOR CKeyBoardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKeyBoardDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


BOOL CKeyBoardDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (pMsg->message == WM_KEYDOWN)
	{
		TCHAR strName[32];
		int i = GetKeyNameText(pMsg->lParam, strName, 32);
		GetDlgItem(IDC_EDIT1)->SetWindowText(strName);

		wsprintf(strName, TEXT("%d"), MapVirtualKey(HIWORD(pMsg->lParam),1));
		GetDlgItem(IDC_EDIT2)->SetWindowText(strName);

		wsprintf(strName, TEXT("%d"), MapVirtualKey(HIWORD(pMsg->lParam),3));
		GetDlgItem(IDC_EDIT3)->SetWindowText(strName);

		ShowLockStatus();
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CKeyBoardDlg::ShowLockStatus()
{
	//If the high-order bit is 1, the key is down; otherwise, it is up.
	//SHORT 16 bits	
	//0x8000 1000 0000 0000 0000
	
	/*if (GetKeyState(VK_CAPITAL) != 0)
	{
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	}

	if (GetKeyState(VK_NUMLOCK) != 0)
	{
		((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(TRUE);
	}

	if (GetKeyState(VK_SCROLL) != 0) 
	{
		((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(TRUE);
	}*/

	BYTE keyState[256];
	GetKeyboardState((LPBYTE)keyState);

	if (keyState[VK_CAPITAL] & 1)
	{
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(FALSE);
	}
	
	if (keyState[VK_NUMLOCK] & 1)
	{
		((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(TRUE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(FALSE);
	}

	if (keyState[VK_SCROLL] & 1)
	{
		((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(TRUE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(FALSE);
	}
}

void CKeyBoardDlg::EmuKeyStroke(WORD wVk, WORD wScan)
{
	INPUT input{};

	input.type = INPUT_KEYBOARD;
	input.ki.wScan = wScan;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = wVk;
	input.ki.dwFlags = 0;

	SendInput(1, &input, sizeof(INPUT));

	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}


void CKeyBoardDlg::OnBnClickedButton1()
{
	//keybd_event(VK_CAPITAL, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0);
	//keybd_event(VK_CAPITAL, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	//use SendInput instead
	EmuKeyStroke(VK_CAPITAL, 0x3a);
}


void CKeyBoardDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	EmuKeyStroke(VK_NUMLOCK, 0x45);
}


void CKeyBoardDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	EmuKeyStroke(VK_SCROLL, 0x46);
}


void CKeyBoardDlg::OnBnClickedButton4()
{
	/*keybd_event(VK_MENU, 0, 0, 0);
	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event(VK_TAB, 0, 0, 0);

	keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);*/

	//SendInput
	INPUT inputs[3]{};

	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wScan = 0;
	inputs[0].ki.time = 0;
	inputs[0].ki.dwExtraInfo = 0;
	inputs[0].ki.wVk = VK_MENU;
	inputs[0].ki.dwFlags = 0;

	inputs[1] = inputs[0];
	inputs[2] = inputs[0];

	inputs[1].ki.wVk = VK_CONTROL;
	inputs[2].ki.wVk = VK_TAB;

	SendInput(3, inputs, sizeof(INPUT));

	inputs[0].ki.dwFlags = KEYEVENTF_KEYUP;
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
	inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(3, inputs, sizeof(INPUT));

	Sleep(2000);

	//关闭切换界面
	inputs[0].ki.dwFlags = 0;
	inputs[0].ki.wVk = VK_ESCAPE;
	SendInput(1, &inputs[0], sizeof(INPUT));

	inputs[0].ki.dwFlags = KEYEVENTF_KEYUP;
	inputs[0].ki.wVk = VK_ESCAPE;
	SendInput(1, &inputs[0], sizeof(INPUT));
}
