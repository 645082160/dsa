#include <iostream>
#include <list>
#include <cstdlib>
using namespace std;

const int MAZE_SIZE = 4;
//0��ʾ�����ߣ�1��ʾ������
int maze[MAZE_SIZE][MAZE_SIZE] = 
{
	{0, 0, 0, 1},
	{0, 0, 1, 0},
	{0, 0, 1, 0},
	{1, 0, 0, 0}
};

int visit[MAZE_SIZE][MAZE_SIZE] = 
{
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}
};

int dir_record[MAZE_SIZE][MAZE_SIZE] = 
{
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}
};
int dir[4][2] = {
	{1, 0},
	{0, 1},
	{-1, 0},
	{0, -1}
};

int sx = 0;
int sy = 1;
int ex = 3;
int ey = 2;

struct node{
	int x;
	int y;
};


list<node> path;
void print()
{
	list<node>::iterator it = path.begin();
	list<node>::iterator end = path.end();

	while(it != end)
	{
		cout << "(" << it->x << ", " << it->y << ")" << endl;
		++it;
	}
	cout << endl;
	return;
}

//��μ�¼�Թ�·��
//����ж��Ƿ��ҵ��˺��ʵ�·��
//��ι�����һ����֧
//��λ���,���ݷ����е㵰�ۡ�
void backtrace(int x, int y)
{
	//�˳�����
	if(x == ex && y == ey)
	{
		print();
		//���һ�� �ڵ㣬����Ҫ�������κη���ֱ�ӻ���
		node tmp1 = path.back();
		visit[tmp1.x][tmp1.y] = 0;
		path.pop_back();
		//cout << "pop3 " << "(" << tmp1.x<< ", " << tmp1.y << ")" << endl;
		return;
	}

	int m = x;
	int n = y;
	//���ɷ�֧,ÿһ��������һ����֧
	for(int i = 0; i < 4; ++i)
	{
		//������һ�����������
		m = x + dir[i][0];
		n = y + dir[i][1];
		node tmp = {m, n};
		//�жϸõ��Ƿ��ͨ��
		if(m >=0 && m < MAZE_SIZE 
		&& n >= 0 && n < MAZE_SIZE
		&& maze[m][n] == 0
		&& visit[m][n] != 1)//��ͨ��,���Ըýڵ����������
		{
			path.push_back(tmp);//���Ϸ��Ľڵ�������
			visit[m][n] = 1;
			//cout << "push " << "(" << m << ", " << n << ")" << endl;
			//������һ���֧������̽
			backtrace(m, n);
		}
		
	}

	
	//��ǰ�ڵ��ĸ����򶼳�����ϣ����˵���һ���ڵ�
	node tmp1 = path.back();
	visit[tmp1.x][tmp1.y] = 0;
	path.pop_back();
	//cout << "pop2 " << "(" << tmp1.x<< ", " << tmp1.y << ")" << endl;
	
	return;
}

int main(int argc, char** argv)
{

	node first = {sx, sy};
	path.push_back(first);
	visit[sx][sy] = 1;
	backtrace(sx, sy);
	return 0;
}
