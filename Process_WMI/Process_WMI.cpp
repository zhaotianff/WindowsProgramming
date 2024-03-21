// Process_WMI.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <WbemIdl.h>
#include<Windows.h>
#include <comdef.h>
#include<vector>

#pragma comment(lib,"wbemuuid.lib")

int main()
{
	HRESULT hr;
	std::vector<VARIANT> bb{};

	hr = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		std::cout << "COM初始化失败.错误码 = 0x" << std::hex << hr << std::endl;
		return 0;
	}

	hr = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
	if (FAILED(hr))
	{
		std::cout << "初始化安全性失败.错误码 = 0x" << std::hex << hr << std::endl;
	}

	IWbemLocator* pLoc = NULL;
	hr = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
	if (FAILED(hr))
	{
		std::cout << "创建IWbemLocator对象失败.错误码 = 0x" << std::hex << hr << std::endl;
		CoUninitialize();
		return 0;
	}

	IWbemServices* pSvc = NULL;

	hr = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);
	if (FAILED(hr))
	{
		std::cout << "连接WMI失败.错误码 = 0x" << std::hex << hr << std::endl;
		pLoc->Release();
		CoUninitialize();
		return 0;
	}

	IEnumWbemClassObject* pEnumerator = NULL;
	hr = pSvc->ExecQuery(_bstr_t(L"WQL"), _bstr_t(L"Select * from win32_process"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(hr))
	{
		std::cout << "查询win32_process失败.错误码 = 0x" << std::hex << hr << std::endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return 0;
	}

	IWbemClassObject* pclsObj = NULL;
	ULONG uReturn = 0;

	while (pEnumerator)
	{
		hr = pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);

		if (0 == uReturn)
		{
			break;
		}

		if (pclsObj->BeginEnumeration(WBEM_FLAG_NONSYSTEM_ONLY) == WBEM_S_NO_ERROR)
		{
			BSTR name = NULL;
			VARIANT vtProp;
			VariantInit(&vtProp);

			while (pclsObj->Next(0, &name, &vtProp, 0, 0) == WBEM_S_NO_ERROR)
			{
				bb.push_back(vtProp);

				//这里暂时只输出字符串
				if (vtProp.vt == VT_NULL || vtProp.vt != VT_BSTR)
					continue;

				//std::wcout << name << "\t" << vtProp.bstrVal << std::endl;
			}

			SysFreeString(name);
			VariantClear(&vtProp);
		}
		pclsObj->Release();
	}

	pEnumerator->Release();
	pSvc->Release();
	pLoc->Release();
	CoUninitialize();

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
