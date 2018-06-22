#include <iostream>
#include <vector>
using namespace std;


const  int SIZE = 10;
class Sort
{
public:
	virtual bool init() = 0;//��ʼ������������s
	virtual void sort() = 0;//ʵ�������㷨
	virtual void print() = 0;//��ӡ������	
protected:
	//���������������ʣ�����������������ʣ�����Ϊprotected
	vector<int> mContainer;
};


class BubbleSort : public Sort
{
public:
	bool init();
	void sort();
	void print();
	/*
	�տ�ʼʱ������Ĳ������������ã����Լ���swap������ָ����ⲻ�������
	*/
	void swap(int& a, int& b);
};


bool BubbleSort::init()
{
	long long tmp = 0;
	int currentSize = 0;
	while(cin >> tmp)
	{
		if(currentSize < SIZE)
		{
			if(tmp > (int)0x7FFFFFFF || tmp < (int)0x80000000)
			{
				cout << "out of range error." << endl;
				return false;
			}

			mContainer.push_back(tmp);
			++currentSize;
		}
		else
		{
			break;
		}
	}
	return true;
}

void BubbleSort::sort()
{
	/*
		�㷨ԭ��:
		�ӵ�һ��Ԫ�ؿ�ʼ�����������Ԫ�أ�ֱ�����һ��Ԫ�أ�����û��һ�֣�
		�����ϸ���ʯͷ�³�������ʯͷ������ӵף����������
	*/
	int containerSize = mContainer.size();
	if(containerSize == 0)
	{
		return;
	}

	int currentSize = containerSize - 1;
	//������ֹ����:ֻ��һ��Ԫ�ص�ʱ�򣬲�����Ҫ����
	//ĳһ����û�з������������㷨����
	for(int i = currentSize; i > 0; --i) 
	{
		bool flag = false;
		for(int j = 0; j < i; ++j)
		{
			if(mContainer[j] > mContainer[j + 1])
			{
				flag = true;
				swap(mContainer[j], mContainer[j + 1]);
			}
		}

		if(flag == false)
		{
			break;
		}

	}
	return;
}

void BubbleSort::print()
{
	cout << "after bubblesort:" << endl;
	if(mContainer.size() == 0)
	{
		cout << "no elements." << endl;
	}

	typedef vector<int>::iterator iter;
	iter it = mContainer.begin();
	iter end = mContainer.end();
	while(it != end)
	{
		cout << *it << endl;
		++it;
	}
	
	return;
}

void BubbleSort::swap(int& a, int& b)
{
	if(&a == &b || a == b)
	{
		return;
	}
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}

int main(int argc, char** argv)
{
	Sort* ptr = new BubbleSort();
	if(ptr->init())
	{
		ptr->sort();
		ptr->print();
	}
	return 0;
}
