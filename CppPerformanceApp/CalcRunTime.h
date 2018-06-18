#pragma once
#include <string>
using namespace std;

class CCalcRunTime
{
public:
	//构造函数必须显式调用
	explicit CCalcRunTime(const string & name, bool bHigher = false);
	~CCalcRunTime(void);

private:
	//使对象不可复制
	CCalcRunTime(const CCalcRunTime &);
	const CCalcRunTime & operator = (const CCalcRunTime &);

	class Impl;
	Impl * m_pImpl;
};
