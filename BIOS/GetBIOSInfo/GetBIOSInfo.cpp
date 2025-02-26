// GetBIOSInfo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<Windows.h>

typedef struct tagRawSMBIOSData
{
    BYTE    Used20CallingMethod;
    BYTE    SMBIOSMajorVersion;
    BYTE    SMBIOSMinorVersion;
    BYTE    DmiRevision;
    DWORD   Length;
    BYTE    SMBIOSTableData[];
}RawSMBIOSData,*PRawSMBIOSData;

int main()
{
    UINT nSize = GetSystemFirmwareTable('ACPI', 0, NULL, 0);

    if (nSize == 0)
        return 0;

    PRawSMBIOSData pRawBiosData = NULL;

    BYTE* buf = new BYTE[nSize];


    if (GetSystemFirmwareTable('RSMB', 0, buf, nSize) != nSize)
        return 0;

    pRawBiosData = (PRawSMBIOSData)buf;

    delete[] buf;
    return 0;
}
