#include <iostream>
using std::endl;
using std::cout;
using std::cin;

bool res = false; 
void check(int* c, int* w, int c_num, int n, int step)
{
	//�������
	//�ݹ����
	if(step >= n)
	{
		res = true;
		return;
	}
	
	//��֧����, �򵥵�˵:
	//��װ������ظ���������һ����ֻ�л���װ���µ�ʱ��ż������£�������ֹ
	//��ô��װ�����һ����װ�䣬˵�����ֿ���װ�����м�װ��
	for(int i = 0; i < c_num; ++i)
	{
		if(c[i] >= w[step]) //��֦����
		{
			c[i] -= w[step];
			check(c, w, c_num, n, step + 1);
			c[i] += w[step];
		}
	}

	//����

	return;
}
int main(int argc, char** argv)
{
	//����2�����������ͼ�װ�����
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

	//����Ƿ���Խ���װ��ת��2������
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
