#pragma once
#include <string>
using namespace std;

class CCalcRunTime
{
public:
	//���캯��������ʽ����
	explicit CCalcRunTime(const string & name, bool bHigher = false);
	~CCalcRunTime(void);

private:
	//ʹ���󲻿ɸ���
	CCalcRunTime(const CCalcRunTime &);
	const CCalcRunTime & operator = (const CCalcRunTime &);

	class Impl;
	Impl * m_pImpl;
};
