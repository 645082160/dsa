#include <iostream>
#include <queue>

using namespace std;

int main(int argc, char* argv[])
{
	//������������
	int boyn = 0;
	while(true)
	{
		cout << "input boy number:";
		cin >> boyn;
		if(boyn > 0)
		{
			break;
		}
		cout << "invaid input!" << endl;
		boyn = 0;
	}
	//����������������������ڶ�ͷ
	queue<string> boyq;
	string name;
	cout << "boys name:";
	for(int i = 0; i < boyn; ++i)
	{
		cin >> name;
		boyq.push(name);
	}
	//����Ů������
	int girln = 0;
	while(true)
	{
		cout << "input girl number:";
		cin >> girln;
		if(girln > 0)
		{
			break;
		}
		cout << "invaid input!" << endl;
		girln = 0;
	}
	//����Ů����������������ڶ�ͷ
	queue<string> girlq;
	cout << "girls name:";
	for(int i = 0; i < girln; ++i)
	{
		cin >> name;
		girlq.push(name);
	}
	//��������
	int round = 0;
	while(true)
	{
		cout << "input round number:";
		cin >> round;
		if(round > 0)
		{
			break;
		}
		cout << "invaid input!" << endl;
		round = 0;
	}

	string boyname, girlname;
	for(int i = 0; i < (round - 1); ++i)
	{
		boyname = boyq.front();
		boyq.pop();
		boyq.push(boyname);
		
		girlname = girlq.front();
		girlq.pop();
		girlq.push(girlname);
	}

	cout << "res:" << boyq.front() << " " << girlq.front() << endl;

	return 0;
}
