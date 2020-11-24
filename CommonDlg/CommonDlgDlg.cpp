
// CommonDlgDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "CommonDlg.h"
#include "CommonDlgDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT_PTR CALLBACK PaintHook(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

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


// CCommonDlgDlg 对话框



CCommonDlgDlg::CCommonDlgDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COMMONDLG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCommonDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCommonDlgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCommonDlgDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCommonDlgDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCommonDlgDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCommonDlgDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CCommonDlgDlg 消息处理程序

BOOL CCommonDlgDlg::OnInitDialog()
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

void CCommonDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCommonDlgDlg::OnPaint()
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
HCURSOR CCommonDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCommonDlgDlg::OnBnClickedButton1()
{
	PRINTDLG pd{};
	
	pd.lStructSize = sizeof(pd);
	pd.hwndOwner = NULL;
	pd.hDevMode = NULL;
	pd.hDevNames = NULL;
	pd.Flags = PD_USEDEVMODECOPIESANDCOLLATE || PD_RETURNDC;
	pd.nCopies = 1;        //设置打印份数
	pd.nFromPage = 0xFFFF; //设置打印起始页号
	pd.nToPage = 0xFFFF;   //设置打印结束页号
	pd.nMinPage = 1;
	pd.nMaxPage = 0xFFFF;

	if (PrintDlg(&pd) == TRUE)
	{
		//打印操作

		//释放dc
		if(pd.hDC != NULL)
			DeleteDC(pd.hDC);
	}

	
}

UINT_PTR CALLBACK PaintHook(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LPRECT lprc;
	COLORREF crMargRect;
	HDC hdc, hdcOld;

	switch (uMsg)
	{
		// Draw the margin rectangle. 
	case WM_PSD_MARGINRECT:
		hdc = (HDC)wParam;
		lprc = (LPRECT)lParam;

		// Get the system highlight color. 
		crMargRect = GetSysColor(COLOR_HIGHLIGHT);

		// Create a dash-dot pen of the system highlight color and 
		// select it into the DC of the sample page. 
		hdcOld = (HDC)SelectObject(hdc, CreatePen(PS_DASHDOT, .5, crMargRect));

		// Draw the margin rectangle. 
		Rectangle(hdc, lprc->left, lprc->top, lprc->right, lprc->bottom);

		// Restore the previous pen to the DC. 
		SelectObject(hdc, hdcOld);
		return TRUE;

	default:
		return FALSE;
	}
	return TRUE;
}


void CCommonDlgDlg::OnBnClickedButton2()
{
	HWND hWnd = GetSafeHwnd();
	HRESULT hResult;
	PRINTDLGEX pdx = { 0 };
	LPPRINTPAGERANGE pPageRanges = NULL;

	// Allocate an array of PRINTPAGERANGE structures.
	pPageRanges = (LPPRINTPAGERANGE)GlobalAlloc(GPTR, 10 * sizeof(PRINTPAGERANGE));
	if (!pPageRanges)
		return;

	//  Initialize the PRINTDLGEX structure.
	pdx.lStructSize = sizeof(PRINTDLGEX);
	pdx.hwndOwner = hWnd;
	pdx.hDevMode = NULL;
	pdx.hDevNames = NULL;
	pdx.hDC = NULL;
	pdx.Flags = PD_RETURNDC | PD_COLLATE;
	pdx.Flags2 = 0;
	pdx.ExclusionFlags = 0;
	pdx.nPageRanges = 0;
	pdx.nMaxPageRanges = 10;
	pdx.lpPageRanges = pPageRanges;
	pdx.nMinPage = 1;
	pdx.nMaxPage = 1000;
	pdx.nCopies = 1;
	pdx.hInstance = 0;
	pdx.lpPrintTemplateName = NULL;
	pdx.lpCallback = NULL;
	pdx.nPropertyPages = 0;
	pdx.lphPropertyPages = NULL;
	pdx.nStartPage = START_PAGE_GENERAL;
	pdx.dwResultAction = 0;

	//  Invoke the Print property sheet.

	hResult = PrintDlgEx(&pdx);

	if ((hResult == S_OK) && pdx.dwResultAction == PD_RESULT_PRINT)
	{
		// User clicked the Print button, so use the DC and other information returned in the 
		// PRINTDLGEX structure to print the document.
	}

	if (pdx.hDevMode != NULL)
		GlobalFree(pdx.hDevMode);
	if (pdx.hDevNames != NULL)
		GlobalFree(pdx.hDevNames);
	if (pdx.lpPageRanges != NULL)
		GlobalFree(pPageRanges);

	if (pdx.hDC != NULL)
		DeleteDC(pdx.hDC);
}


void CCommonDlgDlg::OnBnClickedButton3()
{
	PAGESETUPDLG psd;    // common dialog box structure
	HWND hwnd = GetSafeHwnd();           // owner window

	// Initialize PAGESETUPDLG
	ZeroMemory(&psd, sizeof(psd));
	psd.lStructSize = sizeof(psd);
	psd.hwndOwner = hwnd;
	psd.hDevMode = NULL; // Don't forget to free or store hDevMode.
	psd.hDevNames = NULL; // Don't forget to free or store hDevNames.
	psd.Flags = PSD_INTHOUSANDTHSOFINCHES | PSD_MARGINS |
		PSD_ENABLEPAGEPAINTHOOK;
	psd.rtMargin.top = 1000;
	psd.rtMargin.left = 1250;
	psd.rtMargin.right = 1250;
	psd.rtMargin.bottom = 1000;
	psd.lpfnPagePaintHook = PaintHook;

	if (PageSetupDlg(&psd) == TRUE)
	{
		// check paper size and margin values here.
	}
}


void CCommonDlgDlg::OnBnClickedButton4()
{
	OPENFILENAME ofn{};
	TCHAR szFile[260]{};       //文件名缓冲区

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL; //设置对话框拥有者句柄
	ofn.lpstrFile = szFile; //设置文件名缓冲区
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile); //设置所选文件路径缓冲区最大长度
	ofn.lpstrFilter = L"全部文件\0*.*\0文本文件\0*.txt\0";  //指定文件类型
	ofn.nFilterIndex = 1;  //文件类型选中的索引 从1开始
	ofn.lpstrFileTitle = NULL;  //选中的文件名（不包含路径，包含扩展名）
	ofn.nMaxFileTitle = 0;  //选中的文件名缓冲区最大长度
	ofn.lpstrInitialDir = NULL;  //初始路径
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; //用于初始化对话框的标志位


	if (GetOpenFileName(&ofn) == TRUE)
		MessageBox(ofn.lpstrFile);
}
