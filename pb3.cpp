#include <iostream>
using namespace std;

class Judge
{
public:
	Judge(int elem):m_e(elem)
	{
		cout << "construct Judge " << elem << endl;
	}
	~Judge()
	{
		cout << "destruct Judge " << m_e << endl;
	}
	void check();
private:
	int m_e;
};

void Judge::check()
{
	if((m_e - 1) & m_e)
	{
		cout << "NO." << endl;
	}
	else
	{
		cout << "YES." << endl;
	}
	m_e = 100;

	return;
}


int main(int argc, char** argv)
{
	int val = 0;
	while(true)
	{
		cout << "input element:";
		cin >> val;
		Judge(val).check();
	}
	return 0;
}
