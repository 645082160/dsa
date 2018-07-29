/*
测试C++11新特性final
禁止派生类重写继承而来的虚函数
*/
#include <iostream>
using namespace std;

/*
记住是cplusplus，不是cpluscplus
*/
#ifdef __cplusplus
	#if __cplusplus < 201103
		#error "compiler not support C++11"
	#endif
#else
	#error "compiler not support g++"
#endif
//基类，含有虚函数，但是声明为final，禁止覆盖
class Base
{
/*
final属性用于禁止派生类再次重新定义接口。
*/
public:
	virtual void print() final;
};

void Base::print()
{
	cout << "Base print()" << endl;
	return;
}

//派生类，尝试重写基类中被声明为final的虚函数，测试是否能够编译通过
class Derived : public Base
{
public:
	void print();
};

void Derived::print()
{
	cout << "Derived print()" << endl;
	return;
}
//static_assert检查是否支持C++11标准

//main
int main(int argc, char** argv)
{
	cout << __cplusplus << endl;
	Base* base = new Derived();
	base->print();
	return 0;
}
