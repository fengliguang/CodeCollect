#include "CreateRandom.h"

CCreateRandom::CCreateRandom(char * strName)
{
	m_bCreate = false;
	m_f8BaseValue = 30.000000000;
	m_hEvent = NULL;
	m_hThread = NULL;

	memset(m_strName, 0, sizeof(m_strName));
	if (NULL != strName)
	{
		
		strcpy(m_strName, strName);
	}
}

CCreateRandom::~CCreateRandom(void)
{
	if (m_bCreate)
	{
		::SetEvent(m_hEvent);
		if (::WaitForSingleObject(m_hThread, 1000) == WAIT_TIMEOUT)
		{
			::TerminateThread(m_hThread, 0);
		}
		CloseHandle(m_hThread);
		CloseHandle(m_hEvent);
		m_hThread = NULL;
		m_hEvent = NULL;
	}

	printf("[%s] : ~CCreateRandom\n", m_strName);
}

void CCreateRandom::StartThread(int i4Seed)
{
	if (false == m_bCreate)
	{
		m_i4RandomSeed = i4Seed;
		m_hEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
		m_hThread = ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OnCreateRandomThread, this, 0, NULL);
		m_bCreate = true;
	}
}

DWORD WINAPI CCreateRandom::OnCreateRandomThread(LPVOID lpParam)
{
	CCreateRandom *pThis = (CCreateRandom*)lpParam;
	srand(pThis->m_i4RandomSeed);//多线程的随机数生成
	while (1)
	{
		if (WAIT_OBJECT_0 == ::WaitForSingleObject(pThis->m_hEvent, 3000))
		{
			break;
		}
		double f8Temp = pThis->m_f8BaseValue + pThis->GetRandomValue(0.000, 0.009);
		printf("[%s] : %13.9f\n", pThis->m_strName, f8Temp);
	}

	printf("[%s] : Exit\n", pThis->m_strName);
	return 0;
}
