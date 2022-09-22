// COM.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<Windows.h>
#include<ShObjIdl.h>
#include<ShObjIdl_core.h>

VOID CreateComObj()
{
    IVirtualDesktopManager* pDesktopManager = NULL;
    HRESULT hr = CoInitialize(NULL);

    if (SUCCEEDED(hr))
    {
        hr = CoCreateInstance(
            CLSID_VirtualDesktopManager,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_IVirtualDesktopManager, (void**)&pDesktopManager);

        if (SUCCEEDED(hr))
        {
            pDesktopManager->Release();
        }
    }

    CoUninitialize();
}

int main()
{
    std::cout << "Hello World!\n";
}
