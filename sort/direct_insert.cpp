/*
ʵ��ֱ�Ӳ�������
��ʼ����:��һ��Ԫ����Ȼ����
ѭ������:�ӵڶ���Ԫ�ؿ�ʼ����������Ԫ�ز��뵽����λ���ϣ�
			������Ҫ����ƶ�Ԫ�أ���һ��Ԫ�ر����������ڱ�
��������:
			ѭ�������һ��Ԫ��


�����ƣ���������
*/
#include <iostream>
#include <vector>
using namespace std;

class Sort
{
public:
	virtual bool init() = 0;//��ʼ������������
	virtual void sort() = 0;//ʵ�������㷨
	virtual void print() = 0;//��ӡ������
};

/*
���������int���ͣ����ǣ����ǵ������޹ص����⣬�������ʹ��
ģ����,��Ӧ�����ͱ�����assignable��comparable��
*/
const unsigned int SIZE = 10;//���ȱ�Ȼ�ǷǸ��������ʹ��unsigned int���Ͻ�
class DirectInsertSort : public Sort
{
public:
	bool init();
	void sort();
	void print();
private:
	void swap(int a, int b);
private:
	//ʹ��vector�������ݣ����볤�ȿ����⣬���ǲ��ù���������ݹ�������
	vector<int> mContainer; 
};

bool DirectInsertSort::init()
{
	//��ʼ����һ���ڱ�Ԫ��
	mContainer.push_back(0);
	long long tmp = 0;
	unsigned int currentSize = 0;
	while(cin >> tmp)
	{
		if(currentSize < SIZE)
		{
			if(tmp > (int)0x7FFFFFFF || tmp < (int)0x80000000)
			{
				cout << "out of range error." << endl;
				return false;
			}
			mContainer.push_back((int)tmp);
			++currentSize;
		}
		else
		{
			break;
		}
	}
	return true;
}

void DirectInsertSort::sort()
{
	//ʵ�ʴ���������鳤����Ҫ��ȥ�ڱ�Ԫ��
	int size = mContainer.size() - 1;
	//ֻ���ڱ�Ԫ��
	if(size  <= 0)
	{
		cout << "no elements" << endl;
		return;
	}


	//���±�1��ʼ����һ��Ԫ����һ����������
	//�ӵڶ���Ԫ�ؿ�ʼִ��ֱ�Ӳ�������
	unsigned int j = 0;
	for(unsigned int i = 2; i <= size; ++i)
	{
		//�����ڱ�Ϊ������Ԫ��
		mContainer[0] = mContainer[i];
		//����ж������Ԫ���Ƿ����ڱ�Ԫ������
		//��������򽫵�ǰԪ�غ���һ��λ��
		 //�ȶ����㷨��ǰ���Ԫ�ش��ں����Ԫ�أ��Żᵼ�½���λ��
		for(j = i - 1; mContainer[j] > mContainer[0]; --j)
		{
			mContainer[j + 1] = mContainer[j];
		}
		mContainer[j + 1] = mContainer[0];
	}
	return;
}

void DirectInsertSort::print()
{
	typedef vector<int>::iterator iter;
	iter it = mContainer.begin();
	iter end = mContainer.end();

	cout << "after sort:" << endl;
	//���ڵ�һ��Ԫ����Ϊ�ڱ�������Թ���Ԫ��
	++it;
	while(it != end)
	{
		cout << *it << endl;
		++it;
	}
	return;
}

void DirectInsertSort::swap(int a, int b)
{
	if(&a == &b || a == b)
	{
		return;
	}
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
	return;
}
int main(int argc, char** argv)
{
	//ʹ�ö�̬
	Sort* obj = new DirectInsertSort();
	if(obj->init())
	{
		obj->sort();
		obj->print();
	}
	

	return 0;
}

