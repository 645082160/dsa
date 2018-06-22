#include <iostream>
using namespace std;

//模板，继承该类的类将被赋予无法被继承的特性
template<class T>
class MakedSealed
{
private:
	friend T;
	MakedSealed(){}
	~MakedSealed(){}
};

//无法被继承类，需要使用虚继承
/*
理解模板的一个很好的方法在于，理解实例化之后的模板，跟一个普通的类其实没有
任何区别，实例化的类就可以被当做一个普通类来使用。
模板与普通的类之间的纽带就是实例化之后的类。
*/
class Sealed : virtual public MakedSealed<Sealed>
{
public:
	Sealed(){cout << "construct Sealed class~" << endl;}
	~Sealed(){cout << "destruct Sealed class~" << endl;}
};

//测试sealedclass 被继承
class Test : public Sealed
{
public:
	Test(){cout << "construct Test" << endl;}
	~Test(){cout << "destruct Test" << endl;}
};

int main(int argc, char** argv)
{
	Sealed sealed;
	Test test;
	return 0;
}