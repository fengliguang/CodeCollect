#include "StlApplyDemo.h"


void CStlApplyDemo::DeleteTheRepeatElevment(bool bRun)
{
	if (!bRun) return;

	vector<double> vecTemp;
	vecTemp.push_back(10.1234);
	vecTemp.push_back(12.2345);
	vecTemp.push_back(14.3456);
	vecTemp.push_back(11.4567);
	vecTemp.push_back(12.2345);
	vecTemp.push_back(10.1234);
	vecTemp.push_back(16.5678);

	for (unsigned int i = 0; i < vecTemp.size(); i++)
	{
		printf("%02d:%7.4f\n", i, vecTemp[i]);
	}

	printf("sort.\n");

	sort(vecTemp.begin(), vecTemp.end());

	int n = 0;
	for (vector<double>::iterator it = vecTemp.begin(); it != vecTemp.end(); it++ )
	{
		printf("%02d:%7.4f\n", n++, *it);
	}

	printf("delete the repeat one.\n");

	double f8CurTemp = 0.0;
	double f8LastTemp = -9999;
	for (vector<double>::iterator it = vecTemp.begin(); it != vecTemp.end();)
	{
		f8CurTemp = *it;
		if (fabs(f8CurTemp - f8LastTemp) < 0.000001 )
		{
			//以迭代器为参数，删除满足条件的元素，并把数据删除后的下一个元素返回给迭代器
			//此时不可执行++it
			printf("Find and erase:%7.4f\n", *it);
			it = vecTemp.erase(it);
		}
		else
		{
			++it;
		}
		f8LastTemp = *it;
	}

	for (unsigned int i = 0; i < vecTemp.size(); i++)
	{
		printf("%02d:%7.4f\n\n", i, vecTemp[i]);
	}
}

void CStlApplyDemo::SingleSimDemo(bool bRun)
{
	if (!bRun) return;

	CSingingCompetition mySingCompetition;
	//报名参加比赛
	mySingCompetition.JoinCompetition();
	//第一轮淘汰赛
	mySingCompetition.FirstKnockout();
	//第二轮淘汰赛
	mySingCompetition.SecondKnockout();
	//决赛
	mySingCompetition.Finals();
}


struct WORK_LINE 
{  
	int	   token;
	double f8Mile;

	WORK_LINE()
	{
		token = 0;
		f8Mile = 0.0;
	}

	WORK_LINE& operator=(const WORK_LINE& line)//注意const
	{
		token = line.token;
		f8Mile = line.f8Mile;
		return *this;
	}

	WORK_LINE& operator+(const WORK_LINE& line)
	{
		token += line.token;
		f8Mile += line.f8Mile;
		return *this;
	}

	WORK_LINE& operator-(const WORK_LINE& line)
	{
		token -= line.token;
		f8Mile -= line.f8Mile;
		return *this;
	}

	bool operator==(const WORK_LINE line)
	{
		return ( line.token == token && (fabs(line.f8Mile-f8Mile) < 0.0001) );
	}

	//重载IO输出操作，在结构体内部将输入操作的重载定义为友元函数重载
	friend ostream &operator<<(ostream &out, WORK_LINE line);
};

//在结构体外部进行具体定义
ostream& operator<<(ostream &out,WORK_LINE line)
{
	out<<"Token = "<< line.token <<";Miles = "<< line.f8Mile <<endl;
	return out;
}

//定义函数模板格式的输出函数
template <typename T>
void DisplayValue(T value)
{
	cout<<value;
}

bool SortByToken(const WORK_LINE& line1, const WORK_LINE& line2)
{
	return line1.token < line2.token; //从小到大排列,升序 
}


void CStlApplyDemo::VectorStructDataDemo(bool bRun)
{
	if (!bRun) return;

	{
		vector<WORK_LINE> vecLine;
		WORK_LINE* pLine= new WORK_LINE;
		vecLine.push_back(*pLine);
		for (vector<WORK_LINE>::iterator it = vecLine.begin(); it != vecLine.end(); ++it)
		{
			DisplayValue(*it);
		}
		pLine->token = 1;
		pLine->f8Mile = 10.00;
		cout << endl;
		for (vector<WORK_LINE>::iterator it = vecLine.begin(); it != vecLine.end(); ++it)
		{
			DisplayValue(*it);
		}
		vecLine.at(0).token = 1;
		vecLine.at(0).f8Mile = 10.00;
		cout << endl;
		for (vector<WORK_LINE>::iterator it = vecLine.begin(); it != vecLine.end(); ++it)
		{
			DisplayValue(*it);
		}
		delete pLine;
	}

	{
		vector<WORK_LINE*> vecLine;

		WORK_LINE* pLine1= new WORK_LINE;
		pLine1->token = 1;
		vecLine.push_back(pLine1);

		WORK_LINE* pLine2= new WORK_LINE;
		pLine2->token = 2;
		vecLine.push_back(pLine2);

		WORK_LINE* pLine3= new WORK_LINE;
		pLine3->token = 3;
		vecLine.push_back(pLine3);

		pLine1->f8Mile = 1.0;
		pLine2->f8Mile = 2.0;
		pLine3->f8Mile = 3.0;

		for(int i = 0; i< (int)vecLine.size(); i++)
		{
			WORK_LINE* pLine = vecLine.at(i);
			if (NULL != pLine)
			{
				cout << pLine->token << '\t'  << pLine->f8Mile << endl;
			}
		}


		for (vector<WORK_LINE*>::iterator it = vecLine.begin(); it != vecLine.end(); it++)
		{
			if (NULL != *it) 
			{
				delete *it; 
				*it = NULL;
			}
		}
		vecLine.clear();
	}
}