// Process_ZwQuerySystemInformation.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <Windows.h>
#include <winternl.h>
#include<strsafe.h>
#include<iostream>

typedef long(__stdcall* funNtQuerySystemInformation)(UINT, PVOID, ULONG, PULONG);

int main()
{
    NTSTATUS status;
    PVOID buffer;
    PSYSTEM_PROCESS_INFORMATION pspi;

    //分配足够大的空间
    buffer = VirtualAlloc(NULL, 1024 * 1024, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); 

    if (!buffer)
    {
        //分配内存失败
        //GetLastError
        return 0;
    }

    HMODULE hModule = LoadLibrary(L"ntdll.dll");

    if (!hModule)
    {
        //加载dll失败
        //GetLastError
        return 0;
    }

    funNtQuerySystemInformation NtQuerySystemInformation = (funNtQuerySystemInformation)GetProcAddress(hModule, "NtQuerySystemInformation");

    pspi = (PSYSTEM_PROCESS_INFORMATION)buffer;

    if (!NT_SUCCESS(status = NtQuerySystemInformation(SystemProcessInformation, pspi, 1024 * 1024, NULL)))
    {
        //查询进程列表失败
        VirtualFree(buffer, 0, MEM_RELEASE);
        return 0;
    }

    while (pspi->NextEntryOffset) // Loop over the list until we reach the last entry.
    {
        //在这里添加处理逻辑
        //......
        TCHAR buf[128]{};
        StringCchCopy(buf, pspi->ImageName.Length, pspi->ImageName.Buffer);
        std::wcout << buf << std::endl;

        //计算下一条目的地址
        pspi = (PSYSTEM_PROCESS_INFORMATION)((LPBYTE)pspi + pspi->NextEntryOffset); 
    }

    //释放分配的空间
    VirtualFree(buffer, 0, MEM_RELEASE); 

    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
