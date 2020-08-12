#include <iostream>
#include<Windows.h>
#include"disk.h"

using namespace std;

int main()
{
	GetDiskDriverVolumnName();

	GetDiskDriverSpaceByDriverName(L"C:\\");

	//格式化磁盘 谨慎操作
	//FormatDriverByDriverName(L"G:\\");

	//监控磁盘文件变化 
	//MonitorDiskFile(TEXT("D:\\"));

	EjectCD();
}
