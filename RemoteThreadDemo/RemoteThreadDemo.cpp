// RemoteThreadDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "inject.h"



int main()
{
    CreateRemoteThreadInject(8448, LR"(E:\project\github\WindowsX\WindowsX\x64\Debug\net6.0-windows\WindowsXCoreShellHook.dll)");
}