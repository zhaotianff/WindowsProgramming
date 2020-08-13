
// ClipBoardDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ClipBoard.h"
#include "ClipBoardDlg.h"
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


// CClipBoardDlg 对话框



CClipBoardDlg::CClipBoardDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLIPBOARD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClipBoardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDCANCEL, m_picture);
}

BEGIN_MESSAGE_MAP(CClipBoardDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CClipBoardDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CClipBoardDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CClipBoardDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CClipBoardDlg 消息处理程序

BOOL CClipBoardDlg::OnInitDialog()
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

void CClipBoardDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClipBoardDlg::OnPaint()
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
HCURSOR CClipBoardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClipBoardDlg::OnBnClickedOk()
{
	//https://docs.microsoft.com/en-us/windows/win32/dataxchg/clipboard

	

	
}


void CClipBoardDlg::OnBnClickedButton1()
{
	//https://docs.microsoft.com/en-us/windows/win32/dataxchg/standard-clipboard-formats#constants

	m_list.ResetContent();

	if (OpenClipboard())
	{
		UINT format = 0;

		while (format = EnumClipboardFormats(format))
		{
			m_list.AddString(GetClipBoardFormat(format));
		}
	}
}

CString CClipBoardDlg::GetClipBoardFormat(int index)
{
	CString format;
	switch (index)
	{
	case 1:
		format = "CF_TEXT";
		break;
	case 2:
		format = "CF_BITMAP";
		break;
	case 3:
		format = "CF_METAFILEPICT";
		break;
	case 4:
		format = "CF_SYLK";
		break;
	case 5:
		format = "CF_DIF";
		break;
	case 6:
		format = "CF_TIFF";
		break;
	case 7:
		format = "CF_OEMTEXT";
		break;
	case 8:
		format = "CF_DIB";
		break;
	case 9:
		format = "CF_PALETTE";
		break;
	case 10:
		format = "CF_PENDATA";
		break;
	case 11:
		format = "CF_RIFF";
		break;
	case 12:
		format = "CF_WAVE";
		break;
	case 13:
		format = "CF_UNICODETEXT";
		break;
	case 14:
		format = "CF_ENHMETAFILE";
		break;
	case 15:
		format = "CF_HDROP";
		break;
	case 16:
		format = "CF_LOCALE";
		break;
	case 17:
		format = "CF_MAX";
		break;
	case 0x0080:
		format = "CF_OWNERDISPLAY";
		break;
	case 0x0081:
		format = "CF_DSPTEXT";
		break;
	case 0x0082:
		format = "CF_DSPBITMAP";
		break;
	case 0x0083:
		format = "CF_DSPMETAFILEPICT";
		break;
	case 0x008E:
		format = "CF_DSPENHMETAFILE";
		break;
	case 0x0200:
		format = "CF_PRIVATEFIRST";
		break;
	case 0x02FF:
		format = "CF_PRIVATELAST";
		break;
	case 0x0300:
		format = "CF_GDIOBJFIRST";
		break;
	case 0x03FF:
		format = "CF_GDIOBJLAST";
		break;
	default:
		format.Format(TEXT("%d"),index);
		break;

	}

	return format;
}


void CClipBoardDlg::OnBnClickedButton2()
{
	OPENFILENAME ofn;   
	TCHAR szFile[260]{};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = GetSafeHwnd();
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = _T("图像\0*.bmp\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		HANDLE hBMP = LoadImage(NULL,ofn.lpstrFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		::OpenClipboard(GetSafeHwnd());
		::EmptyClipboard();
		::SetClipboardData(CF_BITMAP, hBMP);
		::CloseClipboard();
	}
}
