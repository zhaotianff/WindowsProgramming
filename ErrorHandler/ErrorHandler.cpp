// ErrorHandler.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<Windows.h>

using namespace std;

BOOL ShowErrorInfo(DWORD errorCode);
int main()
{
    //当Windows 函数检测到错误时，会使用一种名为“线程本地存储区”（thread-local storeage）的机制将相应的错误代码与
    //调用线程关联到一起
    //这种机制使不同的线程能独立运行，不会出现相互干扰对方的错误代码的情况
    //使用GetLastError()函数来获取函数执行的错误
    //需要注意的时，由于是所有的线程错误都存储在一个位置，所以当发生错误后，要马上调用GetLastError()函数来获取错误码，否则结果可能不对了


    //使用监视窗口的$err,hr可以查看错误代码具体代表什么意思

    DWORD dwErrorCode = 0x02;
    ShowErrorInfo(dwErrorCode);

}

BOOL ShowErrorInfo(DWORD errorCode)
{
   
    PCTSTR lpszErrorInfo = NULL;

    HLOCAL hlocal = NULL;  //存储错误信息字符串的缓冲区
    DWORD systemLocale = MAKELANGID(LANG_NEUTRAL,SUBLANG_NEUTRAL); //使用操作系统默认的语言

    BOOL fOK = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER,
        NULL,errorCode,systemLocale,
        (PTSTR)&hlocal, 0, NULL);

    if (!fOK)
    {
        //网络相关的错误
        HMODULE hDll = LoadLibraryEx(L"netmsg.dll", NULL, DONT_RESOLVE_DLL_REFERENCES);

        if (hDll)
        {
            fOK = FormatMessage(FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER,
                hDll, errorCode, systemLocale,
                (PTSTR)&hlocal, 0, NULL);
        }
    }
    
    if (fOK && (hlocal != NULL))
    {
        lpszErrorInfo = (PCTSTR)LocalLock(hlocal);   

        //测试输出
        //打印中文须先设置本地语言为中文
        setlocale(LC_ALL, "chs");     
        std::wcout << lpszErrorInfo << std::endl;

        LocalFree(hlocal);
        return TRUE;
    }
    else
    {
        lpszErrorInfo = L"";
        return FALSE;
    }
}