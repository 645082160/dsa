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
	//�ݹ����
	if(step >= M)
	{
		print(res);
		return;
	}
	//��֧����
	//����û��ִ�л��ݲ�������Ϊ���ݲ����ķ�ʽ��֤��
	//�����ǻ���λ��ģ�͵��㷨ʵ��ģʽ
	//�Ӻ������غ�step��i���Ѿ���ԭ�е�״̬
	for(int i = start; i < ELEM_SIZE; ++i)
	{
		res[step] = a[i];
		find_combination(step + 1, i + 1, a, res);
	}

	//����
	return;
}
int main(int argc, char** argv)
{
	int a[ELEM_SIZE] = {4, 8, 9, 2};
	int res[M] = {0};
	find_combination(0, 0, a, res);
	return 0;
}
