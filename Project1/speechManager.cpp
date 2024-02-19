#include"speechManager.h"
#include"speaker.h"
speechManager::speechManager()
{
	//��ʼ������������
	this->initSpeach();

	//����12��ѡ��
	this->createSpeaker();

	//���������¼
	this->loadRecord();
}
//�˵�����
void speechManager::show_Menu()
{
	cout << "********************************" << endl;
	cout << "******* ��ӭ�μ��ݽ����� *******" << endl;
	cout << "******* 1.��ʼ�ݽ�����  ********" << endl;
	cout << "******* 2.�鿴�����¼  ********" << endl;
	cout << "******* 3.��ձ�����¼  ********" << endl;
	cout << "******* 0.�˳���������  ********" << endl;
	cout << "********************************" << endl;
	cout << endl;
}

//�˳�����
void speechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}


//��ʼ������������
void speechManager::initSpeach()
{
	//�����ÿ�
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//��ʼ����
	this->m_Index = 1;

	//����¼�������
	this->m_Record.clear();
}

//����12��ѡ��
void speechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHILKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];

		speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j]=0;
		}
		//����ѡ�ֱ�ŷ���v1
		this->v1.push_back(i + 100001);

		//ѡ�ֱ�ż�ѡ�ַ���map
		this->m_Speaker.insert(make_pair(i + 100001, sp));
	}
}

//�������̿��ƺ���
void speechManager::startSpeaker()
{
	//��һ�ֱ�����ʼ

	//��ǩ
	this->speechDraw();
	
	//����
	this->speechContest();

	//��ʾ��������
	this->showscore();

	//�ڶ��ֱ�����ʼ
	this->m_Index++;

	//��ǩ
	this->speechDraw();

	//����
	this->speechContest();

	//��ʾ��������
	this->showscore();

	//����������ļ���
	this->saveRecord();

	//���ñ�������ȡ��¼
	//��ʼ������������
	this->initSpeach();

	//����12��ѡ��
	this->createSpeaker();

	//���������¼
	this->loadRecord();
	cout << "���������ϣ�" << endl;
	system("pause");
	system("cls");
}

//��ǩ
void speechManager::speechDraw()
{
	cout << "��<< " << this->m_Index << " >>�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "---------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;
	if (m_Index == 1)
	{
		//��һ��
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

//����
void speechManager::speechContest()
{
	cout << "----------��" << this->m_Index << "�ֱ�����ʽ��ʼ----------" << endl;

	//��ʱ���������С��ɼ�
	multimap<double, int, greater<double>>groupScore;

	int num = 0;//��¼��Ա����

	vector<int>v_Src;//����ѡ������
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	//��������ѡ�ֱ���
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//��ί���
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			//cout << score << " ";
			d.push_back(score);
		}
		//cout << endl;
		sort(d.begin(), d.end(), greater<double>());//����
		d.pop_front();
		d.pop_back();
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();//ƽ����
		
		//ƽ���ַ���map����
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
		
		//������ݷ�����ʱС��
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С���������" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "��ţ�" << it->second << " ������" << this->m_Speaker[it->second].m_Name
					<< " �ɼ���" << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}
			
		//ȡ��ǰ��
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
	cout << "----------��" << this->m_Index << "�ֱ�����ϣ�----------" << endl;
	system("pause");

}

//��ʾ��������
void speechManager::showscore()
{
	cout << "----------��" << this->m_Index << "�ֽ���ѡ����Ϣ���£�----------" << endl;

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
		cout << "ѡ�ֱ�ţ�" << *it << " ������" << this->m_Speaker[*it].m_Name << " �÷֣�"
			<< this->m_Speaker[*it].m_Score[this->m_Index-1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}

//�����¼
void speechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//׷�ӷ�ʽд�ļ�

	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	ofs.clear();
	cout << "��¼�Ѿ�����" << endl;

	this->fileIsEmpty = false;
}

//��ȡ��¼
void speechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);//���ļ�

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
		vector<string>v;//���6���ַ���
		

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

//��ʾ�����¼
void speechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "�ļ������ڻ�Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
			{
				cout << "��" << i + 1 << "��"
					<< "�ھ���ţ�" << this->m_Record[i][0] << " �÷֣�" << this->m_Record[i][1] << " "
					<< "�Ǿ���ţ�" << this->m_Record[i][2] << " �÷֣�" << this->m_Record[i][3] << " "
					<< "������ţ�" << this->m_Record[i][4] << " �÷֣�" << this->m_Record[i][5] << endl;
		
			}
	}
	
	system("pause");
	system("cls");
}

//����ļ�
void speechManager::clearRecord()
{
	cout << "�Ƿ�ȷ������ļ�" << endl;
	cout << " 1����" << endl;
	cout << " 2����" << endl;
	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//��ʼ������������
		this->initSpeach();

		//����12��ѡ��
		this->createSpeaker();

		//���������¼
		this->loadRecord();

		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}
speechManager::~speechManager()
{

}