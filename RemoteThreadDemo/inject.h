#pragma once
#include <Windows.h>

BOOL EnablePrivileges(HANDLE hProcess, TCHAR* pszPrivilegesName);

BOOL CreateRemoteThreadInject(DWORD dwPid, LPCTSTR pszDllFileName);