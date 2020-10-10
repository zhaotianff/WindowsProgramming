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

// 钩子回调函数
LRESULT GetMsgProc(int code, WPARAM wParam, LPARAM lParam)
{
	
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
	return TRUE;
}


