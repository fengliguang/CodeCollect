#pragma once

#include <Windows.h>

class CLock
{
public:
	CLock(void);
	virtual ~CLock(void);
public:
	void Lock();
	void UnLock();
private:
	CRITICAL_SECTION m_crit;
};

class CGuardLock
{
public:
	CGuardLock(CLock * pLock)  : m_pLock(pLock)
	{
		m_pLock->Lock();
	}

	~CGuardLock(void)
	{
		m_pLock->UnLock();
	}
private:
	CLock * m_pLock;
};

//�����߳���
class CAutoLock
{
public:
	explicit CAutoLock(CLock & lk) : m_Lock(lk)
	{
		m_Lock.Lock();
	}
	~CAutoLock()
	{
		m_Lock.UnLock();
	}
private:
	CLock & m_Lock; //���ñ���
};