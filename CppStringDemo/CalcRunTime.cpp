#include "CalcRunTime.h"
#include <time.h>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
#include <windows.h>


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
	//获取微妙精度
	double GetElapsed() const
	{
		return (GetTickMicrosecond() - m_u8StartTime) / 1e3;
	}
public:
	string			   m_name;
	unsigned long long m_u8StartTime;
};

CCalcRunTime::CCalcRunTime(const string & name) : m_pImpl(new CCalcRunTime::Impl())
{
	m_pImpl->m_name = name;
	m_pImpl->m_u8StartTime = GetTickMicrosecond();
}

CCalcRunTime::~CCalcRunTime(void)
{
	cout.setf(ios::fixed);
	cout << m_pImpl->m_name << ": took " << setprecision(4) << m_pImpl->GetElapsed() << " ms." << endl;
	cout.unsetf(ios::fixed);
	delete m_pImpl;
	m_pImpl = NULL;
}