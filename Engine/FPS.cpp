#include "FPS.h"


FpsMonitor::FpsMonitor()
{
}


FpsMonitor::FpsMonitor(const FpsMonitor& other)
{
}


FpsMonitor::~FpsMonitor()
{
}


void FpsMonitor::Initialize()
{
	m_fps = 0;
	m_count = 0;
	m_startTime = timeGetTime();
	return;
}


void FpsMonitor::Frame()
{
	m_count++;

	if(timeGetTime() >= (m_startTime + 1000))
	{
		m_fps = m_count;
		m_count = 0;
		
		m_startTime = timeGetTime();
	}
}


int FpsMonitor::GetFps()
{
	return m_fps;
}