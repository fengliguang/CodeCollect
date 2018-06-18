#include "Thread.h"

CThread::CThread(void) : m_bStop(false), m_hThread(INVALID_HANDLE_VALUE)
{

}

CThread::~CThread(void)
{
	Stop();
}

void CThread::Start()
{
	if (false == m_bStop)
	{
		m_hThread = ::CreateThread(NULL, 0, ThreadProc, this, 0, NULL);
	}
}

DWORD WINAPI CThread::ThreadProc(LPVOID lpParam)
{
	CThread * pThis = (CThread*)lpParam;
	pThis->Run();
	CloseHandle(pThis->m_hThread);
	pThis->m_hThread = INVALID_HANDLE_VALUE;
	return 0;
}

void CThread::Stop()
{
	m_bStop = true;
	if(m_hThread != INVALID_HANDLE_VALUE)
	{
		if(WaitForSingleObject(m_hThread,INFINITE) != WAIT_ABANDONED)
		{
			CloseHandle(m_hThread);
		}
		m_hThread = INVALID_HANDLE_VALUE;
	}
}


bool CThread::IsStop()
{
	return m_bStop;
}