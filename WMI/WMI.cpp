// WMI.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _WIN32_DCOM

#include <iostream>
#include <WbemIdl.h>
#include<Windows.h>

#pragma comment(lib,"wbemuuid.lib")

void GetWMIDataSync();

int main()
{
    std::cout << "Hello World!\n";
}


void GetWMIDataSync()
{
	//初始化COM [MTAThread]
	HRESULT hr;
	hr = CoInitializeEx(0, COINIT_MULTITHREADED);

	if (FAILED(hr))
	{
		return;
	}

	//设置COM安全级别
	hr = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);

	if (FAILED(hr))
	{
		CoUninitialize();
		return;
	}

	//创建WMI命名空间的连接
	IWbemLocator* pLoc = NULL;

	hr = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);

	IWbemServices* pSvc = NULL;

	hr = pLoc->ConnectServer(BSTR(L"ROOT\\DEFAULT"), NULL, NULL, 0, NULL, 0, 0, &pSvc);

	if (FAILED(hr))
	{
		pLoc->Release();
		CoUninitialize();
		return;
	}

	//在代理上设置安全级别
	hr = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);

	if (FAILED(hr))
	{
		pSvc->Release();
		pLoc->Release();

		CoUninitialize();
	}

	//查询WMI对象
	//pSvc->ExecQueryAsync()



	//pSvc->Release();
	//pLoc->Release();
}
