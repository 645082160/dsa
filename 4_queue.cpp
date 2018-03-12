#include <iostream>
using namespace std;

//ʹ��4X4��ά�����ʾ���̣�Ϊ0��ʾû�����ӣ�Ϊ1��ʾ������
//�ж��Ƿ���ͬһ��������
//�ж��Ƿ���ͬһ��������
//�ж��Ƿ���2���Խ����Ƿ������ӣ���2���Խ��ߵ��㷨��ʲô��?

int chessboard[4][4] = {
{0, 0, 0, 0},
{0, 0, 0, 0},
{0, 0, 0, 0},
{0, 0, 0, 0}
};

//���ͬһ���Ƿ�������
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

//���ͬһ���Ƿ�������
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

// 4���Խ��ߵ���̽����
int dir[4][2] = {
	{-1, -1},
	{1, -1},
	{1, 1},
	{-1, 1}
};
/*
@param i ��ǰ�ڵ��һά����
@param j ��ǰ�ڵ�Ķ�ά����
*/
bool check_diagonal(int i, int j)
{
	// m n��¼�µ�����
	int m = 0;
	int n = 0;
	for(int k = 0; k < 4; ++k)
	{
		//�����ŷ������֮ǰ�ȳ�ʼ��m��n����
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
		if(check(i, j))//��ǰ���ӺϷ���������̽
		{
			trail(i + 1);
		}
		//�ָ�����
		chessboard[i][j] = 0;
	}

	return;
}
int main(int argc, char** argv)
{
	trail(0);
	
	return 0;
}
