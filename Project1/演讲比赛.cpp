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
		cout << "���������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1://��ʼ����
			sm.startSpeaker();
			break;
		case 2://�鿴�������
			sm.showRecord();
			break;
		case 3://��ձ�����¼
			sm.clearRecord();
			break;
		case 0://�˳�ϵͳ
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