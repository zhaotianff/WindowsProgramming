
// MessageDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Message.h"
#include "MessageDlg.h"
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


// CMessageDlg 对话框



CMessageDlg::CMessageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MESSAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_editText);
}

BEGIN_MESSAGE_MAP(CMessageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMessageDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMessageDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMessageDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMessageDlg 消息处理程序

BOOL CMessageDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMessageDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMessageDlg::OnPaint()
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
HCURSOR CMessageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);	
}



void CMessageDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	HWND hwnd = ::FindWindow(L"CabinetWClass", NULL);

	if (hwnd)
	{
		::SendMessage(hwnd,WM_CLOSE,NULL,NULL);
	}
}


void CMessageDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	
	TCHAR buf[520]{};

	//获取第一个资源管理器窗口
	HWND hwnd = ::FindWindow(L"CabinetWClass", NULL);
	if (hwnd)
	{
		::SendMessage(hwnd, WM_GETTEXT, (WPARAM)520, (LPARAM)buf);
		((CEdit*)GetDlgItem(IDC_EDIT1))->SetWindowTextW(buf);
	}
	else
	{
		AfxMessageBox(L"没有资源管理器窗口");
	}
}


void CMessageDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	HWND hwnd = ::FindWindow(L"CabinetWClass", NULL);


	if (hwnd)
	{
		TCHAR buf[520]{};
		m_editText.GetWindowTextW(buf, 520);

		::SendMessage(hwnd, WM_SETTEXT, (WPARAM)0, (LPARAM)buf);

		OnBnClickedButton2();
	}
	else
	{
		AfxMessageBox(L"没有资源管理器窗口");
	}
}
