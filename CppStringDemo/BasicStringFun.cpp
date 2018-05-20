#include "BasicStringFun.h"
#include "StringSpliter.h"
#include "CalcRunTime.h"

int CBasicStringFun::GetStringLen(const char *pDest)
{
	assert(pDest);
	int i = 0;
	while( '\0' != (*pDest++) )
	{
		i++;
	}
	return i;
}

//计数器方式
int CBasicStringFun::GetStringLenEx1(const char *pDest)
{
	assert(pDest != NULL); 
	int i = 0;
	while( *pDest != '\0' )
	{
		pDest++;
		i++;
	}
	return i;
}

//指针减指针的方法
int CBasicStringFun::GetStringLenEx2(const char *pDest)
{
	assert(pDest != NULL);
	const char *p = pDest;  
	while(*p != '\0')  
	{  
		p++;
	}  
	return p - pDest;  
}

//函数递归的方法
int CBasicStringFun::GetStringLenEx3(const char *pDest)
{
	assert(pDest != NULL);
	if(*pDest == '\0') 
	{
		return 0;
	}
	else
	{
		return 1 + GetStringLenEx3(pDest + 1);
	}
}

char* CBasicStringFun::FindStrInStr(char *strSrc, char strFind[])
{
	assert(strSrc && strFind);
	char *pLast = NULL;
	char *pStart = strSrc;
	int j = 0;

	while (*strFind == 0)
	{
		return NULL;
	}

	while (*strSrc && *strFind)
	{
		pStart = strSrc;
		while (*strSrc && strFind[j] && *strSrc == strFind[j])
		{
			strSrc++;
			j++;
		}
		if (strFind[j]== '\0')
		{
			pLast = pStart;
		}
		strSrc = pStart + 1; 
		j = 0;
	}

	if (*strSrc == '\0')
	{
		return pLast;
	}
	else
	{
		return NULL;
	}
}

char* CBasicStringFun::StrStr(const char * str1, const char * str2)
{
	assert(str1 && str2);
	char *cp = (char *) str1;
	char *s1, *s2;
	if (!*str2)
	{
		return((char *)str1);
	}
	while (*cp)
	{
		s1 = cp;
		s2 = (char *) str2;
		while ( *s1 && *s2 && !(*s1-*s2) )
			s1++, s2++;
		if (!*s2)
			return(cp);
		cp++;
	}
	return(NULL);
}

char* CBasicStringFun::SubStr(char *str1, char *str2)
{
	assert(str1 && str2);
	char * p = str1;
	while(*p)
	{
		if(memcmp(p, str2, strlen(str2)) == 0)
			return p;
		p++;
	}
	return NULL;
}

void CBasicStringFun::SplitA(const char * pSource, int i4SourceLen, const char * pDelimStr, vector<string> & vecOut)
{
	assert(pSource && pDelimStr);
	char* copyStr = (char*)malloc((i4SourceLen + 1) * sizeof(char));
	memcpy(copyStr, pSource, i4SourceLen);
	copyStr[i4SourceLen] = '\0';

	//strtok连续的分隔符被当做一个处理
	char * tmp = strtok(copyStr, pDelimStr);
	while (tmp != NULL)
	{
		vecOut.push_back(tmp);
		tmp = strtok(NULL, pDelimStr);
	}

	free(copyStr);
	copyStr = NULL;
}

void CBasicStringFun_Test(bool bRun)
{
	if (!bRun) return;

	char strBufferTemp[32] = {'\0'};
	char *pBufferTemp = "Hello World!";

	int i4BufferLen1 = CBasicStringFun::GetStringLen(pBufferTemp);
	int i4BufferLen2 = CBasicStringFun::GetStringLenEx1(pBufferTemp);
	int i4BufferLen3 = CBasicStringFun::GetStringLenEx2(pBufferTemp);
	int i4BufferLen4 = CBasicStringFun::GetStringLenEx3(pBufferTemp);

	int i4BufferLen5 = CBasicStringFun::GetStringLen(strBufferTemp);
	
	printf("%s=%d,%d,%d,%d\n", pBufferTemp, i4BufferLen1,i4BufferLen2,i4BufferLen3,i4BufferLen4);
	printf("%s=%d\n", strBufferTemp, i4BufferLen5);


	char strBufferLong[] = "Hello China!;How are you;My name is feng,";
	char strFind[] = ";";
	printf("FindStrInStr:%s\n", CBasicStringFun::FindStrInStr(strBufferLong, strFind));
	printf("StrStr:%s\n", CBasicStringFun::StrStr(strBufferLong, strFind));
	char * pTemp1 = CBasicStringFun::SubStr(strBufferLong, strFind);
	printf("SubStr:%s\n", pTemp1);
	//char *strpbrk(const char *s, const char *accept);
	//strpbrk()用来找出参数s 字符串中最先出现存在参数accept 字符串中的任意字符.
	char * pTemp2 = strpbrk(strBufferLong, strFind);
	printf("strpbrk:%s\n", pTemp2);

	{
		CCalcRunTime time("Sleep");
		Sleep(100);
	}

	printf("\n");
	{
		CCalcRunTime time("SplitA");
		char *str = "$CMD12,1.12232323,1,28,200,0000,21.821,0,,1,CMD12,1.12232323,1,28,200,0000,21.821,0,,1CMD12,1.12232323,1,28,200,0000,21.821,0,,1CMD12,1.12232323,1,28,200,0000,21.821,0,,1,*6B";
		vector<string> vecTemp;
		CBasicStringFun::SplitA(str, strlen(str), ",", vecTemp);
		for (int i = 0; i < int(vecTemp.size()); i++)
		{
			//printf("%d:%s\n", i, vecTemp.at(i).c_str());
		}
		printf("%d\n", vecTemp.size());
	}

	printf("\n");
	{
		CCalcRunTime time("StringSpliter");
		char *str = "$CMD12,1.12232323,1,28,200,0000,21.821,0,,1,CMD12,1.12232323,1,28,200,0000,21.821,0,,1CMD12,1.12232323,1,28,200,0000,21.821,0,,1CMD12,1.12232323,1,28,200,0000,21.821,0,,1,*6B";
		StringSpliter string_spliter(str, ",");
		int n;
		const char *sec;
		for (n=0, sec = string_spliter.Next(); sec; sec=string_spliter.Next(), n++) 
		{
			//printf("%d:%s\n", n, sec);
		}
		printf("%d\n", n);
	}

	printf("\n");
	{
		CCalcRunTime time("StringSpliterRaw");
		char *str = "$CMD12,1.12232323,1,28,200,0000,21.821,0,,1,CMD12,1.12232323,1,28,200,0000,21.821,0,,1CMD12,1.12232323,1,28,200,0000,21.821,0,,1CMD12,1.12232323,1,28,200,0000,21.821,0,,1,*6B";
		char	strTemp[50] = {'\0'};	
		int		BlockNum = 0;
		int		BackComma = 0;
		void*	pEnd = memchr(str, '*', strlen(str));
		int		nEndPosition = (unsigned char*)pEnd - (unsigned char*)str +1;

		for(int i = 0; i < nEndPosition; i++)
		{
			if ( *(str + i )==',' || *( str + i) =='*' )
			{
				memset(strTemp, '\0', sizeof(strTemp));
				memcpy(strTemp, str + BackComma + 1, i- BackComma);

				//printf("%d:%s\n", BlockNum, strTemp);

				BackComma = i;
				BlockNum++;
			}
		}

		printf("%d\n", BlockNum);
	}
}