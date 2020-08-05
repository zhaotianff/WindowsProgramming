#include "disk.h"
#include <vector>
#include<string>
#include<iostream>
#include<windows.h>

using namespace std;

void GetDiskDriverVolumnName()
{
	DWORD dwSize = GetLogicalDriveStrings(0, nullptr);


	if (dwSize != 0)
	{
		
		HANDLE heap = GetProcessHeap();

		LPTSTR lp = (LPTSTR)HeapAlloc(heap, HEAP_ZERO_MEMORY, dwSize * sizeof(TCHAR));

		GetLogicalDriveStrings(dwSize * sizeof(TCHAR), lp);

		while (*lp != 0)
		{
			UINT nRes = GetDriveType(lp);

			if (nRes == DRIVE_FIXED)
			{
				LPTSTR lpNameBuf = new TCHAR[12];
				DWORD dwNameSize = 12;
				DWORD dwSerialNumber;
				DWORD dwMaxLen;
				DWORD dwFileFlag;
				LPTSTR lpSysNameBuf = new TCHAR[10];
				DWORD dwSysNameSize = 10;
				GetVolumeInformation(lp, lpNameBuf, dwNameSize, &dwSerialNumber, &dwMaxLen, &dwFileFlag, lpSysNameBuf, dwSysNameSize);
				wcout << lp <<"  "<< lpNameBuf<< endl;
			}

			lp = wcschr(lp, 0) + 1;
		}
	}

}

void GetDiskDriverType()
{

}
