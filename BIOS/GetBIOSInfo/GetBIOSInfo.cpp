// GetBIOSInfo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<Windows.h>
#include<map>
#include<string>

typedef struct tagRawSMBIOSData
{
    BYTE    Used20CallingMethod;
    BYTE    SMBIOSMajorVersion;
    BYTE    SMBIOSMinorVersion;
    BYTE    DmiRevision;
    DWORD   Length;
    BYTE    SMBIOSTableData[];
}RawSMBIOSData,*PRawSMBIOSData;

typedef struct SMBIOSHeader {
    BYTE    Type;         // 结构类型    
    BYTE    Length;       // 该类型结构的格式化区域长度(请注意，长度取决于主板或系统支持的具体版本)    
    WORD    Handle;       // 结构句柄(0～0xFEFF范围内的数字)
}*PSMBIOSHeader;

#pragma pack(1)
// 系统信息(Type 1)SMBIOS结构的格式化区域的完整定义
typedef struct _Type1SystemInformation
{
    SMBIOSHeader m_sHeader;       // SMBIOS结构头SMBIOSStructHeader
    BYTE    m_bManufacturer;      // Manufacturer字符串的编号
    BYTE    m_bProductName;       // Product Name字符串的编号
    BYTE    m_bVersion;           // Version字符串的编号
    BYTE    m_bSerialNumber;      // BIOS Serial Number字符串的编号
    UUID    m_uuid;               // UUID
    BYTE    m_bWakeupType;        // 标识导致系统启动的事件(原因)
    BYTE    m_bSKUNumber;         // SKU Number字符串的编号
    BYTE    m_bFamily;            // Family字符串的编号
}Type1SystemInformation, * PType1SystemInformation;

typedef struct _Type28TemperatureProbe
{
    BYTE 	Type;
    BYTE 	Length;
    WORD 	Handle;
    BYTE 	Description;
    BYTE 	Location;
    WORD 	Maximum;
    WORD 	Minimum;
    WORD 	Resolution;
    WORD 	Tolerance;
    WORD 	Accuracy;
    DWORD 	OEM;
    WORD 	Nominal;
}Type28TemperatureProbe, * PType28TemperatureProbe;

LPSTR FindStrFromSMBIOSDataStruct(PSMBIOSHeader pStructHeader, BYTE bNum)
{
    // 指向SMBIOS结构的未格式化区域(字符串数组)
    LPBYTE lpByte = (LPBYTE)pStructHeader + pStructHeader->Length;

    // 字符串编号从1开始
    for (BYTE i = 1; i < bNum; i++)
        lpByte += strlen((LPSTR)lpByte) + 1;

    return (LPSTR)lpByte;
}

std::map<BYTE, std::string> wakeUpTypeMap = {
        {0, "Reserved"},
        {1, "Other"},
        {2, "Unknown"},
        {3, "APM Timer"},
        {4, "Modem Ring"},
        {5, "LAN Remote"},
        {6, "Power Switch"},
        {7, "PCI PME#"},
        {8, "AC Power Restored"}
};

int main()
{
    UINT nSize = GetSystemFirmwareTable('RSMB', 0, NULL, 0);

    if (nSize == 0)
        return 0;

    PRawSMBIOSData pRawBiosData = NULL;
    PSMBIOSHeader pStructHeader = NULL;

    BYTE* buf = new BYTE[nSize];


    if (GetSystemFirmwareTable('RSMB', 0, buf, nSize) != nSize)
        return 0;

    pRawBiosData = (PRawSMBIOSData)buf;

    //当前指针位置
    auto lpData = pRawBiosData->SMBIOSTableData;

    while ((lpData - pRawBiosData->SMBIOSTableData) < pRawBiosData->Length)
    {
        // 根据SMBIOS结构的格式化区域中的结构头的Type字段确定结构类型
        // 确定结构类型以后再把pStructHeader转换为指向对应的格式化区域完整定义的指针
        pStructHeader = (PSMBIOSHeader)lpData;

        switch (pStructHeader->Type)
        {
        case 1: //Type 1
        {
            PType1SystemInformation pType1 = (PType1SystemInformation)pStructHeader;
  
            std::cout << "********************* System Info *********************" << std::endl;
            std::cout << "Manufacturer: " << FindStrFromSMBIOSDataStruct(pStructHeader, pType1->m_bManufacturer) << std::endl;
            std::cout << "ProductName: " << FindStrFromSMBIOSDataStruct(pStructHeader, pType1->m_bProductName) << std::endl;
            std::cout << "Version: " << FindStrFromSMBIOSDataStruct(pStructHeader, pType1->m_bVersion) << std::endl;
            std::cout << "SerialNumber: " << FindStrFromSMBIOSDataStruct(pStructHeader, pType1->m_bSerialNumber) << std::endl;
            std::cout << "SKUNumber: " << FindStrFromSMBIOSDataStruct(pStructHeader, pType1->m_bSKUNumber) << std::endl;
            std::cout << "Family: " << FindStrFromSMBIOSDataStruct(pStructHeader, pType1->m_bFamily) << std::endl;
            std::cout << "WakeupType: " << wakeUpTypeMap.find(pType1->m_bWakeupType)->second << std::endl;
            std::cout << std::endl;
            
        }
        case 28:
        {
            PType28TemperatureProbe pType28 = (PType28TemperatureProbe)pStructHeader;

            std::cout << "********************* Temperature Probe *********************" << std::endl;
            std::cout << "Accuracy: " << pType28->Accuracy << std::endl;
            std::cout << "Description: " << FindStrFromSMBIOSDataStruct(pStructHeader, pType28->Description) << std::endl;
            std::cout << "Handle: " << pType28->Handle << std::endl;
            std::cout << "Length: " << pType28->Length << std::endl;
            std::cout << "Location: " << (int)pType28->Location << std::endl;
            std::cout << "Maximum: " << pType28->Maximum << std::endl;
            std::cout << "Minimum: " << pType28->Minimum << std::endl;
            std::cout << "Nominal: " << pType28->Nominal << std::endl;
            std::cout << "OEM: " << pType28->OEM << std::endl;
            std::cout << "Resolution: " << pType28->Resolution << std::endl;
            std::cout << "Tolerance: " << pType28->Tolerance << std::endl;
            std::cout << "Type: " << (int)pType28->Type << std::endl;
            std::cout << std::endl;
        }
            break;
        default:
            break;
        }


        // 遍历完格式化区域
        lpData += pStructHeader->Length;

        // 跳过未格式化区域
        while ((*(LPWORD)lpData) != 0)
        {
            lpData++;
        }

        // 末尾 加2字节
        lpData += 2;
    }

    delete[] buf;
    return 0;
}
