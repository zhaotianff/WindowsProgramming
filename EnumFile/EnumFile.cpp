// EnumFile.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<Windows.h>

VOID SearchFile(LPCTSTR pszDirectory)
{
	// 搜索指定类型文件
	DWORD dwBufferSize = 2048;
	TCHAR* pszFileName = NULL;
	TCHAR* pTempSrc = NULL;
	WIN32_FIND_DATA findData{};
	BOOL bRet = FALSE;

	// 申请动态内存
	pszFileName = new TCHAR[dwBufferSize];
	pTempSrc = new TCHAR[dwBufferSize];

	// 构造搜索文件类型字符串, *.*表示搜索所有文件类型
	wsprintf(pszFileName, L"%s\\*.*", pszDirectory);

	// 搜索第一个文件
	HANDLE hFile = FindFirstFile(pszFileName, &findData);
	if (INVALID_HANDLE_VALUE != hFile)
	{
		do
		{
			// 要过滤掉 当前目录"." 和 上一层目录"..", 否则会不断进入死循环遍历
			if ('.' == findData.cFileName[0])
			{
				continue;
			}
			// 拼接文件路径	
			wsprintf(pTempSrc, L"%s\\%s", pszDirectory, findData.cFileName);
			// 判断是否是目录还是文件
			if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				// 目录, 则继续往下递归遍历文件
				SearchFile(pTempSrc);
			}
			else
			{
				// 文件
				wprintf_s(L"%s\n", pTempSrc);
			}

			// 搜索下一个文件
		} while (FindNextFile(hFile, &findData));
	}

	// 关闭文件句柄
	FindClose(hFile);
	// 释放内存
	delete[]pTempSrc;
	pTempSrc = NULL;
	delete[]pszFileName;
	pszFileName = NULL;
}

int main()
{
	SearchFile(L"C:\\");
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
