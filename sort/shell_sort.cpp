/*
shell排序，根据步长数组，先将数组分割为不同的子数组，子数组先排序，
使整个数组大概有序，再对这个大概有序的数组进行排序。
因为对于直接插入排序来说，有序数组的算法时间复杂度是n
*/

#include <iostream>
#include <vector>
using namespace std;


const unsigned int SIZE = 10;//元素个数，步长数组的长度
class Sort
{
public:
	virtual bool init() = 0;//初始化待排序数组
	virtual void sort() = 0;//实现排序算法
	virtual void print() = 0;//打印排序结果
};

class ShellSort : public Sort
{
public:
	bool init();
	void sort();
	void shellInsert(int step);
	void print();
private:
	vector<int> mDeltaArray;//步长数组,delta表示数学中的增量
	vector<int> mContainer;//数组容器	
};

bool  ShellSort::init()
{
	//初始化步长数组
	mDeltaArray.push_back(5);
	mDeltaArray.push_back(2);
	mDeltaArray.push_back(1);//最后一个步长必须是1
	//初始化待排序数组
	mContainer.push_back(0);//第一个元素是哨兵
	cout << "input elements:" << endl;

	//输入元素
	long long tmp = 0;
	unsigned int currentSize = 0;
	while(cin >> tmp)
	{
		if(currentSize < SIZE)
		{
			if(tmp > (int)0x7FFFFFFF || tmp < (int)0x80000000)
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

void ShellSort::sort()
{
	//遍历步长数组，每个步长得到一个子数组，并进行直接插入排序
	unsigned int deltaArraySize = mDeltaArray.size();
	if(deltaArraySize == 0 || mDeltaArray[deltaArraySize - 1] != 1)
	{
		cout << "delta array error." << endl;
		return;
	}
	
	unsigned int containerSize = mContainer.size() - 1;
	if(containerSize == 0)
	{
		cout << "no elements" << endl;
		return;
	}
	
	/*
	我编写这段代码的时候，是直接编写的，这样其实抽象的不好
	观察书上的代码，我发现，将这段代码抽象成一个函数，格调更高，
	也更加简洁，从功能上看，也确实每个步长的排序其实是一个内聚度
	很高的操作集合，应该被放到一个函数中。
	像我这样顺序的编写代码，其实是写代码的意识不好，抽象意识不够
	的表现。
	*/
	for(unsigned int k = 0; k < deltaArraySize; ++k)
	{
		shellInsert(mDeltaArray[k]);
	}
	
	return;
}


void ShellSort::shellInsert(int dk)
{
	//对每个步长，在子数组中做直接插入排序
	//其实，你可以看到，本质还是在做直接插入排序
	 //通过子数组先排序，做到让数组基本有序，最后再整个排序
	 //提升排序的效率
	 //0号元素用于暂存元素
	unsigned int containerSize = mContainer.size() - 1;
	//第一次编写的时候，我写成了unsigned int,导致了越界，j变成了一个非常大的数
	//j是可能为负的，因此不能是unsigned int 
	int j = 0;
	for(int i = dk + 1; i <= containerSize; ++i)
	{
		//将元素放入到0号元素暂存
		mContainer[0] = mContainer[i];
		//对每一个待排序元素，做直接插入排序
		for(j = i - dk; j > 0 && mContainer[j] > mContainer[0]; j -= dk)
		{
			//这里再次出错，原来赋值的是mContainer[0]
			//我没搞懂为什么我会这么写，到底是哪里出了问题
			//导致我犯这种低级错误的呢?
			mContainer[j + dk] = mContainer[j]; 
		}

		mContainer[j + dk] = mContainer[0];
	}

	return;
}

void ShellSort::print()
{
	typedef vector<int>::iterator iter;
	iter it = mContainer.begin();
	iter end = mContainer.end();
	//哨兵不输出
	++it;
	cout << "after sort:" << endl;
	while(it != end)
	{
		cout << *it << endl;
		++it;
	}
	return;
}
int main(int argc, char** argv)
{
	Sort* ptr = new ShellSort();
	if(ptr->init())
	{
		ptr->sort();
		ptr->print();
	}
	return 0;
}