#include <iostream>
#include <list>
using std::endl;
using std::cout;
using std::cin;
using std::list;

bool res = false; 
void check(int* c, int* w, int c_num, int n, int step)
{
	//�������
	//�ݹ����
	if(step >= n)
	{
		res = true;
		return;
	}
	
	//��֧����, �򵥵�˵:
	//��װ������ظ���������һ����ֻ�л���װ���µ�ʱ��ż������£�������ֹ
	//��ô��װ�����һ����װ�䣬˵�����ֿ���װ�����м�װ��
	for(int i = 0; i < c_num; ++i)
	{
		if(c[i] >= w[step]) //��֦����
		{
			c[i] -= w[step];
			check(c, w, c_num, n, step + 1);
			c[i] += w[step];
		}
	}

	//����

	return;
}
//ʹ�÷�֧�޽編��⣬��ʹ���Ż��ļ�֦����
/*
1 �ҵ���һ������������װ�ļ�װ��
2 ����ʣ�µļ�װ��ڶ��������Ƿ����װ��
����ʣ�༯װ��������˵��:
ÿ�ν����µ�һ���ʱ�򣬾ͼ�ȥ��ǰ��ļ�װ�䣬
Ȼ�����ew + r �����������ҷ�֧�������ܵ����������������������֧��
�õ�bestw����˵�����ҷ�֧�п��ܴ������Ľ⣬���򲻴��ڣ�����ֱ�Ӽ�֦
*/
class NLoad
{
public:
	bool init();
	void find();
	void check();
private:
	int m_r;//ʣ�µļ�װ������
	int m_c[2]; // 2�Ҵ�������
	int m_n;//��Ʒ����
	int* m_w; //��Ʒ����
	int m_bestw;//��ǰ�������
	list<int> m_q; //�����չ��Ķ���
};

bool NLoad::init()
{
	cout << "input c1 and c2";
	cin >> m_c[0];
	cin >> m_c[1];
	if(m_c[0] <= 0 || m_c[1] <= 0)
	{
		cout << "c1 and c2 error." << endl;
		return false;
	}

	cout << "input objs num:";
	cin >> m_n;
	if(m_n <= 0)
	{
		cout << "objs num error." << endl;
		return false;
	}
	cout << "input weight of objs:";
	m_r = 0;
	m_w = new int[m_n];
	for(int i = 0; i < m_n; ++i)
	{
		cin >> m_w[i];
		if(m_w[i] <= 0)
		{
			cout << "obj weight error." << endl;
			return false;
		}
		m_r += m_w[i];
	}

	m_bestw = 0;
	m_q.clear();
	
	return true;
}

//-1��ʾ��ǰ�����
void NLoad::find()
{
	int level = 0; //�������ӵ�0�㿪ʼ
	int ew = 0; //��ǰ��չ��������������ǰ��������ѡ���������ܺ�
	int tmp_w = 0;
	
	m_r -= m_w[level]; //ȥ����һ����Ʒ������
	
	//��ʼ��m_q
	m_q.push_back(-1);//-1��ʾ��ǰ�����
	while(true)
	{
		tmp_w = ew + m_w[level];
		if(m_c[0] >= tmp_w)
		{
			if(tmp_w > m_bestw)
			{
				m_bestw = tmp_w;
			}
			m_q.push_back(tmp_w);
		}

		//����ҷ�֧�Ƿ���ڸ��ŵ�ֵ
		if(m_r + ew > m_bestw)
		{
			m_q.push_back(ew);
		}

		//Ϊ��һ�ֲ�������ʼ��
		ew = m_q.front();
		m_q.pop_front();
		if(ew == -1) //��һ���Ѿ��������
		{
			//���Ӳ���
			++level;
			if(level >= m_n) //�����������ƣ���ʾ�������
			{
				break;
			}
			
			m_q.push_back(-1);//��ӱ�������������ڵ�һ��ʵ�ֵ�ʱ�������ˣ�����������ѭ��
			
			//ȡ����ͷ���Ľڵ���Ϊ��չ�ڵ�
			ew = m_q.front();
			m_q.pop_front();

			//����ʣ�༯װ����������ÿһ�㿪ʼ��ʱ�����������
			m_r -= m_w[level];
		}
	}
	return;
}

void NLoad::check()
{
	int total_w = 0;
	for(int i = 0; i < m_n; ++i)
	{
		total_w += m_w[i];
	}

	//����ʣ��ļ�װ�������Ƿ����ȫ��װ���ڶ���������
	if(total_w - m_bestw <= m_c[1])
	{
		cout << "OK" << endl;
		cout << "bestw:" << m_bestw << endl;
	}
	else
	{
		cout << "FAIL" << endl;
	}
	return;
}

int main(int argc, char** argv)
{
	//����2�����������ͼ�װ�����
	int c[2] = {0};
	int n = 0;
	cout << "c1, c2, n";
	cin >> c[0] >> c[1] >> n;
	cout << "input every box weight:";

	int* w = new int[n];
	for(int i = 0; i < n; ++i)
	{
		cin >> w[i];
	}

	//����Ƿ���Խ���װ��ת��2������
	check(c, w, 2, n, 0);

	if(res)
	{
		cout << "Yes";
	}
	else
	{
		cout << "No";
	}
	cout << endl;

	NLoad nl;
	if(nl.init())
	{
		nl.find();
		nl.check();
	}
	
	return 0;
}
