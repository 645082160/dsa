#include <iostream>
#include <vector>
using namespace std;


const int SIZE = 10;
// �������
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


//quicksort��
class QuickSort : public Sort
{
public:
	bool init();
	void sort();
	/*
		ִ�п��Ų���
	*/
	void quickSort(int low, int high);
	/*
		ִ��һ�����򣬲�����֧��λ�ã���Ϊ�������
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
	//�����ifд����while����������
	//Ϊʲô������ϲ�������ֵͼ�������?
	/*
	���ڽ�ifд����while��������ѭ����������־���ctrl+dû�з�Ӧ��
	һ����Ϊ��cin�����⣬�Ҿ����Լ��Ų�����ķ�ʽ��ϰ��Ҳ��ֵ������
	�ĵط���ͨ�����Գ������ȷ��cinû�����⣬��ô����Ӧ���������ط���
	���������ʵ��͸�������������Ľ����ⶨλ������ǰ�ƽ���
	��һֱ�����������ֽ������Ĳ��õ�ϰ�ߣ�û�취�Ѳ��ϵĳ��Խ��
	�̻�������ͨ�����Խ�����ó�һЩ���õĽ��ۣ���Щ�����ܹ��ƽ�
	����Ľ���������������ڲ��ϳ��ԣ������ֶԽ��������ް���
	�������С����ǵ��Ǹ�����Խ�絼�µ�coredump����ô? �㲻�ϵĳ��ԣ���
	���ԣ����Ǿ��ǲ�֪���������������û��������Խ��Խ����
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
����Ĵ����߿�ʼɨ�裬ֱ���ҵ�֧�����ȷλ��
*/
int QuickSort::partition(int low, int high)
{
	int pivot = mContainer[low];//����֧����Ϣ��lowΪ֧�㣬�䱻�Ϳ�
	while(low < high)
	{
		//��high��ʼɨ�裬�ҵ���һ����֧��С�����ݣ�����֧�㽻��
		while(low < high && mContainer[high] >= pivot) --high;
		/*
			����һ����֧��С��Ԫ�أ��ŵ�֧���lowλ�ã�
			���Ԫ�ر��֧��λ�ã�
		*/
		mContainer[low] = mContainer[high];
		//��low��ʼɨ�裬�ҵ���һ����֧��������
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
