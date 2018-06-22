/*
shell���򣬸��ݲ������飬�Ƚ�����ָ�Ϊ��ͬ�������飬������������
ʹ���������������ٶ�����������������������
��Ϊ����ֱ�Ӳ���������˵������������㷨ʱ�临�Ӷ���n
*/

#include <iostream>
#include <vector>
using namespace std;


const unsigned int SIZE = 10;//Ԫ�ظ�������������ĳ���
class Sort
{
public:
	virtual bool init() = 0;//��ʼ������������
	virtual void sort() = 0;//ʵ�������㷨
	virtual void print() = 0;//��ӡ������
};

class ShellSort : public Sort
{
public:
	bool init();
	void sort();
	void shellInsert(int step);
	void print();
private:
	vector<int> mDeltaArray;//��������,delta��ʾ��ѧ�е�����
	vector<int> mContainer;//��������	
};

bool  ShellSort::init()
{
	//��ʼ����������
	mDeltaArray.push_back(5);
	mDeltaArray.push_back(2);
	mDeltaArray.push_back(1);//���һ������������1
	//��ʼ������������
	mContainer.push_back(0);//��һ��Ԫ�����ڱ�
	cout << "input elements:" << endl;

	//����Ԫ��
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
	//�����������飬ÿ�������õ�һ�������飬������ֱ�Ӳ�������
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
	�ұ�д��δ����ʱ����ֱ�ӱ�д�ģ�������ʵ����Ĳ���
	�۲����ϵĴ��룬�ҷ��֣�����δ�������һ��������������ߣ�
	Ҳ���Ӽ�࣬�ӹ����Ͽ���Ҳȷʵÿ��������������ʵ��һ���ھ۶�
	�ܸߵĲ������ϣ�Ӧ�ñ��ŵ�һ�������С�
	��������˳��ı�д���룬��ʵ��д�������ʶ���ã�������ʶ����
	�ı��֡�
	*/
	for(unsigned int k = 0; k < deltaArraySize; ++k)
	{
		shellInsert(mDeltaArray[k]);
	}
	
	return;
}


void ShellSort::shellInsert(int dk)
{
	//��ÿ��������������������ֱ�Ӳ�������
	//��ʵ������Կ��������ʻ�������ֱ�Ӳ�������
	 //ͨ��������������������������������������������
	 //���������Ч��
	 //0��Ԫ�������ݴ�Ԫ��
	unsigned int containerSize = mContainer.size() - 1;
	//��һ�α�д��ʱ����д����unsigned int,������Խ�磬j�����һ���ǳ������
	//j�ǿ���Ϊ���ģ���˲�����unsigned int 
	int j = 0;
	for(int i = dk + 1; i <= containerSize; ++i)
	{
		//��Ԫ�ط��뵽0��Ԫ���ݴ�
		mContainer[0] = mContainer[i];
		//��ÿһ��������Ԫ�أ���ֱ�Ӳ�������
		for(j = i - dk; j > 0 && mContainer[j] > mContainer[0]; j -= dk)
		{
			//�����ٴγ���ԭ����ֵ����mContainer[0]
			//��û�㶮Ϊʲô�һ���ôд�������������������
			//�����ҷ����ֵͼ��������?
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
	//�ڱ������
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