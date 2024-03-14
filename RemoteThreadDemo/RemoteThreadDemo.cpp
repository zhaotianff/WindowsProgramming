// RemoteThreadDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "inject.h"



int main()
{
    CreateRemoteThreadInject(34580, LR"(E:\project\github\WindowsProgramming\x64\Debug\RemoteThread_lib.dll)");
}