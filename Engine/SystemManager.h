#pragma once


#define WIN32_LEAN_AND_MEAN


#include <windows.h>
#include "ApplicationManager.h"


class SystemManager
{

public:
	SystemManager(); 
	SystemManager(const SystemManager&); 
	~SystemManager(); 

	bool Initialize();
	void Run();
	void Shutdown();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM); 

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_applicationName; 
	HINSTANCE m_hinstance; 
	HWND m_hwnd;
	ApplicationManager* m_AppManag;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); 
static SystemManager* ApplicationHandle = 0; 
