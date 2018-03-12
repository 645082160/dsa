#include <iostream>
using namespace std;

//使用4X4二维数组表示棋盘，为0表示没有棋子，为1表示有棋子
//判断是否在同一行有棋子
//判断是否在同一列有棋子
//判断是否在2个对角线是否有棋子，这2条对角线的算法是什么呢?

int chessboard[4][4] = {
{0, 0, 0, 0},
{0, 0, 0, 0},
{0, 0, 0, 0},
{0, 0, 0, 0}
};

//检查同一行是否有棋子
bool check_line(int i , int j)
{
	for(int k = 0; k < 4; ++k)
	{
		if(k != i)
		{
			if(chessboard[k][j] == 1)
			{
				return false;
			}
			
		}
	}

	return true;
}

//检查同一列是否有棋子
bool check_column(int i, int j)
{
	for(int k = 0; k < 4; ++k)
	{
		if(k != j)
		{
			if(chessboard[i][k] == 1)
			{
				return false;
			}
		}
	}

	return true;
}

// 4个对角线的试探方向
int dir[4][2] = {
	{-1, -1},
	{1, -1},
	{1, 1},
	{-1, 1}
};
/*
@param i 当前节点的一维坐标
@param j 当前节点的二维坐标
*/
bool check_diagonal(int i, int j)
{
	// m n记录新的坐标
	int m = 0;
	int n = 0;
	for(int k = 0; k < 4; ++k)
	{
		//在沿着方向遍历之前先初始化m、n坐标
		m = i + dir[k][0];
		n = j + dir[k][1];
		while(m < 4 && m >= 0 && n < 4 && n >= 0)
		{
			if(chessboard[m][n] == 1)
			{
				return false;
			}

			m += dir[k][0];
			n += dir[k][1];
		}
	}

	return true;
}

bool check(int i, int j)
{
	return check_line(i, j) && check_column(i, j) && check_diagonal(i, j);
}

void print()
{
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			cout << chessboard[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;

	return;
}
void trail(int i)
{
	if(i >= 4)
	{
		print();
		return;
	}

	for(int j = 0; j < 4; ++j)
	{
		chessboard[i][j] = 1;
		if(check(i, j))//当前棋子合法，继续试探
		{
			trail(i + 1);
		}
		//恢复棋子
		chessboard[i][j] = 0;
	}

	return;
}
int main(int argc, char** argv)
{
	trail(0);
	
	return 0;
}
