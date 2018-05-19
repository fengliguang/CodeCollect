#ifndef _TIMEUTIL_H_
#define _TIMEUTIL_H_

#include <time.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
using namespace std;

class CCalcRunTime
{
public:
	//���캯��������ʽ����
	explicit CCalcRunTime(const string & name);
	~CCalcRunTime(void);

private:
	//ʹ���󲻿ɸ���
	CCalcRunTime(const CCalcRunTime &);
	const CCalcRunTime & operator = (const CCalcRunTime &);

	class Impl;
	Impl * m_pImpl;
};

#endif
