#include <iostream>
using namespace std;

//ģ�壬�̳и�����ཫ�������޷����̳е�����
template<class T>
class MakedSealed
{
private:
	friend T;
	MakedSealed(){}
	~MakedSealed(){}
};

//�޷����̳��࣬��Ҫʹ����̳�
/*
���ģ���һ���ܺõķ������ڣ����ʵ����֮���ģ�壬��һ����ͨ������ʵû��
�κ�����ʵ��������Ϳ��Ա�����һ����ͨ����ʹ�á�
ģ������ͨ����֮���Ŧ������ʵ����֮����ࡣ
*/
class Sealed : virtual public MakedSealed<Sealed>
{
public:
	Sealed(){cout << "construct Sealed class~" << endl;}
	~Sealed(){cout << "destruct Sealed class~" << endl;}
};

//����sealedclass ���̳�
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