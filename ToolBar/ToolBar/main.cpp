#include <Windows.h>
#include <GdiPlus.h>
#include "ToolBarWindow.h"
#pragma  comment(lib,"GdiPlus.lib")
using namespace Gdiplus;
int WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd )
{
	SetErrorMode(SEM_FAILCRITICALERRORS|SEM_NOGPFAULTERRORBOX);
	HANDLE hMutexOneInstance = ::CreateMutex(NULL, TRUE,"_ToolBar_");
	if(GetLastError() == ERROR_ALREADY_EXISTS){
		return 0;
	}

	ULONG_PTR token;
	GdiplusStartupInput gsi;
	GdiplusStartup(&token,&gsi,NULL);
	int ncount = atoi(lpCmdLine);
	CToolBarWindow *pWnd = new CToolBarWindow();
	if(pWnd)
	{
		pWnd->CreateToolBarWindow();
	}
		MSG msg;
		while(GetMessage(&msg,NULL,NULL,NULL)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		GdiplusShutdown(token);

	return 0;
}