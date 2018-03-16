#pragma once


#pragma comment(lib, "winmm.lib")


#include <windows.h>
#include <mmsystem.h>


class FpsMonitor
{
public:
	FpsMonitor();
	FpsMonitor(const FpsMonitor&);
	~FpsMonitor();

	void Initialize();
	void Frame();
	int GetFps();

private:
	int m_fps, m_count;
	unsigned long m_startTime;
};