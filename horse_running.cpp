#include <iostream>
#include <list>
#include <cstdlib>
using namespace std;

//值为1表示已经走过，值为0表示没有走过
int map[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};

int dir[8][2] = {
	{-2, 1},
	{-1, 2},
	{1, 2},
	{2, 1},
	{2, -1},
	{1, -2},
	{-1, -2},
	{-2, -1}
};

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
	node tmp = path.back();
	map[tmp.x][tmp.y] = 0;
	path.pop_back();
	return;
}
//输入一个点的坐标，判断这个点的4个方向是否可以行走
//坐标值满足条件，没有走过则设置走过
//回退的时候，需要将 走过标志以及记录周游路径的list
void find(int x, int y)
{
	if(path.size() == 64)
	{
		print();
		back();
		exit(-1);
	}

	int m = 0, n = 0;
	for(int i = 0; i < 8; ++i)
	{
		//更新坐标，尝试新的方向
		m = x + dir[i][0];
		n = y + dir[i][1];
		if(m >=0 && m <8
		&& n >= 0 && n < 8
		&& map[m][n] != 1)
		{
			node tmp = {m, n};
			path.push_back(tmp);
			map[m][n] = 1;
			find(m, n);
		}
	}

	back();

	return;
}


int main(int argc, char** argv)
{
	int sx = 0;
	int sy = 0;

	node tmp = {sx, sy};
	path.push_back(tmp);
	map[sx][sy] = 1;
	find(sx, sy);
	
	return 0;
}
