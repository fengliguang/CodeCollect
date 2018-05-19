#pragma once
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

#ifdef WIN32
#pragma warning(disable:4996)
#endif

class CBasicStringFun
{
public:
	//获取字符串长度
	static int GetStringLen(const char *pDest);
	static int GetStringLenEx1(const char *pDest);
	static int GetStringLenEx2(const char *pDest);
	static int GetStringLenEx3(const char *pDest);

	//查找字符串
	static char* FindStrInStr(char *strSrc, char strFind[]);
	static char* StrStr(const char * str1, const char * str2);
	static char* SubStr(char *str1, char *str2);

	static void SplitA(const char * pSource, int i4SourceLen, const char * pDelimStr, vector<string> & vecOut);
};



void CBasicStringFun_Test(bool bRun);