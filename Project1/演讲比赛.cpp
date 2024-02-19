#include<iostream>
using namespace std;
#include"speechManager.h"
#include<string>
#include<ctime>
int main()
{
	srand((unsigned int)time(NULL));

	speechManager sm;

	int choice = 0;
	while (true)
	{
		sm.show_Menu();
		cout << "请输入你的选择：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1://开始比赛
			sm.startSpeaker();
			break;
		case 2://查看往届比赛
			sm.showRecord();
			break;
		case 3://清空比赛记录
			sm.clearRecord();
			break;
		case 0://退出系统
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	
	system("pause");
	return 0;
}