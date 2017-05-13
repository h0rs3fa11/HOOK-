#include<windows.h>
#include<stdio.h>
#define MYHOOKAPI extern "C" __declspec(dllexport)

#include"MyHookDll.h"

#pragma data_seg("Shared")
#define PROCESS_NAME "notepad.exe"
HWND g_hWndCaller = NULL;	// ±£´æÖ÷´°¿Ú¾ä±ú
HHOOK HookMsg;
#pragma data_seg()

HMODULE WINAPI ModuleFromAddress(PVOID pv)
{
	MEMORY_BASIC_INFORMATION mbi;
	if (::VirtualQuery(pv, &mbi, sizeof(mbi)) != 0)
	{
		return (HMODULE)mbi.AllocationBase;
	}
	else
	{
		return NULL;
	}
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	CHAR szBuf[128];
	HDC hdc;
	static int c = 0;
	size_t cch;
	HRESULT hResult;
	char szPath[MAX_PATH] = { 0 };
	char *p = NULL;
	GetModuleFileNameA(NULL, szPath, MAX_PATH);
	p = strrchr(szPath, '\\');

	if (nCode >= 0 && !_stricmp(p+1,PROCESS_NAME))
	{
		if (!(lParam & 0x80000000))
		{
			HWND hWnd = ::FindWindow(NULL, "¼üÅÌ¼ÇÂ¼Æ÷");
			PostMessage(hWnd, HM_KEY, wParam, lParam);
			//return 1;
		}
	}
	return CallNextHookEx(HookMsg, nCode, wParam, lParam);
}

BOOL HookStart()
{
	BOOL bol = 1;
	HookMsg = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, ModuleFromAddress(KeyboardProc), 0);
	if (HookMsg == NULL)
	{
		bol = 0;
	}
	return bol;
}

void HookStop()
{
	UnhookWindowsHookEx(HookMsg);
}