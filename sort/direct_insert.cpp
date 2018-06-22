/*
实现直接插入排序，
开始条件:第一个元素天然有序
循环条件:从第二个元素开始，将待排序元素插入到合适位置上，
			可能需要向后移动元素，第一个元素被用来当做哨兵
结束条件:
			循环到最后一个元素


类的设计，变量命名
*/
#include <iostream>
#include <vector>
using namespace std;

class Sort
{
public:
	virtual bool init() = 0;//初始化待排序数组
	virtual void sort() = 0;//实现排序算法
	virtual void print() = 0;//打印排序结果
};

/*
这里可以是int类型，但是，考虑到类型无关的问题，这里可以使用
模板编程,对应的类型必须是assignable和comparable的
*/
const unsigned int SIZE = 10;//长度必然是非负数，因此使用unsigned int更严谨
class DirectInsertSort : public Sort
{
public:
	bool init();
	void sort();
	void print();
private:
	void swap(int a, int b);
private:
	//使用vector保存数据，输入长度可任意，我们不用管输入的数据过多的情况
	vector<int> mContainer; 
};

bool DirectInsertSort::init()
{
	//初始化第一个哨兵元素
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
	//实际待排序的数组长度需要减去哨兵元素
	int size = mContainer.size() - 1;
	//只有哨兵元素
	if(size  <= 0)
	{
		cout << "no elements" << endl;
		return;
	}


	//从下标1开始，第一个元素是一个有序序列
	//从第二个元素开始执行直接插入排序
	unsigned int j = 0;
	for(unsigned int i = 2; i <= size; ++i)
	{
		//设置哨兵为待排序元素
		mContainer[0] = mContainer[i];
		//逐个判断有序的元素是否与哨兵元素逆序
		//如果逆序，则将当前元素后移一个位置
		 //稳定的算法，前面的元素大于后面的元素，才会导致交换位置
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
	//由于第一个元素作为哨兵，因此略过该元素
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
	//使用多态
	Sort* obj = new DirectInsertSort();
	if(obj->init())
	{
		obj->sort();
		obj->print();
	}
	

	return 0;
}

