#include <iostream>
#include <vector>
using namespace std;


//容器总大小
const int SIZE = 10;

//排序抽象类
class Sort
{
public:
	virtual bool init() = 0;
	virtual void sort() = 0;
	virtual void print() = 0;
protected:
	vector<int> mContainer;
};


//简单选择排序类，继承自抽象类
class SimpleSelect : public Sort
{
public:
	bool init();
	void sort();
	void print();
	void swap(int& a, int& b);
	int findMin(int start, int end);
};

bool SimpleSelect::init()
{
	long long tmp = 0;
	int currentSize = 0;
	while(cin >> tmp && currentSize < SIZE)
	{
		if(tmp > (int)0x7FFFFFFF || tmp < (int)0x80000000)
		{
			cout << "out of range." <<endl;
			return false;
		}
		mContainer.push_back(tmp);
		++currentSize;
	}

	return true;
}

void SimpleSelect::sort()
{
	/*
		关于简单选择排序，一直以来的理解都是有误区的。
		首先，说原理的时候，首先确定是正序排列，然后再来说原理。
		首先，第i个位置，从n-i+1中选择最小的数，与第i个元素的位置交换，
		直到最后一个元素
		由于最后一个元素只有一个元素，肯定是最终合适的元素，因此，只需要倒数
		第二个元素找到合适的位置之后，整个排序就结束了
	*/
	//判断容器中元素个数是否大于1，没有元素或者0个元素时，不用排序
	int containerSize = mContainer.size();
	if(containerSize <= 1)
	{
		return;
	}
	//从第一个位置开始，不断重复上述算法，直到倒数第二个元素
	int loopSize = containerSize - 1;
	int minLoc = 0;
	for(int i = 0; i < loopSize; ++i)
	{
		//这里查找最小，是要包括最后一个元素的，因此
		//最后的边界是容器的大小
		//我在第一次实现的时候，错误的将这个参数传递为loopSize这是不对的。
		//想要实现算法，请数形结合
		minLoc= findMin(i, containerSize);
		if(i != minLoc)
		{
			swap(mContainer[i], mContainer[minLoc]);
		}
		
	}

	return;
}

void SimpleSelect::print()
{
	cout << "after simple select sort:" << endl;
	if(mContainer.size() == 0)
	{
		cout << "no elements." << endl;
		return;
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

/*
这个接口必须考虑到如果是同一个变量的问题，自己与自己交换时结果会是0
因此，基于位运算的swap其实是有限制的，但是如果是基于加法,也有同样的问题。
很多运算，其实都要考虑自己与自己进行运算的问题
*/
void SimpleSelect::swap(int& a, int& b)
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

int SimpleSelect::findMin(int start, int end)
{
	//由于是内部调用，不需要检查参数
	int min = mContainer[start];
	int minLoc = start;
	// 区间为[start, end)
	for(int i = start + 1; i < end; ++i)
	{
		if(mContainer[i] < min)
		{
			min = mContainer[i];
			minLoc = i;
		}
	}

	return minLoc;
}


//main函数
int main(int argc, char** argv)
{
	Sort* tool = new (nothrow)SimpleSelect();
	if(tool == NULL)
	{
		cout << "new fail" << endl;
		return -1;
	}

	if(tool->init())
	{
		tool->sort();
		tool->print();
	}
	return 0;
}
