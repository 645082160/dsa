#include <iostream>
#include <cstring>
using namespace std;

bool find(int* array, int len_b, int elem)
{
	for(int i = 0; i < len_b; ++i)
	{
		if(elem == array[i])
		{
			return true;
		}
	}

	return false;
}
/*
将a和b合并到一起，元素不重复
*/
void merge(int* a, int len_a, int* b, int len_b, int* c, int& len_c)
{
	memcpy(c, a, sizeof(int) * len_a);
	len_c = len_a;
	bool flag = false;
	for(int i = 0; i < len_b; ++i, flag = false)
	{
		if(!find(a, len_a, b[i]))
		{
			c[len_c++] = b[i];
		}
	}

	return;
}

void input(int* & a, int& len)
{
	len = 0;
	while(len <= 0)
	{
		cout << "input array a len";
		cin >> len;
	}

	a = new int(len);

	int input_count = 0;
	cout << "input element";
	while(input_count < len)
	{
		cin >> a[input_count++];
	}

	return;
}
void output(int* array, int len)
{
	cout << "length: " << len << endl;
	
	for(int i = 0; i < len; ++i)
	{
		cout << array[i] << endl;
	}

	cout << "++++++++++++++++++++" << endl;
}
int main(int argc, char** argv)
{
	int* a = NULL, *b = NULL, *c = NULL ;
	int len_a = 0, len_b = 0, len_c = 0;

	input(a, len_a);
	input(b, len_b);

	output(a, len_a);
	output(b, len_b);

	len_c = len_a + len_b;
	c = new int[len_c];

	merge(a, len_a, b, len_b, c, len_c);

	output(c, len_c);

	if(a != NULL)
	{
		delete [] a;
		a = NULL;
	}

	if(b != NULL)
	{
		delete [] b;
		b = NULL;
	}

	if(c != NULL)
	{
		delete [] c;
		c = NULL;
	}
	return 0;
}
