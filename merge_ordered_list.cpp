#include <iostream>
using namespace std;
/*
将2个有序线性表合并为1个线性表
*/

void merge(int* a, int len_a, int *b, int len_b, int*& c)
{
	if(a == NULL || len_a <= 0 || b == NULL || len_b <= 0 || c ==NULL)
	{
		cout << "input error" << endl;
		return;
	}
	int i = 0, j = 0, k = 0;
	while(i < len_a && j < len_b)
	{
		a[i] < b[j] ? c[k++] = a[i++] : c[k++] = b[j++];
	}

	while(i < len_a)
	{
		c[k++] = a[i++];
	}

	while(j < len_b)
	{
		c[k++] = b[j++];
	}

	return;
}

void output(int* a, int len)
{
	if(a == NULL || len <= 0)
	{
		cout << "input error" << endl;
		return;
	}
	for(int i = 0; i < len; ++i)
	{
		cout << a[i] << endl;
	}

	cout << "++++++++++++++++" << endl;

	return;
}
int main(int argc, char** argv)
{
	int a[] = {1, 2, 5, 6, 7};
	int len_a = 5;
	int b[] = {3, 4, 5, 9};
	int len_b = 4;

	int* c = new int[9];
	int len_c = 9;

	merge(a, len_a, b, len_b, c);

	output(c, len_c);

	return 0;
}
