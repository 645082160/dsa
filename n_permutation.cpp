#include <iostream>
#include <list>
using std::endl;
using std::cout;
using std::list;

const int ELEM_NUM = 3;
const int M = 2;
void print(int* res)
{
	for(int i = 0; i < M; ++i)
	{
		cout << res[i] << " ";
	}

	cout << endl;

	return;
}

void find(int pos, int* a, bool* visit, int* res)
{
	//递归出口
	if(pos >= M)
	{
		print(res);
		return;
	}

	
	//搜索所有分支
	for(int i = 0; i < 3; ++i)
	{
		if(!visit[i])
		{	
			res[pos] = a[i];
			visit[i] = true;
			find(pos+1, a, visit, res);
			visit[i] = false;
		}
	}
	
	return;
}

int main(int argc, char** argv)
{
	int a[ELEM_NUM] = {5, 6, 7};
	int res[ELEM_NUM] = {0};
	bool visit[ELEM_NUM] = {false}; //记录是否已经访问过
	
	find(0, a, visit, res);

	return 0;
}
