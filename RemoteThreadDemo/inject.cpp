#include "inject.h"

BOOL EnablePrivileges(HANDLE hProcess,TCHAR* pszPrivilegesName)
{
    HANDLE hToken = NULL;
    LUID luidValue = { 0 };
    TOKEN_PRIVILEGES tokenPrivileges = { 0 };
    BOOL bRet = FALSE;
    DWORD dwRet = 0;

    bRet = OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES, &hToken);
    if (FALSE == bRet)
    {
        return FALSE;
    }

    bRet = LookupPrivilegeValue(NULL, pszPrivilegesName, &luidValue);
    if (FALSE == bRet)
    {
        return FALSE;
    }

    tokenPrivileges.PrivilegeCount = 1;
    tokenPrivileges.Privileges[0].Luid = luidValue;
    tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    bRet = AdjustTokenPrivileges(hToken, FALSE, &tokenPrivileges, 0, NULL, NULL);
    if (FALSE == bRet)
    {
        return FALSE;
    }
    else
    {
        dwRet = GetLastError();

        if (ERROR_SUCCESS == dwRet)
        {
            return TRUE;
        }
        else if (ERROR_NOT_ALL_ASSIGNED == dwRet)
        {
            return FALSE;
        }
    }
    return FALSE;


}

BOOL CreateRemoteThreadInject(DWORD dwPid, LPCTSTR pszDllFileName)
{
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
    
    if (NULL == hProcess)
        return FALSE;

    SIZE_T dwSize = (1 + lstrlen(pszDllFileName)) * sizeof(TCHAR);
    LPVOID lpDllAddr = VirtualAllocEx(hProcess, NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);

    if (NULL == lpDllAddr)
    {
        CloseHandle(hProcess);
        return FALSE;
    }

    BOOL bRet = WriteProcessMemory(hProcess, lpDllAddr, pszDllFileName, dwSize, NULL);

    if (!bRet)
    {
        CloseHandle(hProcess);
        return FALSE;
    }

    LPVOID lpLoadLibraryFunc = LoadLibraryW;

    HANDLE hRemoteThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)lpLoadLibraryFunc, (LPVOID)lpDllAddr, 0, NULL);

    if (NULL == hRemoteThread)
    {
        CloseHandle(hProcess);
        return FALSE;
    }

    //WaitForSingleObject(hRemoteThread, INFINITE);

    CloseHandle(hProcess);
    CloseHandle(hRemoteThread);
    return TRUE;
}
