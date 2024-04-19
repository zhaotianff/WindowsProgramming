// Mailslots_CreateAndWrite.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<Windows.h>

#define DEMO_SLOT_NAME L"\\\\.\\mailslot\\demo_slot"

HANDLE WINAPI MakeSlot(LPCTSTR lpszSlotName)
{
    HANDLE hSlot = CreateMailslot(lpszSlotName,
        0,                      //no maximum message size
        MAILSLOT_WAIT_FOREVER,  //no time-out for operations
        NULL);                  //default security

    if (hSlot == INVALID_HANDLE_VALUE)
    {
        std::cout << "Create mailslot failed with " 
            << GetLastError() 
            << std::endl;
        return NULL;
    }
    else
    {
        std::cout << "Create mailslot successfully." << std::endl;
        return hSlot;
    }
    
}

BOOL WriteSlot(LPCTSTR lpszSlotName, LPCTSTR lpszMessage)
{
    HANDLE hFile = CreateFile(lpszSlotName, GENERIC_WRITE, 
        FILE_SHARE_READ, NULL, OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        std::cout << "CreateFile failed with " << GetLastError() << std::endl;
        return FALSE;
    }

    DWORD cbWritten = 0;
    BOOL bResult = WriteFile(hFile,lpszMessage, (DWORD)(lstrlen(lpszMessage) * sizeof(TCHAR)),
        &cbWritten, NULL);

    if (!bResult)
    {
        std::cout << "WriteFile failed with " << GetLastError() << std::endl;
        CloseHandle(hFile);
        return FALSE;
    }
    else
    {
        std::wcout << L"Slot written to [" << lpszMessage << L"] successfully." << std::endl;
        CloseHandle(hFile);
        return TRUE;
    }
}

BOOL CloseSlot(HANDLE hSlot)
{
    if (hSlot)
    {
        return CloseHandle(hSlot);
    }

    return FALSE;
}

int main()
{
    HANDLE hSlot = MakeSlot(DEMO_SLOT_NAME);
    WriteSlot(DEMO_SLOT_NAME, L"HelloWorld");
    
    // A mailslot exists until the CloseHandle function is called for all open server handles or 
    // until all server processes that own a mailslot handle exit. 
    // In both cases, any unread messages are deleted from the mailslot, 
    // all client handles to the mailslot are closed, 
    // and the mailslot itself is deleted from memory.
    //CloseHandle(hSlot);
    return 0;
}