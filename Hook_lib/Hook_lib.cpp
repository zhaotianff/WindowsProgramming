// Hook_lib.cpp : 定义 DLL 的导出函数。
//

#include "pch.h"
#include "framework.h"
#include "Hook_lib.h"


extern HMODULE g_hDllModule;

// 共享内存
#pragma data_seg("mydata")
HHOOK g_hHook = NULL;
#pragma data_seg()
#pragma comment(linker, "/SECTION:mydata,RWS")

BOOL bInstalled = FALSE;

LRESULT CALLBACK OwnerDrawButtonProc(HWND hWnd, UINT uMsg, WPARAM wParam,
	LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		MessageBox(NULL, L"StartMenu", NULL, MB_OK);
		return TRUE;
	}
	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

// 钩子回调函数
LRESULT GetMsgProc(int code, WPARAM wParam, LPARAM lParam)
{
	//If code is less than zero, the hook procedure must return the value returned by CallNextHookEx.

	//If code is greater than or equal to zero, it is highly recommended that you call CallNextHookEx and return the value it returns;
	//otherwise, other applications that have installed WH_GETMESSAGE hooks will not receive hook notifications and may behave incorrectly as a result.
	//If the hook procedure does not call CallNextHookEx, the return value should be zero.

	if (code == HC_ACTION)
	{
		PMSG msg = (PMSG)lParam;

		if (!bInstalled)
		{
			bInstalled = TRUE;
			HWND tray = FindWindow(L"Shell_TrayWnd", NULL);
			HWND hStart = FindWindowEx(tray, NULL, L"Start", NULL);
			BOOL bResult = SetWindowSubclass(hStart, OwnerDrawButtonProc, 'CLSH', 0);

			if (bResult)
			{
				MessageBox(NULL, L"1", NULL, MB_OK);
			}
			else
			{
				MessageBox(NULL, L"0", NULL, MB_OK);
			}
		}

		return TRUE;
	}
	else
	{
		return CallNextHookEx(g_hHook, code, wParam, lParam);
	}	


	/*
	*键盘钩子
	BOOL fEatKeystroke = FALSE;
	PKBDLLHOOKSTRUCT p = NULL;

	if (nCode == HC_ACTION)
	{
		p = (PKBDLLHOOKSTRUCT)lParam;
		switch (wParam)
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
			fEatKeystroke = (p->vkCode == VK_LWIN) || (p->vkCode == VK_RWIN) ||         // 屏蔽Win
				((p->vkCode == VK_TAB) && ((p->flags & LLKHF_ALTDOWN) != 0)) ||         // 屏蔽Alt+Tab
				((p->vkCode == VK_ESCAPE) && ((p->flags & LLKHF_ALTDOWN) != 0)) ||		// 屏蔽Alt+Esc
				((p->vkCode == VK_F4) && ((p->flags & LLKHF_ALTDOWN) != 0)) ||          // 屏蔽Alt+F4
				((p->vkCode == VK_ESCAPE) && ((GetKeyState(VK_CONTROL) & 0x8000) != 0));// 屏蔽Ctrl+Esc
			break;
		default:
			break;
		}
	}

	return (fEatKeystroke ? TRUE : CallNextHookEx(g_lhHook, nCode, wParam, lParam));
	*/
}

HOOKLIB_API BOOL SetHook()
{
	//https://docs.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-setwindowshookexa
	//WH_CALLWNDPROC 安装钩子程序，在系统将消息发送到目标窗口过程之前监视消息
	//WH_CALLWNDPROCRET 安装钩子程序，在目标窗口过程处理消息后监视消息
	//WH_CBT 安装接收对CBT应用程序有用通知的钩子程序
	//WH_DEBUG 安装可用于调试其它钩子程序的钩子程序
	//WH_FOREGROUNDIDLE 安装在应用程序的前台线程即将变为空闲时调用的钩子过程，该钩子对于在空闲时执行低优先级任务很有用
	//WH_GETMESSAGE 安装一个挂钩过程，它监视发送到消息队列的消息
	//WH_JOURNALPLAYBACK 安装一个挂钩过程，用于发布先前由WH_JOURNALRECORD挂钩过程记录的消息
	//WH_JOURNALRECORD 安装一个挂钩过程，记录发布到系统消息队列中的输入消息。这个钩子对于录制宏很有用
	//WH_KEYBOARD 安装监视按键消息的挂钩过程
	//WH_KEYBOARD_LL 安装监视低级键盘输入事件的挂钩过程
	//WH_MOUSE 安装监视鼠标消息的挂钩过程
	//WH_MOUSE_LL 安装监视低级鼠标输入事件的挂钩过程
	//WH_MSGFILTER 安装钩子程序，用于在对话框、消息框、菜单或滚动条中监视由于输入事件而生成的消息
	//WH_SHELL 安装接收对shell应用程序有用通知的钩子程序
	//WH_SYSMESGFILTER 安装钩子程序，用于在对话框、消息框、菜单或滚动条中监视由于输入事件而生成的消息，钩子程序在与调用线程相同的桌面中监视所有应用程序的这些消息
	//(The hook procedure monitors these messages for all applications in the same desktop as the calling thread. For more information, see the SysMsgProc hook procedure. )
	g_hHook = SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)GetMsgProc, g_hDllModule, 0);
	if (g_hHook)
		return TRUE;
	else
		return FALSE;
}

HOOKLIB_API BOOL UnsetHook()
{
	if (g_hHook)
		return UnhookWindowsHookEx(g_hHook);

	return FALSE;
}


