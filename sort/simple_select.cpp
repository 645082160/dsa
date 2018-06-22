#include <iostream>
#include <vector>
using namespace std;


//�����ܴ�С
const int SIZE = 10;

//���������
class Sort
{
public:
	virtual bool init() = 0;
	virtual void sort() = 0;
	virtual void print() = 0;
protected:
	vector<int> mContainer;
};


//��ѡ�������࣬�̳��Գ�����
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
		���ڼ�ѡ������һֱ��������ⶼ���������ġ�
		���ȣ�˵ԭ���ʱ������ȷ�����������У�Ȼ������˵ԭ��
		���ȣ���i��λ�ã���n-i+1��ѡ����С���������i��Ԫ�ص�λ�ý�����
		ֱ�����һ��Ԫ��
		�������һ��Ԫ��ֻ��һ��Ԫ�أ��϶������պ��ʵ�Ԫ�أ���ˣ�ֻ��Ҫ����
		�ڶ���Ԫ���ҵ����ʵ�λ��֮����������ͽ�����
	*/
	//�ж�������Ԫ�ظ����Ƿ����1��û��Ԫ�ػ���0��Ԫ��ʱ����������
	int containerSize = mContainer.size();
	if(containerSize <= 1)
	{
		return;
	}
	//�ӵ�һ��λ�ÿ�ʼ�������ظ������㷨��ֱ�������ڶ���Ԫ��
	int loopSize = containerSize - 1;
	int minLoc = 0;
	for(int i = 0; i < loopSize; ++i)
	{
		//���������С����Ҫ�������һ��Ԫ�صģ����
		//���ı߽��������Ĵ�С
		//���ڵ�һ��ʵ�ֵ�ʱ�򣬴���Ľ������������ΪloopSize���ǲ��Եġ�
		//��Ҫʵ���㷨�������ν��
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
����ӿڱ��뿼�ǵ������ͬһ�����������⣬�Լ����Լ�����ʱ�������0
��ˣ�����λ�����swap��ʵ�������Ƶģ���������ǻ��ڼӷ�,Ҳ��ͬ�������⡣
�ܶ����㣬��ʵ��Ҫ�����Լ����Լ��������������
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
	//�������ڲ����ã�����Ҫ������
	int min = mContainer[start];
	int minLoc = start;
	// ����Ϊ[start, end)
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


//main����
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
