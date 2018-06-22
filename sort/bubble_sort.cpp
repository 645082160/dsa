#include <iostream>
#include <vector>
using namespace std;


const  int SIZE = 10;
class Sort
{
public:
	virtual bool init() = 0;//初始化待排序数组s
	virtual void sort() = 0;//实现排序算法
	virtual void print() = 0;//打印排序结果	
protected:
	//如果不允许类外访问，但是允许派生类访问，设置为protected
	vector<int> mContainer;
};


class BubbleSort : public Sort
{
public:
	bool init();
	void sort();
	void print();
	/*
	刚开始时，传入的参数并不是引用，你自己对swap函数的指责理解不清楚啊。
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
		算法原理:
		从第一个元素开始，交换逆序的元素，直到最后一个元素，这样没过一轮，
		泡泡上浮，石头下沉，最大的石头会沉到河底，如此往复。
	*/
	int containerSize = mContainer.size();
	if(containerSize == 0)
	{
		return;
	}

	int currentSize = containerSize - 1;
	//关于终止条件:只有一个元素的时候，不再需要交换
	//某一轮中没有发生交换，则算法结束
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
