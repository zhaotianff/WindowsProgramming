#include"TaskbarHook.h"

BOOL CreateTaskbarHook()
{
    HWND hwndProgMan = FindWindowEx(NULL, NULL, L"Progman", NULL);

    DWORD process = 0;
    DWORD thread = GetWindowThreadProcessId(hwndProgMan, &process);
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, process);

    wchar_t path[MAX_PATH];
    if (GetModuleFileNameEx(hProcess, NULL, path, _countof(path)))
    {
        if (_wcsicmp(PathFindFileName(path), L"explorer.exe") != 0)
            return FALSE;
    }
    CloseHandle(hProcess);

    thread = GetWindowThreadProcessId(g_TaskBar, NULL);
    g_hook = SetWindowsHookEx(WH_GETMESSAGE, GetMessageProc, g_hModule, thread);
    PostMessage(g_TaskBar, WM_NULL, 0, 0); // make sure there is one message in the queue

    return true;
}


BOOL CALLBACK FindTaskBarEnum(HWND hwnd, LPARAM lParam)
{
    // look for top-level window with class "Shell_TrayWnd" and process ID=lParam
    DWORD process;
    GetWindowThreadProcessId(hwnd, &process);
    if (process != lParam) return TRUE;
    wchar_t name[256];
    GetClassName(hwnd, name, _countof(name));
    if (_wcsicmp(name, L"Shell_TrayWnd") != 0) return TRUE;
    g_TaskBar = hwnd;
    return FALSE;
}

HWND FindTaskBar(DWORD dwProcessId)
{
    // find the taskbar
    EnumWindows(FindTaskBarEnum, dwProcessId);
    if (!g_TaskBar)
        g_TaskBar = FindWindowEx(GetDesktopWindow(), NULL, L"Shell_TrayWnd", NULL);
    return g_TaskBar;
}

LRESULT GetMessageProc(int code, WPARAM wParam, LPARAM lParam)
{
    if (code == HC_ACTION && !g_TaskBar)
        InitStartMenuDLL();
    return CallNextHookEx(NULL, code, wParam, lParam);
}

VOID InitStartMenuDLL()
{
    if (bInitCalled)
        return;

    bInitCalled = TRUE;

    //IatHooks?

    HMODULE dwn = GetModuleHandle(L"dwmapi.dll");
}