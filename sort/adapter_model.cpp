#include <iostream>
#include <vector>
using namespace std;


class SortAlgorithm
{
public:
	/*
		这里我第一次写的时候出了问题，忘记了virtual关键字
		所以，纯虚函数首先是一个虚函数
	*/
	virtual void sort(vector<int>& container) = 0; 
	/*
		因为是作为一个基类，并且利用了多台，因此将析构函数声明为了virtual，
		但是，我居然忘记给出实现了。
	*/
	virtual ~SortAlgorithm(){}
};

const unsigned int SIZE = 10;
class Sort
{
public:
	Sort():mSortMethod(NULL)
	{}
	~Sort()
	{
		/*
		这个地方，我犯了一个错误，delete了一个不完整的类型，这样是会出现未
		定义的行为的，因此，我觉得如果是实现抽象的类型，那么先给出这个类型的定义
		把框架写完，然后再继承这个抽象类型实现相应的功能即可。
		*/
		if(mSortMethod != NULL)
		{
			delete mSortMethod;
			mSortMethod = NULL;
		}
	}
	bool init();
	void setSortMethod(SortAlgorithm* ptr);
	void sort();
	void print();
private:
	SortAlgorithm* mSortMethod;
	vector<int> mContainer; //第一个位置为哨兵
};

bool Sort::init()
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

void Sort::setSortMethod(SortAlgorithm* ptr)
{
	mSortMethod = ptr;
	return;
}

void Sort::sort()
{
	mSortMethod->sort(mContainer);
	return;	
}

void Sort::print()
{
	if(mContainer.size() == 1)
	{
		return;
	}

	typedef vector<int>::iterator iter;
	iter it = mContainer.begin();
	iter end = mContainer.end();
	++it;
	while(it != end)
	{
		cout << *it << endl;
		++it;
	}
	return;
}

class DirectInsertSort : public SortAlgorithm
{
public:
	void sort(vector<int>& container);
};

void DirectInsertSort::sort(vector<int>& container)
{
	//实际待排序的数组长度需要减去哨兵元素
	int size = container.size() - 1;
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
		container[0] = container[i];
		//逐个判断有序的元素是否与哨兵元素逆序
		//如果逆序，则将当前元素后移一个位置
		 //稳定的算法，前面的元素大于后面的元素，才会导致交换位置
		for(j = i - 1; container[j] > container[0]; --j)
		{
			container[j + 1] = container[j];
		}
		container[j + 1] = container[0];
	}
	return;
}




int main(int argc, char** argv)
{
	SortAlgorithm* ptr = new DirectInsertSort();
	Sort tool;
	tool.setSortMethod(ptr);
	if(tool.init())
	{
		tool.sort();
		tool.print();
	}
	
	return 0;
}