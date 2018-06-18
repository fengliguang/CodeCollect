#include "CalcRunTime.h"
#include <stdio.h>
#include <Windows.h>

inline unsigned long long GetTickMicrosecond()
{
	LARGE_INTEGER lip;
	LARGE_INTEGER lic;
	QueryPerformanceFrequency(&lip);//机器内部计时器的时钟频率
	QueryPerformanceCounter(&lic);
	return (unsigned long long)(lic.QuadPart*1000/(lip.QuadPart/1000));
}

class CCalcRunTime::Impl
{
public:
	double GetElapsed() const
	{
		if (m_bHigher)
		{
			return (GetTickMicrosecond() - m_u8MicroNow) / 1000.0;
		}
		else
		{
			return (GetTickCount() - m_u4StartTime) / 1000.0;
		}
	}
public:
	string				m_name;
	bool				m_bHigher;
	unsigned long		m_u4StartTime;
	unsigned long long  m_u8MicroNow;
};

CCalcRunTime::CCalcRunTime(const string & name, bool bHigher) : m_pImpl(new CCalcRunTime::Impl())
{
	m_pImpl->m_name = name;
	m_pImpl->m_bHigher = bHigher;
	if (m_pImpl->m_bHigher)
	{
		m_pImpl->m_u8MicroNow = GetTickMicrosecond();
	}
	else
	{
		m_pImpl->m_u4StartTime = GetTickCount();
	}
}

CCalcRunTime::~CCalcRunTime(void)
{
	if (m_pImpl->m_bHigher)
	{
		printf("[%s]: %12.3f ms.\n", m_pImpl->m_name.c_str(), m_pImpl->GetElapsed());
	}
	else
	{
		printf("[%s]: %12.3f sec.\n", m_pImpl->m_name.c_str(), m_pImpl->GetElapsed());
	}

	delete m_pImpl;
	m_pImpl = NULL;
}