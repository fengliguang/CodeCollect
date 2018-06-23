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
	string strName;		//名字
	int    iLatestScore;	//最新得分
};

#define TRACE printf

class CSingingCompetition
{
public:
	CSingingCompetition(void);
	virtual ~CSingingCompetition(void);

	//对外开放的成员方法
public:
	//报名参加比赛
	void JoinCompetition();

	//第一轮淘汰赛
	void FirstKnockout();

	//第二轮淘汰赛
	void SecondKnockout();

	//决赛
	void Finals();

	//不对外开放的私有成员方法
private:
	//生成歌手的分数
	void MakeScore(Singer &singer);

	//打印当前小组的分数
	void PrintGroupScore();

	//在当前小组中淘汰歌手
	void EraseInCurGroup();

	//在剩余歌手中删除歌手
	void EraseInRemainingID(list<int>::iterator it);

	//淘汰赛
	void Knockout();

	//私有成员变量
private:
	map<int, Singer> m_mapSinger;		//所有的参赛ID与歌手的映射集合。int:参赛ID，Singer:参加比赛的歌手。
	list<int> m_lstRemainingID;			//剩余歌手(没被淘汰的歌手)的参赛ID。int:剩余歌手的参赛ID。
	multimap<int, int, greater<int> > m_mltmapCurGroup;		//当前演唱小组的歌手分数与歌手参赛ID的映射集合。第一个int: 歌手分数；第二个int: 歌手参赛ID；greater<int>: 函数对象，用于歌手分数的降序排列。
	vector<int> m_vecIDBeEliminatedInFirstRound;			//第一轮淘汰赛中被淘汰的歌手参赛的集合。int: 歌手的参赛号。
	multiset<int> m_mltsetScoreBeEliminatedInSecondRound;	//第二轮淘汰赛中被淘汰的歌手分数的集合。int: 歌手的分数。

	int m_iRound;		//第几轮比赛，值为1：第一轮；值为2：第二轮；值为3：第三轮。
};

#endif