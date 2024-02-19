#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include"speaker.h"
#include<algorithm>
#include<deque>
#include<numeric>
#include<fstream>


class speechManager
{
public:
	speechManager();


	//菜单功能
	void show_Menu();

	//退出功能
	void exitSystem();

	~speechManager();

	//初始化容器和属性
	void initSpeach();

	//创建12名选手
	void createSpeaker();

	//比赛流程控制函数
	void startSpeaker();

	//抽签
	void speechDraw();
	
	//比赛
	void speechContest();

	//显示比赛分数
	void showscore();

	//保存记录
	void saveRecord();

	//读取记录
	void loadRecord();

	//显示往届记录
	void showRecord();

	//清空文件
	void clearRecord();

	//判断文件是否为空
	bool fileIsEmpty;

	map<int, vector<string>>m_Record;

	//第一轮选手容器
	vector<int>v1;

	//第二轮选手容器
	vector<int>v2;

	//胜出选手容器
	vector<int>vVictory;

	//编号及对应选手容器
	map<int, speaker>m_Speaker;

	//比赛轮数
	int m_Index;
};