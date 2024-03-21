// Process_EnumProcesses.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<Windows.h>
#include<tchar.h>
#include<Psapi.h>

int main()
{
    DWORD processesArray[1024], cbNeeded, processesCount;
    
    if (!EnumProcesses(processesArray, sizeof(processesArray), &cbNeeded))
    {
        return 0;
    }

    processesCount = cbNeeded / sizeof(DWORD);


    for (int i = 0; i < processesCount; i++)
    {
        TCHAR szProcessName[MAX_PATH] = L"<unknown>";

        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
            FALSE, processesArray[i]);

        if (NULL != hProcess)
        {
            HMODULE hMod;

            if (EnumProcessModulesEx(hProcess, &hMod, sizeof(hMod), &cbNeeded, LIST_MODULES_ALL))
            {
                GetModuleBaseName(hProcess, hMod, szProcessName, 
                    sizeof(szProcessName) / sizeof(TCHAR));

                std::wcout << szProcessName << std::endl;

                CloseHandle(hProcess);
            }

        }
    }
}