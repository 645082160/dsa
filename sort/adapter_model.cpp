#include <iostream>
#include <vector>
using namespace std;


class SortAlgorithm
{
public:
	/*
		�����ҵ�һ��д��ʱ��������⣬������virtual�ؼ���
		���ԣ����麯��������һ���麯��
	*/
	virtual void sort(vector<int>& container) = 0; 
	/*
		��Ϊ����Ϊһ�����࣬���������˶�̨����˽�������������Ϊ��virtual��
		���ǣ��Ҿ�Ȼ���Ǹ���ʵ���ˡ�
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
		����ط����ҷ���һ������delete��һ�������������ͣ������ǻ����δ
		�������Ϊ�ģ���ˣ��Ҿ��������ʵ�ֳ�������ͣ���ô�ȸ���������͵Ķ���
		�ѿ��д�꣬Ȼ���ټ̳������������ʵ����Ӧ�Ĺ��ܼ��ɡ�
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
	vector<int> mContainer; //��һ��λ��Ϊ�ڱ�
};

bool Sort::init()
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
	//ʵ�ʴ���������鳤����Ҫ��ȥ�ڱ�Ԫ��
	int size = container.size() - 1;
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
		container[0] = container[i];
		//����ж������Ԫ���Ƿ����ڱ�Ԫ������
		//��������򽫵�ǰԪ�غ���һ��λ��
		 //�ȶ����㷨��ǰ���Ԫ�ش��ں����Ԫ�أ��Żᵼ�½���λ��
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