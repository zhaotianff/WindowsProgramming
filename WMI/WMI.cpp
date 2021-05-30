// WMI.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _WIN32_DCOM

#include <iostream>
#include <WbemIdl.h>
#include<Windows.h>
#include <comdef.h>
#include<vector>

#pragma comment(lib,"wbemuuid.lib")

void GetWMIDataSync();
void EnumWMIData();
void CallWMIProviderMethod();
void EnumWMIMethod();

int main()
{
	EnumWMIMethod();
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

	//连接WMI
	hr = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);

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
	//使用IWbemServices指针创建WMI请求 
	IEnumWbemClassObject* pEnumerator = NULL;
	pSvc->ExecQuery(bstr_t("WQL"),
		bstr_t("Select * from win32_OperatingSystem"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(hr))
	{
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return;
	}

	//获取数据
	IWbemClassObject* pclsObj = NULL;
	ULONG uReturn = 0;

	while (pEnumerator)
	{
		hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

		if (0 == uReturn)
		{
			break;
		}

		VARIANT vtProp{};
		hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);

		std::wcout << "OS Name : " << vtProp.bstrVal << std::endl;

		VariantClear(&vtProp);
		pclsObj->Release();
	}

	pSvc->Release();
	pLoc->Release();
	pEnumerator->Release();
	CoUninitialize();
}

void EnumWMIData()
{
	HRESULT hr;
	std::vector<VARIANT> bb{};

	hr = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		std::cout << "COM初始化失败.错误码 = 0x" << std::hex << hr << std::endl;
		return;
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
		return;
	}

	IWbemServices* pSvc = NULL;

	hr = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);
	if (FAILED(hr))
	{
		std::cout << "连接WMI失败.错误码 = 0x" << std::hex << hr << std::endl;
		pLoc->Release();
		CoUninitialize();
		return;
	}

	IEnumWbemClassObject* pEnumerator = NULL;
	hr = pSvc->ExecQuery(_bstr_t(L"WQL"), _bstr_t(L"Select * from win32_OperatingSystem"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(hr))
	{
		std::cout << "查询Win32_OperatingSystem失败.错误码 = 0x" << std::hex << hr << std::endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return;
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

				std::wcout << name << "\t" << vtProp.bstrVal << std::endl;
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
}

void CallWMIProviderMethod()
{
	HRESULT hr;
	hr = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		return;
	}

	hr = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
	if (FAILED(hr))
	{
		CoUninitialize();
		return;
	}

	IWbemLocator* pLoc = NULL;
	hr = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
	if (FAILED(hr))
	{
		CoUninitialize();
		return;
	}

	IWbemServices* pSvc = NULL;
	hr = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0,0, &pSvc);
	if (FAILED(hr))
	{
		pLoc->Release();
		CoUninitialize();
		return;
	}

	hr = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
	if (FAILED(hr))
	{
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return;
	}

	BSTR methodName = SysAllocString(L"Create");
	BSTR className = SysAllocString(L"Win32_Process");

	IWbemClassObject* pClass = NULL;
	hr = pSvc->GetObjectW(className, 0, NULL, &pClass, NULL);

	IWbemClassObject* pInParamDefinition = NULL;
	hr = pClass->GetMethod(methodName, 0, &pInParamDefinition, NULL);

	IWbemClassObject* pClassInstance = NULL;
	hr = pInParamDefinition->SpawnInstance(0, &pClassInstance);

	VARIANT varCommand;
	VariantInit(&varCommand);
	varCommand.vt = VT_BSTR;
	varCommand.bstrVal = _bstr_t(L"notepad.exe");

	hr = pClassInstance->Put(L"CommandLine", 0, &varCommand, 0);

	IWbemClassObject* pOutParams = NULL;
	hr = pSvc->ExecMethod(className, methodName, 0, NULL, pClassInstance, &pOutParams, NULL);

	if (FAILED(hr))
	{
		VariantClear(&varCommand);
		SysFreeString(className);
		SysFreeString(methodName);
		pClass->Release();
		pClassInstance->Release();
		pInParamDefinition->Release();
		pOutParams->Release();
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return;
	}

	VARIANT varReturnValue;
	VariantInit(&varReturnValue);
	hr = pOutParams->Get(BSTR(L"ReturnValue"), 0, &varReturnValue, NULL, 0);

	if (SUCCEEDED(hr))
	{
		VariantClear(&varReturnValue);
	}
	VariantClear(&varCommand);
	SysFreeString(className);
	SysFreeString(methodName);
	pClass->Release();
	pClassInstance->Release();
	pInParamDefinition->Release();
	pOutParams->Release();
	pLoc->Release();
	pSvc->Release();
	CoUninitialize();
}

void EnumWMIMethod()
{
	HRESULT hr;
	hr = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		return;
	}

	hr = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
	if (FAILED(hr))
	{
		CoUninitialize();
		return;
	}

	IWbemLocator* pLoc = NULL;
	hr = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
	if (FAILED(hr))
	{
		CoUninitialize();
		return;
	}

	IWbemServices* pSvc = NULL;
	hr = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);
	if (FAILED(hr))
	{
		pLoc->Release();
		CoUninitialize();
		return;
	}

	hr = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
	if (FAILED(hr))
	{
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return;
	}

	BSTR className = SysAllocString(L"Win32_NetworkAdapter");

	IWbemClassObject* pClass = NULL;
	hr = pSvc->GetObjectW(className, 0, NULL, &pClass, NULL);

	IWbemClassObject* pInParamDefinition = NULL;
	IWbemClassObject* pOutParamDefinition = NULL;
	hr = pClass->BeginMethodEnumeration(WBEM_FLAG_LOCAL_ONLY);

	if (SUCCEEDED(hr))
	{
		BSTR name = NULL;
		while (pClass->NextMethod(0, &name, &pInParamDefinition, &pOutParamDefinition) == WBEM_S_NO_ERROR)
		{
			std::wcout << name << std::endl;
		}
	}

	if (FAILED(hr))
	{
		SysFreeString(className);
		pClass->Release();
		if (pInParamDefinition != NULL)
		{
			pInParamDefinition->Release();
		}
		if (pOutParamDefinition != NULL)
		{
			pOutParamDefinition->Release();
		}
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return;
	}

	SysFreeString(className);
	pClass->Release();
	if (pInParamDefinition != NULL)
	{
		pInParamDefinition->Release();
	}
	if (pOutParamDefinition != NULL)
	{
		pOutParamDefinition->Release();
	}
	pLoc->Release();
	pSvc->Release();
	CoUninitialize();
}
