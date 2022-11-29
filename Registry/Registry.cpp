// Registry.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<Windows.h>
#include<strsafe.h>
#include <stdio.h>
#include <tchar.h>

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

#define STARTUP_RUN LR"(Software\Microsoft\Windows\CurrentVersion\Run)"

TCHAR  achValue[MAX_VALUE_NAME];
DWORD cchValue = MAX_VALUE_NAME;

void QueryKey(HKEY hKey);

void QueryKey(HKEY hKey)
{
    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string 
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
    DWORD    cchClassName = MAX_PATH;  // size of class string 
    DWORD    cSubKeys = 0;               // number of subkeys 
    DWORD    cbMaxSubKey;              // longest subkey size 
    DWORD    cchMaxClass;              // longest class string 
    DWORD    cValues;              // number of values for key 
    DWORD    cchMaxValue;          // longest value name 
    DWORD    cbMaxValueData;       // longest value data 
    DWORD    cbSecurityDescriptor; // size of security descriptor 
    FILETIME ftLastWriteTime;      // last write time 

    DWORD i, retCode;


    // Get the class name and the value count. 
    retCode = RegQueryInfoKey(
        hKey,                    // key handle 
        achClass,                // buffer for class name 
        &cchClassName,           // size of class string 
        NULL,                    // reserved 
        &cSubKeys,               // number of subkeys 
        &cbMaxSubKey,            // longest subkey size 
        &cchMaxClass,            // longest class string 
        &cValues,                // number of values for this key 
        &cchMaxValue,            // longest value name 
        &cbMaxValueData,         // longest value data 
        &cbSecurityDescriptor,   // security descriptor 
        &ftLastWriteTime);       // last write time 

    // Enumerate the subkeys, until RegEnumKeyEx fails.

    if (cSubKeys)
    {
        printf("\nNumber of subkeys: %d\n", cSubKeys);

        for (i = 0; i < cSubKeys; i++)
        {
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(hKey, i,
                achKey,
                &cbName,
                NULL,
                NULL,
                NULL,
                &ftLastWriteTime);
            if (retCode == ERROR_SUCCESS)
            {
                _tprintf(TEXT("(%d) %s\n"), i + 1, achKey);
            }
        }
    }

    // Enumerate the key values. 

    if (cValues)
    {
        printf("\nNumber of values: %d\n", cValues);

        for (i = 0, retCode = ERROR_SUCCESS; i < cValues; i++)
        {
            cchValue = MAX_VALUE_NAME;
            achValue[0] = '\0';
            retCode = RegEnumValue(hKey, i,
                achValue,
                &cchValue,
                NULL,
                NULL,
                NULL,
                NULL);

            if (retCode == ERROR_SUCCESS)
            {
                _tprintf(TEXT("(%d) %s\n"), i + 1, achValue);
            }
        }
    }
}

int main()
{
    HKEY hKey = NULL;
    auto result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, STARTUP_RUN, 0, KEY_READ | KEY_ENUMERATE_SUB_KEYS | KEY_WOW64_32KEY, &hKey);

    if (ERROR_SUCCESS == result)
    {
        QueryKey(hKey);
        RegCloseKey(hKey);
    }
    return 0;
}