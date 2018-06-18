#include "Timer.h"

CTimer::CTimer(void) : m_TimerHandler(0), m_u4Interval(-1)
{
}

CTimer::~CTimer(void)
{
	Cancel();
}

void CTimer::RegisterHandler(TimerHandler handler, void* p)
{
	m_TimerHandler = handler;
	m_Param = p;
}

void CTimer::SetTimerInterval(int i4MillSecond)
{
	m_u4Interval = i4MillSecond;
}

void CTimer::Run()
{
	unsigned long tickNow = ::GetTickCount();
	unsigned long tickLastTime = tickNow;

	while(!IsStop())
	{
		tickNow = ::GetTickCount();
		if(tickNow - tickLastTime > m_u4Interval)
		{
			if(m_TimerHandler)
			{
				(*m_TimerHandler)(m_Param);
			}
			tickLastTime = ::GetTickCount();
		}
		::Sleep(1);
	}
}

void CTimer::Cancel()
{
	Stop();
}
