#include <iostream>
#include <vector>
using namespace std;


const int SIZE = 10;
// 排序基类
class Sort
{
public:
	virtual bool init() = 0;
	virtual void sort() = 0;
	virtual void print() = 0;
	virtual ~Sort(){}
protected:
	vector<int> mContainer;
};


//quicksort类
class QuickSort : public Sort
{
public:
	bool init();
	void sort();
	/*
		执行快排操作
	*/
	void quickSort(int low, int high);
	/*
		执行一趟排序，并返回支点位置，作为拆分依据
	*/
	int partition(int low, int high);
	void swap(int& a, int& b);
	void print();
};

bool QuickSort::init()
{
	long long tmp = 0;
	int currentSize = 0;

	while(cin >> tmp)
	{
		if(currentSize < SIZE)
		{
			if(tmp > (int)0x7fffffff || tmp < (int)0x80000000)
			{
				cout << "out of range" << endl;
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

void QuickSort::sort()
{
	if(mContainer.size() == 0)
	{
		return;
	}
	quickSort(0, mContainer.size() - 1);
	return;
}


void QuickSort::quickSort(int low, int high)
{
	int pivotLocation = 0;
	//这里把if写成了while导致了问题
	//为什么我老是喜欢出这种低级问题呢?
	/*
	由于将if写成了while导致了死循环，对外表现就是ctrl+d没有反应，
	一度以为是cin的问题，我觉得自己排查问题的方式和习惯也有值得提升
	的地方。通过测试程序可以确认cin没有问题，那么问题应该在其他地方，
	这个结论其实早就该做出来，更快的将问题定位过程向前推进。
	我一直觉得你有这种解决问题的不好的习惯，没办法把不断的尝试结果
	固化下来，通过尝试结果，得出一些有用的结论，这些结论能够推进
	问题的解决，而不是陷入在不断尝试，但是又对解决问题毫无帮助
	的泥沼中。还记得那个数组越界导致的coredump问题么? 你不断的尝试，再
	尝试，但是就是不知道问题在哪里，甚至没有离问题越来越近。
	*/
	if(low < high) 
	{
		pivotLocation = partition(low, high);
		quickSort(low, pivotLocation - 1);
		quickSort(pivotLocation + 1, high);
	}

	return;
}

/*
交替的从两边开始扫描，直到找到支点的正确位置
*/
int QuickSort::partition(int low, int high)
{
	int pivot = mContainer[low];//保存支点信息，low为支点，其被掏空
	while(low < high)
	{
		//从high开始扫描，找到第一个比支点小的数据，并与支点交换
		while(low < high && mContainer[high] >= pivot) --high;
		/*
			将第一个比支点小的元素，放到支点的low位置，
			这个元素变成支点位置，
		*/
		mContainer[low] = mContainer[high];
		//从low开始扫描，找到第一个比支点大的数据
		while(low < high && mContainer[low] <= pivot) ++low;
		mContainer[high] = mContainer[low];
	}

	mContainer[low] = pivot;

	return low;
}


void QuickSort::swap(int& a, int& b)
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

void QuickSort::print()
{
	cout << "after quicksort:" << endl;
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





int main(int argc, char** argv)
{
	Sort* tool = new (nothrow) QuickSort();
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

	delete tool;

	return 0;
}
