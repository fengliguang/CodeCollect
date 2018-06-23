#include "SingingCompetition.h"

CSingingCompetition::CSingingCompetition(void)
{
	//还没开始比赛，比赛轮数设置为0
	m_iRound = 0;

	//设置随机种子
	srand ( (unsigned)time ( 0 ) );
}

CSingingCompetition::~CSingingCompetition(void)
{
}

//报名参加比赛
void CSingingCompetition::JoinCompetition()
{
	if (m_iRound == 0)
	{
		string strNameBaseSource("ABCDEFGHIJKLMNOPQRSTUVWXYZ");  //名字组成元素的来源

		//随机排序名字组成元素的来源
		random_shuffle(strNameBaseSource.begin(), strNameBaseSource.end());

		for (int i=0; i<24; ++i)
		{
			//获取参加比赛的歌手名字
			string strExt(1,strNameBaseSource[i]);

			//构造歌手对象
			Singer singer;
			singer.iLatestScore = 0;
			singer.strName = "选手";
			singer.strName += strExt;

			//录入参加比赛的歌手
			m_mapSinger.insert(pair<int, Singer>(i+100, singer));
			m_lstRemainingID.push_back(i+100);
		}

		//打印参加比赛的歌手名字与参赛号
		TRACE("*******************************************************\n");
		TRACE("参加比赛的歌手名字与参赛号：\n");
		for (map<int,Singer>::iterator it=m_mapSinger.begin(); it!=m_mapSinger.end(); ++it)
		{
			TRACE("%s，参赛号：%d\n", it->second.strName.c_str(), it->first);
		}
		TRACE("\n");
	}
}

//第一轮淘汰赛
void CSingingCompetition::FirstKnockout()
{
	if (m_iRound == 0)
	{
		m_iRound = 1;

		//进行淘汰赛
		Knockout();

		TRACE("第%d轮淘汰赛中被淘汰的歌手的名字：\n", m_iRound);
		for (vector<int>::iterator it=m_vecIDBeEliminatedInFirstRound.begin(); it!=m_vecIDBeEliminatedInFirstRound.end(); ++it)
		{
			TRACE("%s ", m_mapSinger[*it].strName.c_str());
		}
		TRACE("\n");
		TRACE("\n");
	}
}

//第二轮淘汰赛
void CSingingCompetition::SecondKnockout()
{
	if (m_iRound == 1)
	{
		m_iRound = 2;

		//进行淘汰赛
		Knockout();

		TRACE("第%d轮淘汰赛中被淘汰的歌手的分数：\n", m_iRound);
		for (multiset<int>::iterator it=m_mltsetScoreBeEliminatedInSecondRound.begin(); it!=m_mltsetScoreBeEliminatedInSecondRound.end(); ++it)
		{
			TRACE("%d ", *it);
		}
		TRACE("\n");
		TRACE("\n");
	}
}

//决赛
void CSingingCompetition::Finals()
{
	if (m_iRound == 2)
	{
		m_iRound = 3;

		//第三轮决赛
		for (list<int>::iterator it=m_lstRemainingID.begin(); it!=m_lstRemainingID.end(); ++it)
		{
			//生成歌手的分数
			MakeScore(m_mapSinger[*it]);

			//记录当前小组歌手的得分情况，按分数降序排列
			m_mltmapCurGroup.insert(pair<int,int>(m_mapSinger[*it].iLatestScore, *it));
		}

		//打印小组决赛情况
		TRACE("*************小组决赛情况：*************\n");
		for (multimap<int,int, greater<int> >::iterator it=m_mltmapCurGroup.begin(); it!=m_mltmapCurGroup.end(); ++it)
		{
			TRACE("%s的得分：%d\n", m_mapSinger[it->second].strName.c_str() ,it->first);
		}
		TRACE("\n");

		//清除所有的数据
		m_mapSinger.clear();
		m_lstRemainingID.clear();
		m_vecIDBeEliminatedInFirstRound.clear();
		m_mltsetScoreBeEliminatedInSecondRound.clear();
		m_mltmapCurGroup.clear();
		m_iRound = 0;
	}
}

//生成歌手的分数
void CSingingCompetition::MakeScore(Singer &singer)
{
	deque<int> deqScore;

	//十个评委分别对歌手打分
	for (int i=0; i<10; ++i)
	{
		int iScore = 60 + rand()%40;
		deqScore.push_back(iScore);
	}

	//为十个评委的打分排序
	sort(deqScore.begin(), deqScore.end());

	//去掉一个最高分，去掉一个最低分
	deqScore.pop_front();
	deqScore.pop_back();

	//求八个评委打分的总和
	int iScoreSum = accumulate(deqScore.begin(), deqScore.end(), 0);

	//求八个评委打分的平均分
	int iScoreAverage = (int)(iScoreSum/deqScore.size());

	//给歌手设置得分
	singer.iLatestScore = iScoreAverage;
}

//打印当前小组的分数
void CSingingCompetition::PrintGroupScore()
{
	TRACE("小组得分情况：\n");
	for (multimap<int,int, greater<int> >::iterator it=m_mltmapCurGroup.begin(); it!=m_mltmapCurGroup.end(); ++it)
	{
		TRACE("%s的得分：%d\n", m_mapSinger[it->second].strName.c_str() ,it->first);
	}
	TRACE("\n");
}

//在当前小组中淘汰歌手
void CSingingCompetition::EraseInCurGroup()
{
	int iSingerLastIndexInGroup = 0;		//组内歌手的倒数索引
	while(iSingerLastIndexInGroup<3)
	{
		//获取当前演唱小组的最后一个元素的迭代器
		multimap<int,int,greater<int> >::iterator it=m_mltmapCurGroup.end();
		--it;

		++iSingerLastIndexInGroup;

		if (m_iRound == 1)
		{
			//记录第一轮淘汰赛中被淘汰的歌手的参赛号
			m_vecIDBeEliminatedInFirstRound.push_back(it->second);
		}
		else if (m_iRound == 2)
		{
			//记录第二轮淘汰赛中被淘汰的歌手的分数
			m_mltsetScoreBeEliminatedInSecondRound.insert(m_mapSinger[it->second].iLatestScore);
		}

		//从当前演唱小组的集合容器中删除最后一个元素
		m_mltmapCurGroup.erase(it);
	}
}

//在剩余歌手中删除歌手
void CSingingCompetition::EraseInRemainingID(list<int>::iterator it)
{
	int iSingerReverseIndexInGroup = 0;		//逆向遍历的索引
	while(iSingerReverseIndexInGroup<6)
	{
		//查找逆向遍历迭代器所指的参赛ID所对应歌手的{分数，参赛ID}是否在当前演唱小组中
		multimap<int,int,greater<int> >::iterator itMltmapScoreToID = 
			find(m_mltmapCurGroup.begin(),m_mltmapCurGroup.end(), 
			multimap<int,int,greater<int> >::value_type(m_mapSinger[*it].iLatestScore, 
			*it));

		if (itMltmapScoreToID == m_mltmapCurGroup.end())
		{
			//没找到，从剩余歌手集合中删除该歌手的参赛号
			it = m_lstRemainingID.erase(it);
		}

		//逆向遍历的索引自增
		++iSingerReverseIndexInGroup;

		//防止对容器的begin()迭代器进行--操作。
		if (it != m_lstRemainingID.begin())
		{
			--it;
		}
	}

	//清除该组的比赛记录存储，以便下一组比赛记录的存储
	m_mltmapCurGroup.clear();
}

//淘汰赛
void CSingingCompetition::Knockout()
{
	TRACE("*************第%d轮淘汰赛：*************\n", m_iRound);

	int iSingerIndex = 0;		//第几个歌手正在演唱，1代表第一个歌手，2代表第二个歌手。。。
	for (list<int>::iterator it=m_lstRemainingID.begin(); it!=m_lstRemainingID.end(); )
	{
		++iSingerIndex;

		//生成歌手的分数
		MakeScore(m_mapSinger[*it]);

		//记录当前演唱小组歌手的得分情况，按分数降序排列
		m_mltmapCurGroup.insert(pair<int,int>(m_mapSinger[*it].iLatestScore, *it));

		if (iSingerIndex%6 == 0)
		{
			//小组演唱完毕，打印小组得分情况
			PrintGroupScore();

			//在当前小组中淘汰歌手
			EraseInCurGroup();

			//在剩余歌手中删除歌手
			EraseInRemainingID(it++);  //不可用++it代替，因为要转入自增之前的迭代器
		}
		else
		{
			++it;
		}
	}
}