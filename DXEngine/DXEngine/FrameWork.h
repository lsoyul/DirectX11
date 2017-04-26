#ifndef _FRAME_WORK_H
#define _FRAME_WORK_H

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

class FrameWork
{
public:
	FrameWork();
	~FrameWork();

	bool Initialize();
	void Run();

private:
	bool CreateDXWindow(LPCWSTR windowsTitle, int x, int y, int width, int height);

	LPCWSTR m_applicationName;
	HINSTANCE m_hInstance;
	

};


#endif