#pragma once
#include "framework.h"

HHOOK g_hook;
HWND g_TaskBar;

HMODULE g_hModule;
static BOOL bInitCalled = FALSE;

typedef VOID(WINAPI *tDwmpBeginTransitionRequest)(int param);
typedef VOID(WINAPI *tDwmpTransitionWindowWithRects)(HWND, int, RECT*, RECT*, RECT*, RECT*, RECT*);
typedef VOID(WINAPI* tDwmpEndTransitionRequest)(int param);

tDwmpBeginTransitionRequest g_DwmBeginTransitionRequest;
tDwmpTransitionWindowWithRects g_DwmTransitionWindowWithRects;
tDwmpEndTransitionRequest g_DwmpEndTransitionRequest;

BOOL CreateTaskbarHook();
LRESULT __stdcall GetMessageProc(int code, WPARAM wParam, LPARAM lParam);
HWND FindTaskBar(DWORD dwProcessId);
BOOL CALLBACK FindTaskBarEnum(HWND hwnd, LPARAM lParam);
VOID InitStartMenuDLL();
