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
�ڱ�д��δ����ʱ����Ȼ����һ�����⣬�ҵ�Ԫ�غ�û��break����ѭ����Ϊʲô�᷸
���ֵͼ�������?
��2����ʹ��λ������档
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
			//�Ƚ���2�ֲ�ͬ��д������һ�ֺ͵ڶ�����ʵûɶ����
			//Ϊʲô���õڶ��ֻ�����أ���ʵ������֪�Ĳ���
			//�����Ŀ���ʽ��ʶ���������³������Ϊ��һ�ָ���
			//����Լ�ѧ�Ķ��������ţ��㲻�ܶ���˼����
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
	//����fb����
	make_fb();

	//��ѡfbֵ
	for(m_k = 0; m_k < ARRAY_SIZE; ++m_k)
	{
		if(ARRAY_SIZE < m_fb[m_k]) //�������Ҫ��Ҫ�ҵ�һ���ȵ�ǰ������fbֵ
		{
			break;
		}
	}
	
	//��������
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
	//����low��high
	m_low = 0;
	m_high = ARRAY_SIZE; //���ﲻ�ǵ������������鳤�ȣ����ǵ���ԭ����ĳ���

	cout << "input key:";
	cin >> m_key;
	
	return true;
}

void FbSearch::search()
{
	int mid = 0;
	while(m_low < m_high)
	{
		mid = m_low + m_fb[m_k - 1] - 1; //��֤�ǵ�m_fb[m_k - 1]  λ�õ�Ԫ����Ϊ�м��
		if(m_tmp[mid] != m_key)
		{
			if(m_tmp[mid] < m_key)
			{
				m_low = mid + 1;
				m_k -= 2;
			}
			else
			{
				m_high = mid; //���λ������Ч�ģ�offset by one����
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
