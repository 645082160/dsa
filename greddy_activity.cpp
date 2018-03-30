#include <iostream>
#include <vector>
#include <algorithm>

using std::endl;
using std::cout;
using std::cin;
using std::vector;
using std::sort;
struct node{
		int start; //活动开始时间
		int end;//活动结束时间
	};
bool my_comp(node left, node right)
{
	return left.end < right.end;
}
class Activity
{
public:
	
	bool init();//初始化
	int select();//选择活动，并返回最多的活动数目
private:
	vector<node> m_activitys;//活动
	int m_n;//活动个数
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
	
	int sum = 1; //活动个数，第一个活动默认选择
	int curr = 0;//是计数器，指示当前最新选择的活动
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

