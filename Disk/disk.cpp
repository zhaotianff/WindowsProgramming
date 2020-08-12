#include "disk.h"

void GetDiskDriverVolumnName()
{
	DWORD dwSize = GetLogicalDriveStrings(0, nullptr);


	if (dwSize != 0)
	{
		LPTSTR lp = new TCHAR[dwSize * sizeof(TCHAR)];

		GetLogicalDriveStrings(dwSize * sizeof(TCHAR), lp);

		LPTSTR lpTemp = lp;

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
				wcout << lp << "  " << lpNameBuf << " " << hex << dwSerialNumber << endl;

				/*
				* hex 十六进制
				* oct 八进制
				* dec 十进制
				*/

				delete[] lpSysNameBuf;
				delete[] lpNameBuf;
			}

			lp = wcschr(lp, 0) + 1;
		}

		lp = lpTemp;
		delete[] lp;
	}

}

void GetDiskDriverSpaceByDriverName(LPTSTR driver)
{
	ULARGE_INTEGER nFreeBytesAvailableToCaller;
	ULARGE_INTEGER nTotalNumberOfBytes;
	ULARGE_INTEGER nTotalNumberOfFreeBytes;
	auto result = GetDiskFreeSpaceEx(driver, &nFreeBytesAvailableToCaller, &nTotalNumberOfBytes, &nTotalNumberOfFreeBytes);

	if (result != 0)
	{
		std::wstringstream wss;
		wss << "Drive:" << driver << " total size: "
			<< nTotalNumberOfBytes.QuadPart << " bytes "
			<< "available size: "
			<< nTotalNumberOfFreeBytes.QuadPart << " bytes ";
		wcout << wss.str() << endl;
	}
}


void FormatDriverByDriverName(LPTSTR driver)
{
	UINT driveID = driver[0] - 'A';
	//代码未启用，谨防误操作
	//SHFormatDrive(GetConsoleWindow(),driveID, SHFMT_ID_DEFAULT,0);
}

void SetDiskDriverLabel(LPTSTR driver, LPTSTR lable)
{
	SetVolumeLabel(driver, lable);
}

VOID MonitorDiskFile(LPTSTR lpPath)
{
	HANDLE handle = FindFirstChangeNotification(lpPath, TRUE, FILE_NOTIFY_CHANGE_FILE_NAME);

	/*
	FILE_NOTIFY_CHANGE_FILE_NAME
	Any file name change in the watched directory or subtree causes a change notification wait operation to return. Changes include renaming, creating, or deleting a file name.

	FILE_NOTIFY_CHANGE_DIR_NAME
	Any directory-name change in the watched directory or subtree causes a change notification wait operation to return. Changes include creating or deleting a directory.

	FILE_NOTIFY_CHANGE_ATTRIBUTES
	Any attribute change in the watched directory or subtree causes a change notification wait operation to return.

	FILE_NOTIFY_CHANGE_SIZE
	Any file-size change in the watched directory or subtree causes a change notification wait operation to return. The operating system detects a change in file size only when the file is written to the disk. For operating systems that use extensive caching, detection occurs only when the cache is sufficiently flushed.

	FILE_NOTIFY_CHANGE_LAST_WRITE
	Any change to the last write-time of files in the watched directory or subtree causes a change notification wait operation to return. The operating system detects a change to the last write-time only when the file is written to the disk. For operating systems that use extensive caching, detection occurs only when the cache is sufficiently flushed.

	FILE_NOTIFY_CHANGE_SECURITY
	Any security-descriptor change in the watched directory or subtree causes a change notification wait operation to return.
	*/

	if (handle == INVALID_HANDLE_VALUE)
	{
		cout << "FindFirstChangeNotification failed" << endl;
		return;
	}

	DWORD result = WaitForSingleObject(handle, INFINITE);

	if (result == WAIT_FAILED)
	{
		cout << "wait failed" << endl;
	}
	else
	{
		cout << "disk file property changed" << endl;
	}

	//FindNextChangeNotification https://docs.microsoft.com/en-us/windows/desktop/api/fileapi/nf-fileapi-findnextchangenotification
}

VOID EjectCD()
{
	mciSendString(TEXT("set cdaudio door open"), NULL, 0, NULL);
}
