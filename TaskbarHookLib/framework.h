﻿// header.h: 标准系统包含文件的包含文件，
// 或特定于项目的包含文件
//

#pragma once

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
#include<string>
#include<Shlwapi.h>
#include<wincodec.h>
#include<wrl/client.h>
#include<Psapi.h>

#pragma comment(lib,"shlwapi.lib")

