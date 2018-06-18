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
			//�Ե�����Ϊ������ɾ������������Ԫ�أ���������ɾ�������һ��Ԫ�ط��ظ�������
			//��ʱ����ִ��++it
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
	//�����μӱ���
	mySingCompetition.JoinCompetition();
	//��һ����̭��
	mySingCompetition.FirstKnockout();
	//�ڶ�����̭��
	mySingCompetition.SecondKnockout();
	//����
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

	WORK_LINE& operator=(const WORK_LINE& line)//ע��const
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

	//����IO����������ڽṹ���ڲ���������������ض���Ϊ��Ԫ��������
	friend ostream &operator<<(ostream &out, WORK_LINE line);
};

//�ڽṹ���ⲿ���о��嶨��
ostream& operator<<(ostream &out,WORK_LINE line)
{
	out<<"Token = "<< line.token <<";Miles = "<< line.f8Mile <<endl;
	return out;
}

//���庯��ģ���ʽ���������
template <typename T>
void DisplayValue(T value)
{
	cout<<value;
}

bool SortByToken(const WORK_LINE& line1, const WORK_LINE& line2)
{
	return line1.token < line2.token; //��С��������,���� 
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