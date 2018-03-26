#include <iostream>
using std::endl;
using std::cout;

const int ELEM_SIZE = 4;
const int M = 3;

void print(int* res)
{
	for(int i = 0; i < M; ++i)
	{
		cout << res[i] << " ";
	}

	cout << endl;

	return;
}

void find_combination(int step, int start, int* a, int* res)
{
	//递归出口
	if(step >= M)
	{
		print(res);
		return;
	}
	//分支回溯
	//这里没有执行回溯操作是因为传递参数的方式保证了
	//这里是基于位置模型的算法实现模式
	//从函数返回后，step和i都已经是原有的状态
	for(int i = start; i < ELEM_SIZE; ++i)
	{
		res[step] = a[i];
		find_combination(step + 1, i + 1, a, res);
	}

	//返回
	return;
}
int main(int argc, char** argv)
{
	int a[ELEM_SIZE] = {4, 8, 9, 2};
	int res[M] = {0};
	find_combination(0, 0, a, res);
	return 0;
}
