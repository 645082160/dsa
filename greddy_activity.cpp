#include <iostream>
#include <vector>
#include <algorithm>

using std::endl;
using std::cout;
using std::cin;
using std::vector;
using std::sort;
struct node{
		int start; //���ʼʱ��
		int end;//�����ʱ��
	};
bool my_comp(node left, node right)
{
	return left.end < right.end;
}
class Activity
{
public:
	
	bool init();//��ʼ��
	int select();//ѡ�������������Ļ��Ŀ
private:
	vector<node> m_activitys;//�
	int m_n;//�����
};

bool Activity::init()
{
	cout << "input activity num:";
	cin >> m_n;

	if(m_n <= 0)
	{
		cout << "invalid activity num." << endl;
		return false;
	}

	node tmp_activity;
	for(int i = 0; i < m_n; ++i)
	{
		cout << "activity " << i << " start and end:";
		cin >> tmp_activity.start;
		cin >> tmp_activity.end;
		if(tmp_activity.start < 0 
			|| tmp_activity.end < 0 
			|| tmp_activity.start > tmp_activity.end 
			|| tmp_activity.end <= 0)
		{
			cout << "activity start or end error." << endl;
			return false;
		}

		m_activitys.push_back(tmp_activity);
	}

	sort(m_activitys.begin(), m_activitys.end(), my_comp);
	
	return true;
}

int Activity::select()
{
	
	int sum = 1; //���������һ���Ĭ��ѡ��
	int curr = 0;//�Ǽ�������ָʾ��ǰ����ѡ��Ļ
	cout << "select activity: [" << m_activitys[curr].start << ", " << m_activitys[curr].end << ")" << endl;
	for(int i = curr + 1; i < m_n; ++i)
	{
		if(m_activitys[i].start > m_activitys[curr].end)
		{
			++sum;
			curr = i;
			cout << "select activity: [" << m_activitys[i].start << ", " << m_activitys[i].end << ")" << endl;
		}
	}

	return sum;
}

int main(int argc, char** argv)
{
	Activity a;
	if(a.init())
	{
		cout << a.select() << endl; 
	}
	else
	{
		cout << "init fail." << endl;
	}
	
	return 0;
}

