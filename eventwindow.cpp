//FILE: ewentwindow.cpp
//handling events that modules send.

#include "eventwindow.h"
#include <Windows.h>
#include <WinUser.h>

//Construction
CEventWindow::CEventWindow()
{
}

CEventWindow::~CEventWindow()
{
	
}

CEventWindow::CEventWindow(const CEventWindow&)
{
}
//////////////////////////////////////////////////////////////////////////
//eventhandle

void CEventWindow::EventHandle()
{
	printf("Entered to EventHandle");

	const wchar_t CLASS_NAME[] = L"CEventWindow";
	//const wchar_t CLASS_NAME = className;

	WNDCLASSEX wcex;

	wcex.lpfnWndProc = &CEventWindow::WindowProc;
	wcex.hInstance = hInstance;
	wcex.lpszClassName = CLASS_NAME;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	//wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	//wc.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	//wc.lpszClassName = strWndName.c_str();
	wcex.hIconSm = NULL;


	if (!RegisterClassExW(&wcex))
		printf("RegisterClassEx err: ", GetLastError());

	// Create the window.
	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		NULL,			                // Window text 
		NULL,                           // Window style
		NULL, NULL, NULL, NULL,         // Size and position
		HWND_MESSAGE,                   // Parent window    
		NULL,                           // Menu
		NULL,                           // Instance handle
		NULL                            // Additional application data
	);
	printf("EventWindow hwnd: ", hwnd);
	if (!hwnd)
	{
		printf("CreateWindow last error: ", GetLastError());
		printf("CreateWindow ExW created and hwnd is: ", hwnd);
	}
	else {
		ShowWindow(hwnd, SW_HIDE);
	}

	MSG msg;
	bool bRet;

	while ((bRet = GetMessage(&msg, hwnd, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			// handle the error and possibly exit
			printf("GetMessage faild");
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg); //<< This line send msg to WindowProc()
		}
	}
	printf("GetMessage loop finished");

}

LRESULT CALLBACK CEventWindow::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WFS_EXECUTE_EVENT:
		ExecuteEventHandle(lParam);
		break;
	case WFS_SERVICE_EVENT:
		ServiceEventHandle(lParam);
		break;
	case WFS_USER_EVENT:
		UserEventHandle(lParam);
		break;
	case WFS_SYSTEM_EVENT:
		SystemEventHandle(lParam);
		break;
	default:
		printf("WndProc msg: ", msg);
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void CEventWindow::SetHwnd(HWND hwnd1)
{
	m_hwnd = hwnd1;
}

HWND CEventWindow::GetHwnd()
{
	return m_hwnd;
}

int CEventWindow::StartThread()
{
	printf("start of thread");
	const wchar_t* className = L"CEventWindow";

	/*thread EventWindowThread(&CEventWindow::EventHandle, CEventWindow());
	EventWindowThread.detach();*/
	return 0;
}


void CEventWindow::ExecuteEventHandle(LPARAM lParam)
{
	printf("WFS_EXECUTE_EVENT");
	ModuleSpecifier(lParam);
}

void CEventWindow::ServiceEventHandle(LPARAM lParam)
{
	printf("WFS_EXECUTE_EVENT");
	ModuleSpecifier(lParam);
}

void CEventWindow::UserEventHandle(LPARAM lParam)
{
	printf("WFS_USER_EVENT");
	ModuleSpecifier(lParam);

}


void CEventWindow::SystemEventHandle(LPARAM lParam)
{
	printf("WFS_SYSTEM_EVENT");
	ModuleSpecifier(lParam);
	LPWFSRESULT lpWFSResult = (LPWFSRESULT)lParam;

	switch (lpWFSResult->u.dwEventID)
	{
	case(WFS_SYSE_UNDELIVERABLE_MSG):
		printf("	WFS_SYSE_UNDELIVERABLE_MSG");
		break;
	case(WFS_SYSE_HARDWARE_ERROR):
		printf("	WFS_SYSE_HARDWARE_ERROR");
		break;
	case(WFS_SYSE_VERSION_ERROR):
		printf("	WFS_SYSE_VERSION_ERROR");
		break;
	case(WFS_SYSE_DEVICE_STATUS):
		ShowDevStatus(lpWFSResult);
		break;
	case(WFS_SYSE_APP_DISCONNECT):
		printf("	WFS_SYSE_APP_DISCONNECT");
		break;
	case(WFS_SYSE_SOFTWARE_ERROR):
		printf("	WFS_SYSE_SOFTWARE_ERROR");
		break;
	case(WFS_SYSE_USER_ERROR):
		printf("	WFS_SYSE_USER_ERROR");
		break;
	case(WFS_SYSE_LOCK_REQUESTED):
		printf("	WFS_SYSE_LOCK_REQUESTED");
		break;
	case(WFS_SYSE_FRAUD_ATTEMPT):
		printf("	WFS_SYSE_FRAUD_ATTEMPT");
		break;
	}
}

void CEventWindow::ShowDevStatus(LPWFSRESULT lpWFSResult)
{
	LPWFSDEVSTATUS lpWFSDEVStatus = (LPWFSDEVSTATUS)(lpWFSResult->lpBuffer);
	printf("lpszPhysicalName", lpWFSDEVStatus->lpszPhysicalName);

	switch (lpWFSDEVStatus->dwState)
	{
	case(WFS_STAT_DEVONLINE):
		printf("	WFS_STAT_DEVONLINE");
		break;
	case(WFS_STAT_DEVOFFLINE):
		printf("	WFS_STAT_DEVOFFLINE");
		break;
	case(WFS_STAT_DEVPOWEROFF):
		printf("	WFS_STAT_DEVPOWEROFF");
		break;
	case(WFS_STAT_DEVNODEVICE):
		printf("	WFS_STAT_DEVNODEVICE");
		break;
	case(WFS_STAT_DEVHWERROR):
		printf("	WFS_STAT_DEVHWERROR");
		break;
	case(WFS_STAT_DEVUSERERROR):
		printf("	WFS_STAT_DEVUSERERROR");
		break;
	case(WFS_STAT_DEVBUSY):
		printf("	WFS_STAT_DEVBUSY");
		break;
	case(WFS_STAT_DEVFRAUDATTEMPT):
		printf("	WFS_STAT_DEVFRAUDATTEMPT");
		break;
	}
}