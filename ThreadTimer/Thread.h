#ifndef _THREAD_H_
#define _THREAD_H_

#include <Windows.h>

class CThread
{
public:
	CThread(void);
	virtual ~CThread(void);
public:
	virtual void    Run() = 0;
	void            Start();
	void            Stop();
	bool            IsStop();
protected:
	static DWORD WINAPI ThreadProc(LPVOID lpParam);
private:
	bool			m_bStop;
	HANDLE			m_hThread;
};

#endif