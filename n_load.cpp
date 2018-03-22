#include <iostream>
using std::endl;
using std::cout;
using std::cin;

bool res = false; 
void check(int* c, int* w, int c_num, int n, int step)
{
	//参数检查
	//递归出口
	if(step >= n)
	{
		res = true;
		return;
	}
	
	//分支回溯, 简单的说:
	//集装箱的总重跟货轮总重一样，只有货轮装的下的时候才继续往下，否则终止
	//那么当装完最后一个集装箱，说明货轮可以装下所有集装箱
	for(int i = 0; i < c_num; ++i)
	{
		if(c[i] >= w[step]) //剪枝操作
		{
			c[i] -= w[step];
			check(c, w, c_num, n, step + 1);
			c[i] += w[step];
		}
	}

	//返回

	return;
}
int main(int argc, char** argv)
{
	//输入2个货轮重量和集装箱个数
	int c[2] = {0};
	int n = 0;
	cout << "c1, c2, n";
	cin >> c[0] >> c[1] >> n;
	cout << "input every box weight:";

	int* w = new int[n];
	for(int i = 0; i < n; ++i)
	{
		cin >> w[i];
	}

	//检查是否可以将集装箱转入2个货轮
	check(c, w, 2, n, 0);

	if(res)
	{
		cout << "Yes";
	}
	else
	{
		cout << "No";
	}
	cout << endl;
	
	return 0;
}
