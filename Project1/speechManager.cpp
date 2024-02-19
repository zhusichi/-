#include"speechManager.h"
#include"speaker.h"
speechManager::speechManager()
{
	//初始化容器和属性
	this->initSpeach();

	//创建12名选手
	this->createSpeaker();

	//加载往届记录
	this->loadRecord();
}
//菜单功能
void speechManager::show_Menu()
{
	cout << "********************************" << endl;
	cout << "******* 欢迎参加演讲比赛 *******" << endl;
	cout << "******* 1.开始演讲比赛  ********" << endl;
	cout << "******* 2.查看往届记录  ********" << endl;
	cout << "******* 3.清空比赛记录  ********" << endl;
	cout << "******* 0.退出比赛程序  ********" << endl;
	cout << "********************************" << endl;
	cout << endl;
}

//退出功能
void speechManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}


//初始化容器和属性
void speechManager::initSpeach()
{
	//容器置空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//初始轮数
	this->m_Index = 1;

	//将记录容器清空
	this->m_Record.clear();
}

//创建12名选手
void speechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHILKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j]=0;
		}
		//创建选手编号放入v1
		this->v1.push_back(i + 100001);

		//选手编号及选手放入map
		this->m_Speaker.insert(make_pair(i + 100001, sp));
	}
}

//比赛流程控制函数
void speechManager::startSpeaker()
{
	//第一轮比赛开始

	//抽签
	this->speechDraw();
	
	//比赛
	this->speechContest();

	//显示比赛分数
	this->showscore();

	//第二轮比赛开始
	this->m_Index++;

	//抽签
	this->speechDraw();

	//比赛
	this->speechContest();

	//显示比赛分数
	this->showscore();

	//保存分数到文件中
	this->saveRecord();

	//重置比赛，获取记录
	//初始化容器和属性
	this->initSpeach();

	//创建12名选手
	this->createSpeaker();

	//加载往届记录
	this->loadRecord();
	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");
}

//抽签
void speechManager::speechDraw()
{
	cout << "第<< " << this->m_Index << " >>轮比赛选手正在抽签" << endl;
	cout << "---------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	if (m_Index == 1)
	{
		//第一轮
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it <<" ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "---------------------" << endl;
	system("pause");
	cout << endl;
}

//比赛
void speechManager::speechContest()
{
	cout << "----------第" << this->m_Index << "轮比赛正式开始----------" << endl;

	//临时容器，存放小组成绩
	multimap<double, int, greater<double>>groupScore;

	int num = 0;//记录人员个数

	vector<int>v_Src;//比赛选手容器
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	//遍历所有选手比赛
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//评委打分
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			//cout << score << " ";
			d.push_back(score);
		}
		//cout << endl;
		sort(d.begin(), d.end(), greater<double>());//排序
		d.pop_front();
		d.pop_back();
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();//平均分
		
		//平均分放入map容器
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
		
		//打分数据放入临时小组
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号：" << it->second << " 姓名：" << this->m_Speaker[it->second].m_Name
					<< " 成绩：" << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}
			
		//取走前三
		int count = 0;
		for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count<3; it++,count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}
			groupScore.clear();
			cout << endl;
		}	
	}
	cout << "----------第" << this->m_Index << "轮比赛完毕！----------" << endl;
	system("pause");

}

//显示比赛分数
void speechManager::showscore()
{
	cout << "----------第" << this->m_Index << "轮晋级选手信息如下：----------" << endl;

	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}
	for(vector<int>::iterator it=v.begin();it!=v.end();it++)
	{
		cout << "选手编号：" << *it << " 姓名：" << this->m_Speaker[*it].m_Name << " 得分："
			<< this->m_Speaker[*it].m_Score[this->m_Index-1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}

//保存记录
void speechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//追加方式写文件

	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	ofs.clear();
	cout << "记录已经保存" << endl;

	this->fileIsEmpty = false;
}

//读取记录
void speechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);//读文件

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	this->fileIsEmpty = false;
	ifs.putback(ch);
	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string>v;//存放6个字符串
		

		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();

}

//显示往届记录
void speechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件不存在或为空" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
			{
				cout << "第" << i + 1 << "届"
					<< "冠军编号：" << this->m_Record[i][0] << " 得分：" << this->m_Record[i][1] << " "
					<< "亚军编号：" << this->m_Record[i][2] << " 得分：" << this->m_Record[i][3] << " "
					<< "季军编号：" << this->m_Record[i][4] << " 得分：" << this->m_Record[i][5] << endl;
		
			}
	}
	
	system("pause");
	system("cls");
}

//清空文件
void speechManager::clearRecord()
{
	cout << "是否确定清空文件" << endl;
	cout << " 1、是" << endl;
	cout << " 2、否" << endl;
	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//初始化容器和属性
		this->initSpeach();

		//创建12名选手
		this->createSpeaker();

		//加载往届记录
		this->loadRecord();

		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}
speechManager::~speechManager()
{

}