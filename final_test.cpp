/*
����C++11������final
��ֹ��������д�̳ж������麯��
*/
#include <iostream>
using namespace std;

/*
��ס��cplusplus������cpluscplus
*/
#ifdef __cplusplus
	#if __cplusplus < 201103
		#error "compiler not support C++11"
	#endif
#else
	#error "compiler not support g++"
#endif
//���࣬�����麯������������Ϊfinal����ֹ����
class Base
{
/*
final�������ڽ�ֹ�������ٴ����¶���ӿڡ�
*/
public:
	virtual void print() final;
};

void Base::print()
{
	cout << "Base print()" << endl;
	return;
}

//�����࣬������д�����б�����Ϊfinal���麯���������Ƿ��ܹ�����ͨ��
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
//static_assert����Ƿ�֧��C++11��׼

//main
int main(int argc, char** argv)
{
	cout << __cplusplus << endl;
	Base* base = new Derived();
	base->print();
	return 0;
}
