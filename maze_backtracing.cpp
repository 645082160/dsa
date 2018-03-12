#include <iostream>
#include <list>
#include <cstdlib>
using namespace std;

const int MAZE_SIZE = 4;
//0表示可以走，1表示不能走
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

//如何记录迷宫路径
//如何判断是否找到了合适的路径
//如何构造下一个分支
//如何回溯,回溯方法有点蛋疼。
void backtrace(int x, int y)
{
	//退出条件
	if(x == ex && y == ey)
	{
		print();
		//最后一个 节点，不需要尝试其任何方向，直接回退
		node tmp1 = path.back();
		visit[tmp1.x][tmp1.y] = 0;
		path.pop_back();
		//cout << "pop3 " << "(" << tmp1.x<< ", " << tmp1.y << ")" << endl;
		return;
	}

	int m = x;
	int n = y;
	//生成分支,每一个方向是一个分支
	for(int i = 0; i < 4; ++i)
	{
		//计算下一个方向的坐标
		m = x + dir[i][0];
		n = y + dir[i][1];
		node tmp = {m, n};
		//判断该点是否可通过
		if(m >=0 && m < MAZE_SIZE 
		&& n >= 0 && n < MAZE_SIZE
		&& maze[m][n] == 0
		&& visit[m][n] != 1)//可通过,尝试该节点的其他方向
		{
			path.push_back(tmp);//将合法的节点加入队列
			visit[m][n] = 1;
			//cout << "push " << "(" << m << ", " << n << ")" << endl;
			//进入下一层分支继续试探
			backtrace(m, n);
		}
		
	}

	
	//当前节点四个方向都尝试完毕，回退到上一个节点
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
