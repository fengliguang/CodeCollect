#ifndef _SINGINGCOMPETITION_H_
#define _SINGINGCOMPETITION_H_

#include <vector>
#include <map>
#include <list>
#include <deque>
#include <set>
#include <algorithm>
#include <numeric>

#include <time.h>
#include <iostream>
using namespace std;

struct Singer
{
	string strName;		//����
	int    iLatestScore;	//���µ÷�
};

#define TRACE printf

class CSingingCompetition
{
public:
	CSingingCompetition(void);
	virtual ~CSingingCompetition(void);

	//���⿪�ŵĳ�Ա����
public:
	//�����μӱ���
	void JoinCompetition();

	//��һ����̭��
	void FirstKnockout();

	//�ڶ�����̭��
	void SecondKnockout();

	//����
	void Finals();

	//�����⿪�ŵ�˽�г�Ա����
private:
	//���ɸ��ֵķ���
	void MakeScore(Singer &singer);

	//��ӡ��ǰС��ķ���
	void PrintGroupScore();

	//�ڵ�ǰС������̭����
	void EraseInCurGroup();

	//��ʣ�������ɾ������
	void EraseInRemainingID(list<int>::iterator it);

	//��̭��
	void Knockout();

	//˽�г�Ա����
private:
	map<int, Singer> m_mapSinger;		//���еĲ���ID����ֵ�ӳ�伯�ϡ�int:����ID��Singer:�μӱ����ĸ��֡�
	list<int> m_lstRemainingID;			//ʣ�����(û����̭�ĸ���)�Ĳ���ID��int:ʣ����ֵĲ���ID��
	multimap<int, int, greater<int> > m_mltmapCurGroup;		//��ǰ�ݳ�С��ĸ��ַ�������ֲ���ID��ӳ�伯�ϡ���һ��int: ���ַ������ڶ���int: ���ֲ���ID��greater<int>: �����������ڸ��ַ����Ľ������С�
	vector<int> m_vecIDBeEliminatedInFirstRound;			//��һ����̭���б���̭�ĸ��ֲ����ļ��ϡ�int: ���ֵĲ����š�
	multiset<int> m_mltsetScoreBeEliminatedInSecondRound;	//�ڶ�����̭���б���̭�ĸ��ַ����ļ��ϡ�int: ���ֵķ�����

	int m_iRound;		//�ڼ��ֱ�����ֵΪ1����һ�֣�ֵΪ2���ڶ��֣�ֵΪ3�������֡�
};

#endif