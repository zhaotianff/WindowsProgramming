/*****************************************************************************
*                                                                            *
*  剪贴板相关                                                                *
*  Copyright (C) 2020 https://github.com/zhaotianff                          *
*  All rights reserved.                                                      *
*  Licensed under the MIT License.                                           *
*                                                                            *
*****************************************************************************/

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// 主符号


// CClipBoardApp:
// 有关此类的实现，请参阅 ClipBoard.cpp
//

class CClipBoardApp : public CWinApp
{
public:
	CClipBoardApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CClipBoardApp theApp;
