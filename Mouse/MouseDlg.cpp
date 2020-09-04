
// MouseDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Mouse.h"
#include "MouseDlg.h"
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


// CMouseDlg 对话框



CMouseDlg::CMouseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MOUSE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMouseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMouseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMouseDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMouseDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMouseDlg::OnBnClickedButton3)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CMouseDlg 消息处理程序

BOOL CMouseDlg::OnInitDialog()
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

void CMouseDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMouseDlg::OnPaint()
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
HCURSOR CMouseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMouseDlg::OnBnClickedButton1()
{
	SwapMouseButton(TRUE);
}


void CMouseDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	SwapMouseButton(FALSE);
}


void CMouseDlg::OnBnClickedButton3()
{


}


BOOL CMouseDlg::PreTranslateMessage(MSG* pMsg)
{	
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd != NULL && pMsg->hwnd == GetDlgItem(IDC_BUTTON3)->GetSafeHwnd())
		{
			SetCapture();
			capture = TRUE;
		}
	}
	
	if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd != NULL && pMsg->hwnd == GetDlgItem(IDC_BUTTON3)->GetSafeHwnd())
		{
			ReleaseCapture();
			capture = FALSE;

			if (m_hWndPrevious != NULL)
			{
				CRect rect;
			    hPen = CreatePen(PS_INSIDEFRAME, 1 * GetSystemMetrics(SM_CXBORDER), RGB(255, 255, 255));
				::GetWindowRect(m_hWndPrevious, &rect);
				hdc = ::GetWindowDC(m_hWndPrevious);
				//sets the current foreground mix mode.
				//R2_NOT Pixel is the inverse of the screen color. 
				SetROP2(hdc, R2_NOT);
				hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
				hOldPen = (HPEN)SelectObject(hdc, hPen);
				SelectObject(hdc, hOldBrush);

				::ReleaseDC(m_hWndPrevious,hdc);
				DeleteObject(hOldPen);
				DeleteObject(hPen);
				DeleteObject(hOldBrush);
				m_hWndPrevious = NULL;
			}
			::InvalidateRect(NULL, NULL, FALSE);
		}
	}

	if (pMsg->message == WM_MOUSEMOVE)
	{
		if (capture)
		{
			CRect rect;
			ClientToScreen(&rect);
			HWND hwnd = ::WindowFromPoint(pMsg->pt);
            hPen = CreatePen(PS_INSIDEFRAME, 1 * GetSystemMetrics(SM_CXBORDER), RGB(255, 255, 255));
			TCHAR buf[512];

			if (hwnd != m_hWndPrevious)
			{
				::GetWindowRect(m_hWndPrevious, &rect);
				hdc = ::GetWindowDC(m_hWndPrevious);
				SetROP2(hdc, R2_NOT);
				hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
				hOldPen = (HPEN)SelectObject(hdc, hPen);
				Rectangle(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top);
				SelectObject(hdc, hOldPen);
				SelectObject(hdc, hOldBrush);
				//::ReleaseDC(hwnd, hdc);
				//DeleteObject(hPen);
				//DeleteObject(hOldPen);
				//DeleteObject(hOldBrush);

				m_hWndPrevious = hwnd;
				::GetWindowRect(m_hWndPrevious, &rect);
				hdc = ::GetWindowDC(m_hWndPrevious);
				hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
				SetROP2(hdc, R2_NOT);
				hOldPen = (HPEN)SelectObject(hdc, hPen);
				Rectangle(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top);
				SelectObject(hdc, hOldPen);
				SelectObject(hdc, hOldBrush);

				::ReleaseDC(m_hWndPrevious, hdc);
				DeleteObject(hPen);
				DeleteObject(hOldPen);
				DeleteObject(hOldBrush);
			}

			if (hwnd != NULL)
			{
				CString str;
				str.Format(TEXT("0x%0xX"), hwnd);
				GetDlgItem(IDC_EDIT2)->SetWindowText(str);

				
				::GetWindowText(hwnd, buf, 512);
				GetDlgItem(IDC_EDIT3)->SetWindowText(buf);

				::GetClassName(hwnd, buf, 512);
				GetDlgItem(IDC_EDIT4)->SetWindowText(buf);
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMouseDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialogEx::OnMouseMove(nFlags, point);
}


void CMouseDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMouseDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnLButtonUp(nFlags, point);
}
