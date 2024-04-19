// Mailslots_Reading.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<Windows.h>
#include<tchar.h>
#include<strsafe.h>

#define DEMO_SLOT_NAME L"\\\\.\\mailslot\\demo_slot"

HANDLE MakeSlot(LPCTSTR lpszSlotName)
{
    HANDLE hSlot = CreateMailslot(lpszSlotName,
        0,
        MAILSLOT_WAIT_FOREVER,
        NULL);

    if (hSlot == INVALID_HANDLE_VALUE)
    {
        std::cout << "CreateMailSlot failed with " << GetLastError() << std::endl;
        return NULL;
    }
    else
    {
        std::cout << "CreateMailSlot successfully." << std::endl;
        return hSlot;
    }
}

BOOL ReadSlot(HANDLE hSlot)
{
    DWORD cbMessage, cMessage, cbRead;
    BOOL bResult;
    LPTSTR lpszBuffer;
    HANDLE hEvent = NULL;
    OVERLAPPED ov;

    cbMessage = cMessage = cbRead = 0;

    hEvent = CreateEvent(NULL, FALSE, FALSE, L"DemoSlotEvent");
    if (hEvent == NULL)
        return FALSE;

    ov.Offset = 0;
    ov.OffsetHigh = 0;
    ov.hEvent = hEvent;

    if (hSlot == NULL)
        return FALSE;

    bResult = GetMailslotInfo(hSlot,     //mailslot handle
        NULL,                            //no maximum message size
        &cbMessage,                      //size of next message
        &cMessage,                       //number of messages
        NULL);                           //no read time-out

    if (!bResult)
    {
        std::cout << "GetMailSlotInfo failed with " << GetLastError() << std::endl;
        return FALSE;
    }

    if (cbMessage == MAILSLOT_NO_MESSAGE)
    {
        std::cout << "waiting for a message" << std::endl;
        return TRUE;
    }

    //retreive all message
    while (cMessage != 0)
    {
        lpszBuffer = (LPTSTR)GlobalAlloc(GPTR, cbMessage);

        if (NULL == lpszBuffer)
            return FALSE;

        lpszBuffer[0] = '\0';

        bResult = ReadFile(hSlot, lpszBuffer, cbMessage, &cbRead, &ov);

        if (!bResult)
        {
            std::cout << "ReadFile failed with " << GetLastError() << std::endl;
            GlobalFree((HGLOBAL)lpszBuffer);
            CloseHandle(hEvent);
            return FALSE;
        }

        std::wcout << L"From Slot:" << lpszBuffer << std::endl;

        GlobalFree((HGLOBAL)lpszBuffer);

        bResult = GetMailslotInfo(hSlot, NULL, &cbMessage, &cMessage, NULL);

        if (!bResult)
        {
            CloseHandle(hEvent);
            std::cout << "GetMailslotInfo failed " << GetLastError() << std::endl;
            return FALSE;
        }
    }

    CloseHandle(hEvent);
    return TRUE;

}

int main()
{
    HANDLE hSlot = MakeSlot(DEMO_SLOT_NAME);

    while (TRUE)
    {
        ReadSlot(hSlot);
        Sleep(1000);
    }

    CloseHandle(hSlot);
}
