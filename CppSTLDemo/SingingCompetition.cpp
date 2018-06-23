#include "SingingCompetition.h"

CSingingCompetition::CSingingCompetition(void)
{
	//��û��ʼ������������������Ϊ0
	m_iRound = 0;

	//�����������
	srand ( (unsigned)time ( 0 ) );
}

CSingingCompetition::~CSingingCompetition(void)
{
}

//�����μӱ���
void CSingingCompetition::JoinCompetition()
{
	if (m_iRound == 0)
	{
		string strNameBaseSource("ABCDEFGHIJKLMNOPQRSTUVWXYZ");  //�������Ԫ�ص���Դ

		//��������������Ԫ�ص���Դ
		random_shuffle(strNameBaseSource.begin(), strNameBaseSource.end());

		for (int i=0; i<24; ++i)
		{
			//��ȡ�μӱ����ĸ�������
			string strExt(1,strNameBaseSource[i]);

			//������ֶ���
			Singer singer;
			singer.iLatestScore = 0;
			singer.strName = "ѡ��";
			singer.strName += strExt;

			//¼��μӱ����ĸ���
			m_mapSinger.insert(pair<int, Singer>(i+100, singer));
			m_lstRemainingID.push_back(i+100);
		}

		//��ӡ�μӱ����ĸ��������������
		TRACE("*******************************************************\n");
		TRACE("�μӱ����ĸ�������������ţ�\n");
		for (map<int,Singer>::iterator it=m_mapSinger.begin(); it!=m_mapSinger.end(); ++it)
		{
			TRACE("%s�������ţ�%d\n", it->second.strName.c_str(), it->first);
		}
		TRACE("\n");
	}
}

//��һ����̭��
void CSingingCompetition::FirstKnockout()
{
	if (m_iRound == 0)
	{
		m_iRound = 1;

		//������̭��
		Knockout();

		TRACE("��%d����̭���б���̭�ĸ��ֵ����֣�\n", m_iRound);
		for (vector<int>::iterator it=m_vecIDBeEliminatedInFirstRound.begin(); it!=m_vecIDBeEliminatedInFirstRound.end(); ++it)
		{
			TRACE("%s ", m_mapSinger[*it].strName.c_str());
		}
		TRACE("\n");
		TRACE("\n");
	}
}

//�ڶ�����̭��
void CSingingCompetition::SecondKnockout()
{
	if (m_iRound == 1)
	{
		m_iRound = 2;

		//������̭��
		Knockout();

		TRACE("��%d����̭���б���̭�ĸ��ֵķ�����\n", m_iRound);
		for (multiset<int>::iterator it=m_mltsetScoreBeEliminatedInSecondRound.begin(); it!=m_mltsetScoreBeEliminatedInSecondRound.end(); ++it)
		{
			TRACE("%d ", *it);
		}
		TRACE("\n");
		TRACE("\n");
	}
}

//����
void CSingingCompetition::Finals()
{
	if (m_iRound == 2)
	{
		m_iRound = 3;

		//�����־���
		for (list<int>::iterator it=m_lstRemainingID.begin(); it!=m_lstRemainingID.end(); ++it)
		{
			//���ɸ��ֵķ���
			MakeScore(m_mapSinger[*it]);

			//��¼��ǰС����ֵĵ÷��������������������
			m_mltmapCurGroup.insert(pair<int,int>(m_mapSinger[*it].iLatestScore, *it));
		}

		//��ӡС��������
		TRACE("*************С����������*************\n");
		for (multimap<int,int, greater<int> >::iterator it=m_mltmapCurGroup.begin(); it!=m_mltmapCurGroup.end(); ++it)
		{
			TRACE("%s�ĵ÷֣�%d\n", m_mapSinger[it->second].strName.c_str() ,it->first);
		}
		TRACE("\n");

		//������е�����
		m_mapSinger.clear();
		m_lstRemainingID.clear();
		m_vecIDBeEliminatedInFirstRound.clear();
		m_mltsetScoreBeEliminatedInSecondRound.clear();
		m_mltmapCurGroup.clear();
		m_iRound = 0;
	}
}

//���ɸ��ֵķ���
void CSingingCompetition::MakeScore(Singer &singer)
{
	deque<int> deqScore;

	//ʮ����ί�ֱ�Ը��ִ��
	for (int i=0; i<10; ++i)
	{
		int iScore = 60 + rand()%40;
		deqScore.push_back(iScore);
	}

	//Ϊʮ����ί�Ĵ������
	sort(deqScore.begin(), deqScore.end());

	//ȥ��һ����߷֣�ȥ��һ����ͷ�
	deqScore.pop_front();
	deqScore.pop_back();

	//��˸���ί��ֵ��ܺ�
	int iScoreSum = accumulate(deqScore.begin(), deqScore.end(), 0);

	//��˸���ί��ֵ�ƽ����
	int iScoreAverage = (int)(iScoreSum/deqScore.size());

	//���������õ÷�
	singer.iLatestScore = iScoreAverage;
}

//��ӡ��ǰС��ķ���
void CSingingCompetition::PrintGroupScore()
{
	TRACE("С��÷������\n");
	for (multimap<int,int, greater<int> >::iterator it=m_mltmapCurGroup.begin(); it!=m_mltmapCurGroup.end(); ++it)
	{
		TRACE("%s�ĵ÷֣�%d\n", m_mapSinger[it->second].strName.c_str() ,it->first);
	}
	TRACE("\n");
}

//�ڵ�ǰС������̭����
void CSingingCompetition::EraseInCurGroup()
{
	int iSingerLastIndexInGroup = 0;		//���ڸ��ֵĵ�������
	while(iSingerLastIndexInGroup<3)
	{
		//��ȡ��ǰ�ݳ�С������һ��Ԫ�صĵ�����
		multimap<int,int,greater<int> >::iterator it=m_mltmapCurGroup.end();
		--it;

		++iSingerLastIndexInGroup;

		if (m_iRound == 1)
		{
			//��¼��һ����̭���б���̭�ĸ��ֵĲ�����
			m_vecIDBeEliminatedInFirstRound.push_back(it->second);
		}
		else if (m_iRound == 2)
		{
			//��¼�ڶ�����̭���б���̭�ĸ��ֵķ���
			m_mltsetScoreBeEliminatedInSecondRound.insert(m_mapSinger[it->second].iLatestScore);
		}

		//�ӵ�ǰ�ݳ�С��ļ���������ɾ�����һ��Ԫ��
		m_mltmapCurGroup.erase(it);
	}
}

//��ʣ�������ɾ������
void CSingingCompetition::EraseInRemainingID(list<int>::iterator it)
{
	int iSingerReverseIndexInGroup = 0;		//�������������
	while(iSingerReverseIndexInGroup<6)
	{
		//�������������������ָ�Ĳ���ID����Ӧ���ֵ�{����������ID}�Ƿ��ڵ�ǰ�ݳ�С����
		multimap<int,int,greater<int> >::iterator itMltmapScoreToID = 
			find(m_mltmapCurGroup.begin(),m_mltmapCurGroup.end(), 
			multimap<int,int,greater<int> >::value_type(m_mapSinger[*it].iLatestScore, 
			*it));

		if (itMltmapScoreToID == m_mltmapCurGroup.end())
		{
			//û�ҵ�����ʣ����ּ�����ɾ���ø��ֵĲ�����
			it = m_lstRemainingID.erase(it);
		}

		//�����������������
		++iSingerReverseIndexInGroup;

		//��ֹ��������begin()����������--������
		if (it != m_lstRemainingID.begin())
		{
			--it;
		}
	}

	//�������ı�����¼�洢���Ա���һ�������¼�Ĵ洢
	m_mltmapCurGroup.clear();
}

//��̭��
void CSingingCompetition::Knockout()
{
	TRACE("*************��%d����̭����*************\n", m_iRound);

	int iSingerIndex = 0;		//�ڼ������������ݳ���1�����һ�����֣�2����ڶ������֡�����
	for (list<int>::iterator it=m_lstRemainingID.begin(); it!=m_lstRemainingID.end(); )
	{
		++iSingerIndex;

		//���ɸ��ֵķ���
		MakeScore(m_mapSinger[*it]);

		//��¼��ǰ�ݳ�С����ֵĵ÷��������������������
		m_mltmapCurGroup.insert(pair<int,int>(m_mapSinger[*it].iLatestScore, *it));

		if (iSingerIndex%6 == 0)
		{
			//С���ݳ���ϣ���ӡС��÷����
			PrintGroupScore();

			//�ڵ�ǰС������̭����
			EraseInCurGroup();

			//��ʣ�������ɾ������
			EraseInRemainingID(it++);  //������++it���棬��ΪҪת������֮ǰ�ĵ�����
		}
		else
		{
			++it;
		}
	}
}