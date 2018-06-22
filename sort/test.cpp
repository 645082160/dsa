#include <iostream>
using namespace std;

class A
{
public:
	virtual int test() = 0;
};
class B : public A
{
public:
	int test();
};

int B::test()
{
	
	return 0;
}

void swap(int& a, int& b)
{
	a = a + b;
	b = a -b;
	a = a - b;
	return;
}

int main(int argc, char** argv)
{
	int a = 7;
	int b = -1;
	swap(a, a);
	cout <<a << " " << b << endl; 
	return 0;
}

