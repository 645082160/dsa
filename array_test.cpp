#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
using std::cout;
using std::endl;
using std::string;

class Test
{
public:
	Test()
	{
		cout << "default construct." << endl;
	}
};
int main(int argc, char** argv)
{
	int a[3];
	int b[3] = {1};

	memset(a, 1, sizeof(a));
	for(int i = 0; i < 3; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	for(int i = 0; i < 3; ++i)
	{
		cout << b[i] << " ";
	}
	cout << endl;

	Test c[2];


	int* d = new int[10000];

	for(int i = 0; i < 10000; ++i)
	{
		cout << d[i] << " ";
	}
	cout << endl;
	Test* e = new Test[5];

	//int* f = new int[5]{0};
	//string* g = new string[5]{"foo"};

	string* h = new string[5]();


	cout << sizeof(a) << endl;

	return 0;
}
