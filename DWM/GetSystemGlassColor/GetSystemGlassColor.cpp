// GetSystemGlassColor.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define SYS_VER_GREATER_THAN_WIN8

#include <iostream>
#include<Windows.h>

//from https://github.com/Open-Shell/Open-Shell-Menu.git 
//SkinManager.cpp

struct DWMCOLORIZATIONPARAMS
{
	DWORD ColorizationColor;
	DWORD ColorizationAfterglow;
	DWORD ColorizationColorBalance;
	DWORD ColorizationAfterglowBalance;
	DWORD ColorizationBlurBalance;
	DWORD ColorizationGlassReflectionIntensity;
	DWORD ColorizationOpaqueBlend;
	DWORD extra; // Win8 has extra parameter
};

BOOL GetSkinColorizationParameters(DWMCOLORIZATIONPARAMS* params)
{
	typedef HRESULT(WINAPI* tGetColorizationParameters)(DWMCOLORIZATIONPARAMS* params);

	// HACK: the system function DwmGetColorizationColor is buggy on Win 7. its calculations can overflow and return a totally wrong value
	// (try orange color with full intensity and no transparency - you'll get alpha=0 and green color). so here we use the undocumented
	// function GetColorizationParameters exported by dwmapi.dll, ordinal 127 and then compute the colors manually using integer math
	HMODULE hMod = LoadLibrary(L"dwmapi.dll");
	if (!hMod) return false;
	tGetColorizationParameters GetColorizationParameters = (tGetColorizationParameters)GetProcAddress(hMod, MAKEINTRESOURCEA(127));
	if (!GetColorizationParameters || FAILED(GetColorizationParameters(params)))
		return false;
#ifdef SYS_VER_GREATER_THAN_WIN8
	params->ColorizationOpaqueBlend = 0; // Win8 has no transparency
#endif

	if (hMod)
		FreeLibrary(hMod);
	return true;
}

COLORREF GetSystemGlassColor8(void)
{
	COLORREF color = 0;
	DWMCOLORIZATIONPARAMS params;
	if (GetSkinColorizationParameters(&params))
	{
		int r = (params.ColorizationColor >> 16) & 255;
		int g = (params.ColorizationColor >> 8) & 255;
		int b = (params.ColorizationColor) & 255;
		int gray = 217 * (100 - params.ColorizationColorBalance) + 50;
		r = (r * params.ColorizationColorBalance + gray) / 100;
		g = (g * params.ColorizationColorBalance + gray) / 100;
		b = (b * params.ColorizationColorBalance + gray) / 100;
		r = (r * 200 + 127) / 255;
		g = (g * 200 + 127) / 255;
		b = (b * 200 + 127) / 255;
		color = (r << 16) | (g << 8) | b | (params.ColorizationColor & 0xFF000000);
	}
	return color;
}

int main()
{
	COLORREF color = GetSystemGlassColor8();
}
