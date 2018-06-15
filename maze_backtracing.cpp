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

void back()
{
	node tmp1 = path.back();
	visit[tmp1.x][tmp1.y] = 0;
	path.pop_back();
	//cout << "pop4 " << "(" << tmp1.x<< ", " << tmp1.y << ")" << endl;
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
			back(); 
		}
		
	}

	return;
}

//另外一种写法，与上面对比下。
void backtrace_1(int x, int y)
{
	//当前节点入栈
	node tmp = {x, y};
	path.push_back(tmp);//将合法的节点加入队列
	visit[x][y] = 1;

	
	//退出条件
	if(x == ex && y == ey)
	{
		print();
		//找到了路径，不需要再试探它的四个方向，执行回溯
	}
	else
	{
		//需要试探它的四个方向，试探完毕后回溯
		int m = x;
		int n = y;
		//生成分支,每一个方向是一个分支
		for(int i = 0; i < 4; ++i)
		{
			//计算下一个方向的坐标
			m = x + dir[i][0];
			n = y + dir[i][1];
			//判断该点是否可通过
			if(m >=0 && m < MAZE_SIZE 
			&& n >= 0 && n < MAZE_SIZE
			&& maze[m][n] == 0
			&& visit[m][n] != 1)//可通过,尝试该节点的其他方向
			{
				//cout << "push " << "(" << m << ", " << n << ")" << endl;
				//进入下一层分支继续试探
				backtrace_1(m, n);
			}	
		}
		//当前节点的4个方向都试探完毕，要想上层返回了，需要back
	}
	
	back();
	return;
}


int main(int argc, char** argv)
{

	node first = {sx, sy};
	path.push_back(first);
	visit[sx][sy] = 1;
	backtrace(sx, sy);
	/*
	另外一种写法:这种写法，在递归返回的时候回溯，形式更统一
	backtrace(sx, sy);
	*/
	return 0;
}
