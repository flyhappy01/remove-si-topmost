// remove-si-topmost.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>

bool isWndTopMost(HWND hwnd) {
	return GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_TOPMOST;
}

void showWndTopMost(HWND hwnd){
	RECT rect;
	GetWindowRect(hwnd, &rect);
	SetWindowPos(hwnd, HWND_TOPMOST, rect.left, rect.top, abs(rect.right - rect.left), abs(rect.bottom - rect.top), SWP_SHOWWINDOW);
}
void cancelTopMost(HWND hwnd){
	RECT rect;
	GetWindowRect(hwnd, &rect);
	SetWindowPos(hwnd, HWND_NOTOPMOST, rect.left, rect.top, abs(rect.right - rect.left), abs(rect.bottom - rect.top), SWP_SHOWWINDOW);
}

BOOL CALLBACK EnumWindowsProc(HWND hWnd,LPARAM lParam)
{
	//_tprintf(_T("find one\n"));
	if(GetParent(hWnd)==NULL && IsWindowVisible(hWnd))  //判断是否顶层窗口并且可见
	{
		//TCHAR WindowTitle[100]={0};
		//::GetWindowText(hWnd,WindowTitle,100);
		//_tprintf(WindowTitle);
		if (isWndTopMost(hWnd))
			cancelTopMost(hWnd);
	}
	return true;
}
int _tmain(int argc, _TCHAR* argv[])
{
	EnumWindows(EnumWindowsProc ,NULL );
	return 0;
}

