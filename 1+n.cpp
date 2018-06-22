#include <iostream>
using namespace std;

class Sum
{
public:
	Sum()
	{
		++m_curr;
		m_sum += m_curr;
	}
	static unsigned int getSum()
	{
		return m_sum;
	}
	static void reset()
	{
		m_curr = 0;
		m_sum = 0;
	}

	static unsigned int operation(int n)
	{
		reset();
	
		Sum* a = new Sum[n];

		delete []a;
		a = NULL;
		
		return getSum();
	}

private:
	static unsigned int  m_curr;
	static unsigned int m_sum;
};

unsigned int Sum::m_sum = 0;
unsigned int Sum::m_curr = 0;

unsigned int solution(int n)
{
	Sum::reset();
	
	Sum* a = new Sum[n];

	delete []a;
	a = NULL;
	
	return Sum::getSum();
}


//使用2个函数指针解决
typedef unsigned int (*sum)(unsigned int);

sum a[2];

unsigned int sumStop(unsigned int n)
{
	return 0;
}

unsigned int sumPlus(unsigned int n)
{
	return a[!!n](n - 1) + n;
}

//使用模板元编程模板实例化+模板特化
template<unsigned int N>
class MySum
{
public:
	enum Value { SUM = N+MySum<N - 1>::SUM};
};

template<>
class MySum<0>
{
public:
	enum Value {SUM};
};

//使用函数模板元编程
template<unsigned int N>
unsigned int sum_fun()
{
	cout << "hello, " << N << endl;
	return N + sum_fun<N-1>();
}

template<>
unsigned int sum_fun<0>()
{
	cout << "hello" << endl;
	return 0;
}

int main(int argc, char** argv)
{
	//cout << solution(100) << endl;
	//cout << Sum::operation(100) << endl;
	/*
	a[0] = sumStop;
	a[1] = sumPlus;
	int n = 100;
	cout << sumPlus(n) << endl;
	*/
	//cout << MySum<100>::SUM << endl;
	
	cout << sum_fun<100>() << endl;
	return 0;
}
