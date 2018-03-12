#include <iostream>
using namespace std;

typedef struct Job
{
	int a;
	int b;
}job;


template <typename T> void visit(T p);
template <typename T>
void print(T p)
{
	visit(p);
	return;
}

template<> void visit<job>(Job p)
{
	cout << p.a << ", " << p.b << endl;
	return;
}


template<> void visit<int>(int p)
{
	cout << "hello, " << p << endl;
	return;
}
int main(int argc, char** argv)
{
	Job a;
	a.a = 10;
	a.b = 20;
	print(a);

	int b = 100;
	print(b);
	return 0;
}
