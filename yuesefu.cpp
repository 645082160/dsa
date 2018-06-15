#include <iostream>
using namespace std;

void yuesefu(int n, int k, int m)
{
	//�������
	if(n < 1)
	{
		cout << "n not right" << endl;
		return;
	}

	if(k < 0)
	{
		cout << "k not right" << endl;
		return;
	}

	if(m < 0)
	{
		cout << "m not right" << endl;
		return;
	}

	//����ҵ�����
	bool* a = new bool[n];
	for(int i = 0; i < n; ++i)
	{
		a[i] = true;
	}

	int count = 0; //��ɱ����
	//��0��ʼ��ţ�K��ʾ�ӱ��Ϊk��ʼ��������Ŵ�0��ʼ
	for(int i = k, j = 0;; ++i, i = i % n)
	{
		if(a[i])
		{
			++j;
			if(j == m)
			{
				a[i] = false;
				cout << i << " out" << endl;
				j = 0;
				++count;
				if(count == n)
				{
					break;
				}
			}
		}
	}

	cout << "over" << endl;

	return;
}

int main(int argc, char* argv[])
{
	int n = 0, k = 0, m = 0;

	cout << "input n:";
	cin >> n;
	cout << "input k:";
	cin >> k;
	cout << "input m:";
	cin >> m;

	yuesefu(n, k, m);

	return 0;

}

