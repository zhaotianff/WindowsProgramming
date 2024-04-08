// RemoteThreadDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "inject.h"



int main()
{
    CreateRemoteThreadInject(30112, LR"(E:\project\github\Master-Zhao\Master-Zhao\x64\Debug\net6.0-windows\MasterZhaoCoreShellHook.dll)");
}