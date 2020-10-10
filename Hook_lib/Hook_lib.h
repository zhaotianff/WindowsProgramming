
#ifdef HOOKLIB_EXPORTS
#define HOOKLIB_API __declspec(dllexport)
#else
#define HOOKLIB_API __declspec(dllimport)
#endif

HOOKLIB_API BOOL SetHook();
HOOKLIB_API BOOL UnsetHook();
