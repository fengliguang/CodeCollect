#pragma once
#include <iostream>
using namespace std;
#include <time.h>
#include <windows.h>


class CCreateRandom
{
public:
	CCreateRandom(char * strName);
	~CCreateRandom(void);
public:
	void StartThread(int i4Seed);

	inline double GetRandomValue(double start, double end)
	{	
		return start + ( end - start) * rand()/(RAND_MAX + 1.0);
	}

private:
	static DWORD WINAPI OnCreateRandomThread(LPVOID lpParam);
private:
	bool   m_bCreate;
	HANDLE m_hThread;
	HANDLE m_hEvent;

    int    m_i4RandomSeed;
	double m_f8BaseValue;
	char   m_strName[32];
};
