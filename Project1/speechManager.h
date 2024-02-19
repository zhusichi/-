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


	//�˵�����
	void show_Menu();

	//�˳�����
	void exitSystem();

	~speechManager();

	//��ʼ������������
	void initSpeach();

	//����12��ѡ��
	void createSpeaker();

	//�������̿��ƺ���
	void startSpeaker();

	//��ǩ
	void speechDraw();
	
	//����
	void speechContest();

	//��ʾ��������
	void showscore();

	//�����¼
	void saveRecord();

	//��ȡ��¼
	void loadRecord();

	//��ʾ�����¼
	void showRecord();

	//����ļ�
	void clearRecord();

	//�ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;

	map<int, vector<string>>m_Record;

	//��һ��ѡ������
	vector<int>v1;

	//�ڶ���ѡ������
	vector<int>v2;

	//ʤ��ѡ������
	vector<int>vVictory;

	//��ż���Ӧѡ������
	map<int, speaker>m_Speaker;

	//��������
	int m_Index;
};