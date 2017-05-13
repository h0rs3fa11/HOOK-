/*
module:MyHookDll.h
*/
#ifdef MYHOOKAPI
#define MYHOOKAPI extern "C" __declspec(dllexport)
#else
#define MYHOOKAPI extern "C" __declspec(dllimport)
#endif
#define HM_KEY WM_USER + 101

MYHOOKAPI BOOL HookStart();
MYHOOKAPI void HookStop();