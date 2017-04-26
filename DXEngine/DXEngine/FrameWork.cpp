#include "FrameWork.h"
#include "SystemDefs.h"

#include <iostream>
using namespace std;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

FrameWork::FrameWork()
{
}


FrameWork::~FrameWork()
{
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	UnregisterClass(m_applicationName, m_hInstance);
	m_hInstance = nullptr;
}


bool FrameWork::Initialize()
{
	if (!CreateDXWindow(L"DxEngineWindow", WINDOWS_POSX, WINDOWS_POSY, SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		return false;
	}

	return true;
}



void FrameWork::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	//UPDATE LOOP
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// update & render functions
		}
	}
}

bool FrameWork::CreateDXWindow(LPCWSTR windowsTitle, int x, int y, int width, int height)
{
	HWND hwnd;
	WNDCLASSEX wcex;

	m_applicationName = windowsTitle;
	m_hInstance = GetModuleHandle(NULL);

	//SETUP THE WINDOWS CLASS WITH DEFAULT SETTINGS.
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wcex.hIconSm = wcex.hIcon;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = m_applicationName;
	wcex.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"RegisterClassEx() Failed", L"Error", MB_OK);
		return false;
	}


	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	if (FULL_SCREEN)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(DEVMODE));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	}
	else
	{
		screenHeight = height;
		screenWidth = width;
	}

	int nStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;


	hwnd = CreateWindowEx(WS_EX_APPWINDOW, windowsTitle, windowsTitle, nStyle, x, y, width, height, NULL, NULL, m_hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, L"CreateWindowEx() Failed", L"Error", MB_OK);
		PostQuitMessage(0);

		return false;
	}

	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	return true;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (msg)
	{
		case WM_PAINT:
		{
			hdc = BeginPaint(hwnd, &ps);
			EndPaint(hwnd, &ps);
		}
		break;

		case WM_CLOSE:
		{
			PostQuitMessage(0);
			DestroyWindow(hwnd);
		}
		break;

		default:
		{
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
	}

	return 0;
}