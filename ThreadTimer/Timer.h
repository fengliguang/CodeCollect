#pragma once
#include "Thread.h"
#include <iostream>
using namespace std;

typedef void(CALLBACK *Timerfunc)(void * p);
typedef Timerfunc TimerHandler;

class CTimer : public CThread
{
public:
	 CTimer(void);
	~CTimer(void);

public:
	void RegisterHandler(TimerHandler handler, void * p);
	void SetTimerInterval(int i4MillSecond);
	void Run();
	void Cancel();

private:
	TimerHandler  m_TimerHandler;
	unsigned long m_u4Interval;
	void*         m_Param;
};
