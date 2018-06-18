#include "CalcRunTime.h"
#include "Lock.h"

#include <vector>
#include <map>
#include <list>
#include <queue>
using namespace std;

struct LogData
{
	int    i4ID;
	char   strLogBuffer[1024];
	LogData()
	{
		i4ID = 0;
		memset(strLogBuffer, 0, sizeof(strLogBuffer));
	}
};


struct MsgData
{
	int    i4ID;
	char   strName[32];
	void * pLogData;

	MsgData()
	{
		i4ID = 0;
		memset(strName, 0, sizeof(strName));
		pLogData = NULL;
	}
};

void TestFun_Sleep();
void TestFun_MapFind();

int main()
{
	TestFun_Sleep();

	TestFun_MapFind();

	system("pause");
	return 0;
}

void TestFun_MapFind()
{
	map<unsigned long, MsgData *> m_MapMsgData;
	for (unsigned long i = 0; i < 1000; i++)
	{
		MsgData * pMsgData = new MsgData;
		pMsgData->i4ID = i;
		sprintf(pMsgData->strName, "MSG_%04d", i);

		LogData * pLogData = new LogData;
		pLogData->i4ID = i;
		sprintf(pLogData->strLogBuffer, "LogBuffer:%4d", pLogData->i4ID);

		pMsgData->pLogData = pLogData;

		m_MapMsgData.insert(make_pair(i, pMsgData));
	}
	printf("map size: %d\n", m_MapMsgData.size());

	CLock m_Lock;
	printf("map find函数测试延时计算:\n");
	int i4FindCount = 0;
	char strTimeName[32];
	for (unsigned long i = 0; i < 1000; i++)
	{
		sprintf(strTimeName, "map find %4d", i);
		CCalcRunTime runTime(strTimeName, true);

		CAutoLock lock(m_Lock);
		map<unsigned long, MsgData *>::iterator it  = m_MapMsgData.find(i);
		if (it != m_MapMsgData.end())
		{
			i4FindCount++;
		}
	}
	printf("map find num: %d\n", i4FindCount);



	printf("map count函数测试延时计算：\n");
	int i4CountCount = 0;
	for (unsigned long i = 0; i < 1000; i++)
	{
		sprintf(strTimeName, "map count %4d", i);
		CCalcRunTime runTime(strTimeName, true);
		CAutoLock lock(m_Lock);
		int i4Have = m_MapMsgData.count(i);
		if (i4Have == 1)
		{
			i4CountCount++;
		}
	}
	printf("map count num: %d\n", i4CountCount);


	printf("map iterator first函数测试延时计算：\n");
	int i4IteratorCount = 0;
	for (unsigned long i = 0; i < 1000; i++)
	{
		sprintf(strTimeName, "map iterator first %4d", i);
		CCalcRunTime runTime(strTimeName, true);
		CAutoLock lock(m_Lock);
		map<unsigned long, MsgData *>::iterator it;
		for (it = m_MapMsgData.begin(); it != m_MapMsgData.end(); )
		{
			if (i == it->first)
			{
				i4IteratorCount++;
				++it;
			}
			else
			{
				++it;
			}
		}
	}
	printf("map iterator first num: %d\n", i4IteratorCount);



	printf("map iterator second函数测试延时计算：\n");
	int i4IteratorCount2 = 0;
	for (unsigned long i = 0; i < 1000; i++)
	{
		sprintf(strTimeName, "map iterator second %4d", i);
		CCalcRunTime runTime(strTimeName, true);
		CAutoLock lock(m_Lock);
		map<unsigned long, MsgData *>::iterator it;
		for (it = m_MapMsgData.begin(); it != m_MapMsgData.end(); )
		{
			if (i == it->second->i4ID)
			{
				i4IteratorCount2++;
				++it;
			}
			else
			{
				++it;
			}
		}
	}
	printf("map iterator second num: %d\n", i4IteratorCount2);



	printf("map erase函数测试延时计算：\n");
	CCalcRunTime runTime("map erase", true);
	CAutoLock lock(m_Lock);
	map<unsigned long, MsgData *>::iterator it;
	for (it = m_MapMsgData.begin(); it != m_MapMsgData.end(); )
	{
		MsgData * pMsg = it->second;
		if (NULL != pMsg)
		{
			LogData * pLog = (LogData *)pMsg->pLogData;
			if (NULL != pLog)
			{
				delete pLog;
				pLog = NULL;
			}
			delete pMsg;
			pMsg = NULL;
		}
		it = m_MapMsgData.erase(it);
	}

	printf("map size: %d\n", m_MapMsgData.size());
}

void TestFun_Sleep()
{
	printf("Sleep true函数测试延时计算:\n");
	{
		CCalcRunTime runTime("Sleep true", true);
		for (int i = 0; i < 10; i++)
		{
			Sleep(100);
		}
	}

	printf("Sleep false函数测试延时计算:\n");
	{
		CCalcRunTime runTime("Sleep false", false);
		for (int i = 0; i < 10; i++)
		{
			Sleep(100);
		}
	}
}