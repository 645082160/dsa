#include <iostream>
#include <cstring>
class A
{
private:
	int n1, n2;
public:
	A():n2(0), n1(n2 + 2){}
	void print()
	{
		std::cout << "n1:" << n1 << ", n2:" << n2 << std::endl;
		return;
	}

};

int main(int argc, char** argv)
{
	A a;
	a.print();

	const char * p = "";
	std::cout << sizeof(p) << ", " << strlen(p) << std::endl;
	return 0;
}