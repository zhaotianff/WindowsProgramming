
// Self-startingDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Self-starting.h"
#include "Self-startingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define notepad_Wide L"C:\\Windows\\System32\\notepad.exe"
#define notepad "C:\\Windows\\System32\\notepad.exe"


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


// CSelfstartingDlg 对话框



CSelfstartingDlg::CSelfstartingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SELFSTARTING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSelfstartingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSelfstartingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSelfstartingDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSelfstartingDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSelfstartingDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CSelfstartingDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CSelfstartingDlg 消息处理程序

BOOL CSelfstartingDlg::OnInitDialog()
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

void CSelfstartingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSelfstartingDlg::OnPaint()
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
HCURSOR CSelfstartingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSelfstartingDlg::OnBnClickedButton1()
{
	//deprecated
	auto nResult = WinExec(notepad, SW_SHOW);
}


void CSelfstartingDlg::OnBnClickedButton2()
{
	
	//CreateProcess()
	PROCESS_INFORMATION pi{};
	STARTUPINFO si{};

	//hide
	//si.dwFlags = STARTF_USESHOWWINDOW;
	//si.wShowWindow = SW_HIDE;

	si.cb = sizeof(STARTUPINFO);
	auto bRet = CreateProcess(notepad_Wide, NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);

	//show
	//ShowWindow(SW_SHOW);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}


void CSelfstartingDlg::OnBnClickedButton3()
{
	// lpOperation edit explore find open print
	TCHAR* lpFile = L"notepad";
	TCHAR* lpDir = L"C:\\Windows\\System32";
	ShellExecute(GetSafeHwnd(), NULL, lpFile, NULL, lpDir, SW_SHOWNORMAL);
}


void CSelfstartingDlg::OnBnClickedButton4()
{
	/*
	* 在Windows XP、Windows Server 2003，以及更老版本的Windows操作系统中，服务和应用程序使用相同的会话(SESSION)来运行，
	* 而这个会话是由第一个登录到控制台的用户来启用的，该会话就称为SESSION 0。
	* 将服务和用户应用程序一起在SESSION 0中运行会导致安全风险，因为服务会使用提升后的权限来运行，而用户应用程序使用用户特权（大部分都是非管理员用户）运行，
	* 这会使得恶意软件把某个服务作为攻击目标，通过“劫持”该服务以达到提升自己权限级别的目的
	* 
	* 从Windows Vista开始，只有服务可以托管到SESSION 0中，用户应用程序和服务之间会进行隔离，并需要运行在用户登录系统时创建的后续会话中
	* 如第一个登录用户创建Session1,第二个登录用户创建Session 2，以此类推
	* 
	* 使用不同会话运行的实体（应用程序或服务），如果不将自己明确标注为全局命名空间，并提供相应的访问控制设置，那么将无法互相发送消息，共享UI元素或共享内核对象
	* 
	* 
	*/

	/*
	* 调用WTSGetActiveConsoleSessionId函数来获取当前程序的会话ID，即Session Id
	* 根据Session Id继续调用WTSQueryUserToken函数来检索用户令牌，并获取对应的用户令牌句柄（调用CloseHandle释放句柄）
	* 使用DuplicateTokenEx函数来创建一个新令牌，并复制上面获取的用户信息，设置新令牌的访问权限为MAXIMUM_ALLOWED，表示获取所有令牌权限。新访问令牌的模拟级别为SecurityIdentification，而且令牌类型为TokenPrimary，这表示新令牌是可以在CreateProcessAsUser函数中使用的主令牌
	* 根据新令牌调用CreateEnvironmentBlock函数创建一个环境块，用来传递给CreateProcessAsUser使用，在不需要使用环境块时，调用DestroyEnvironmentBlock函数进行函数释放
	* 调用CreateProcessAsUser来创建用户桌面进程
	*/
	auto dwSessionID = WTSGetActiveConsoleSessionId();

}
