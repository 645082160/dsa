#include <iostream>
#include <list>
using std::endl;
using std::cout;
using std::list;

const int ELEM_NUM = 3;

void print(int* res)
{
	for(int i = 0; i < ELEM_NUM; ++i)
	{
		cout << res[i] << " ";
	}

	cout << endl;

	return;
}

void find(int pos, int* a, bool* visit, int* res)
{
	//�ݹ����
	if(pos >= ELEM_NUM)
	{
		print(res);
		return;
	}

	
	//�������з�֧
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
	bool visit[ELEM_NUM] = {false}; //��¼�Ƿ��Ѿ����ʹ�
	
	find(0, a, visit, res);

	return 0;
}
