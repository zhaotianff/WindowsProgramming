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

using namespace std;

void GetDiskDriverVolumnName();
void GetDiskDriverSpaceByDriverName(LPTSTR driver);
void FormatDriverByDriverName(LPTSTR driver);