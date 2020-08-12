#pragma once

/*****************************************************************************
*                                                                            *
*  ¥≈≈Ãœ‡πÿ                                                                  *
*  Copyright (C) 2020 https://github.com/zhaotianff                          *
*  All rights reserved.                                                      *
*  Licensed under the MIT License.                                           *
*                                                                            *
*****************************************************************************/

#include<Windows.h>
#include<iostream>
#include <sstream>
#include <iomanip>
#include<shlobj_core.h>

#pragma comment(lib,"Shell32.lib")
#pragma comment(lib,"Winmm.lib")

using namespace std;

VOID GetDiskDriverVolumnName();
VOID GetDiskDriverSpaceByDriverName(LPTSTR driver);
VOID FormatDriverByDriverName(LPTSTR driver);
VOID SetDiskDriverLabel(LPTSTR driver, LPTSTR);
VOID MonitorDiskFile(LPTSTR lpPath);
VOID EjectCD();

