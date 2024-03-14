// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "framework.h"
#include <Windows.h>
#include <TlHelp32.h>

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		//TCHAR szBuffer[MAX_PATH]{};
		//GetModuleFileName(hModule, szBuffer, 260);
		MessageBox(NULL, L"Hello World", L"Inject Success", MB_OK);
	}
	break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

