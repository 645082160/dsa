#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::cin;
using std::vector;

const int ARRAY_SIZE = 10;

class BinarySearch
{
public:
	bool init();
	void search();
	
private:
	int m_a[ARRAY_SIZE];
	int m_low;
	int m_high;
	int m_key;
};

bool BinarySearch::init()
{
	for(int i = 0; i < ARRAY_SIZE; ++i)
	{
		m_a[i] = i * 2;
		cout << m_a[i] << " ";
	}
	cout << endl;
	cout << "input key:";
	cin >> m_key;
	m_low = 0;
	m_high = ARRAY_SIZE;
	
	return true;
}

/*
在编写这段代码的时候，仍然出了一个问题，找到元素后没有break跳出循环，为什么会犯
这种低级错误呢?
除2可以使用位运算代替。
*/
void BinarySearch::search()
{
	int mid = 0;
	while(m_low < m_high)
	{
		mid = (m_low + m_high) >> 1;
		if(m_a[mid] != m_key)
		{
			/*
			if(m_a[mid] < m_key)
			{
				m_low = mid + 1;
			}
			else
			{
				m_high = mid;
			}
			*/
			//比较这2种不同的写法，第一种和第二种其实没啥区别
			//为什么觉得第二种会更难呢，其实都是认知的差异
			//你对三目表达式认识不够，害怕出错才认为第一种更简单
			//你对自己学的东西不自信，你不能独立思考。
			m_a[mid] < m_key ? m_low = mid + 1 : m_high = mid;
		}
		else
		{
			cout << "find, pos:" << mid << endl;
			return;
		}
	}
	
	cout << "no find." << endl;
	
	return;
}


class FbSearch
{
public:
	bool init();
	void search();

private:
	void make_fb();
private:
	int m_a[ARRAY_SIZE];
	int m_fb[ARRAY_SIZE];
	int m_low;
	int m_high;
	int m_key;
	vector<int> m_tmp;
	int m_k;
};

bool FbSearch::init()
{
	for(int i = 0; i < ARRAY_SIZE; ++i)
	{
		m_a[i] = i * 2;
		cout << m_a[i] << " ";
	}
	cout << endl;
	//创建fb数组
	make_fb();

	//挑选fb值
	for(m_k = 0; m_k < ARRAY_SIZE; ++m_k)
	{
		if(ARRAY_SIZE < m_fb[m_k]) //这里很重要，要找到一个比当前数组大的fb值
		{
			break;
		}
	}
	
	//扩充数组
	for(int i = 0; i < ARRAY_SIZE; ++i)
	{
		m_tmp.push_back(m_a[i]);
	}
	for(int i = ARRAY_SIZE; i < m_fb[m_k]; ++i)
	{
		m_tmp.push_back(m_a[ARRAY_SIZE - 1]);
	}
	vector<int>::iterator it = m_tmp.begin();
	vector<int>::iterator end = m_tmp.end();
	while(it != end)
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	//设置low和high
	m_low = 0;
	m_high = ARRAY_SIZE; //这里不是等于扩充后的数组长度，而是等于原数组的长度

	cout << "input key:";
	cin >> m_key;
	
	return true;
}

void FbSearch::search()
{
	int mid = 0;
	while(m_low < m_high)
	{
		mid = m_low + m_fb[m_k - 1] - 1; //保证是第m_fb[m_k - 1]  位置的元素作为中间点
		if(m_tmp[mid] != m_key)
		{
			if(m_tmp[mid] < m_key)
			{
				m_low = mid + 1;
				m_k -= 2;
			}
			else
			{
				m_high = mid; //最高位置是无效的，offset by one规则
				--m_k;
			}
		}
		else
		{
			cout << "find, pos:";
			if(mid >= ARRAY_SIZE)
			{
				cout <<  ARRAY_SIZE - 1 << endl;
			}
			else
			{
				cout << mid << endl;
			}
			return ;
		}
	}
	cout << "no find." << endl;
	return;
}

void FbSearch::make_fb()
{
	m_fb[0] = 1;
	m_fb[1] = 1;
	for(int i = 2; i <  ARRAY_SIZE; ++i)
	{
		m_fb[i] = m_fb[i - 1] + m_fb[i - 2];
	}
	for(int i = 0; i < ARRAY_SIZE; ++i)
	{
		cout << m_fb[i] << " ";
	}
	cout << endl;
	return;
}



int main(int argc, char** argv)
{
	BinarySearch bs;
	if(bs.init())
	{
		bs.search();
	}
	else
	{
		cout << "init fail." << endl;
	}

	FbSearch fb;
	if(fb.init())
	{
		fb.search();
	}
	return 0;
}
