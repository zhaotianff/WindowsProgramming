// Process.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<Windows.h>
#include<vector>
#include<TlHelp32.h>

using std::cout;
using std::vector;
using std::endl;
using std::wcout;

vector<PROCESSENTRY32> GetAllProcess();

int main()
{
    auto processes = GetAllProcess();

    auto b = processes.begin();
    for (b = processes.begin(); b != processes.end(); ++b)
    {
        wcout << b->szExeFile << endl;
        cout << b->th32ProcessID << endl;
        cout << endl;
    }

}

vector<PROCESSENTRY32> GetAllProcess()
{
    std::vector<PROCESSENTRY32> processes{};
    //dwFlags
    //TH32CS_SNAPMODULE 枚举进程中的dll
    //TH32CS_SNAPPROCESS 枚举系统进程
    //TH32CS_SNAPTHREAD 枚举系统中的线程
    auto hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (hSnap == INVALID_HANDLE_VALUE)
    {
        return processes;
    }

    PROCESSENTRY32 pe32{};
    pe32.dwSize = sizeof(PROCESSENTRY32);
    auto bRet = Process32First(hSnap, &pe32);

    while (bRet)
    {
        processes.push_back(pe32);
        bRet = Process32Next(hSnap, &pe32);
    }

    CloseHandle(hSnap);

    return processes;
}

