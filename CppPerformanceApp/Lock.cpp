#include "Lock.h"

CLock::CLock(void)
{
	::InitializeCriticalSection(&m_crit);
}

CLock::~CLock(void)
{
	::DeleteCriticalSection(&m_crit);
}


void CLock::Lock()
{
	::EnterCriticalSection(&m_crit);
}

void CLock::UnLock()
{
	::LeaveCriticalSection(&m_crit);
}