#include <iostream>
#include <list>
using std::endl;
using std::cout;
using std::list;
using std::cin;

int max_value = 0;
list<int> storage;

int sum(list<int>& tmp_storage, int* values)
{
	int sum = 0;
	list<int>::iterator it = tmp_storage.begin();
	list<int>::iterator end = tmp_storage.end();
	while(it != end)
	{
		sum += values[*it];
		++it;
	}

	return sum;
}

void copyfrom(list<int>& now)
{
	storage.clear();
	list<int>::iterator it = now.begin();
	list<int>::iterator end = now.end();
	while(it != end)
	{
		storage.push_back(*it);
		++it;
	}
	
	return;
}

void print()
{
	cout << "max_value:" << max_value << endl;
	cout << "objs:";
	
	list<int>::iterator it = storage.begin();
	list<int>::iterator end = storage.end();
	while(it != end)
	{
		cout << *it << " ";
		++it;
	}

	cout << endl;
	
	return;
}

void find(int pos,  int n, int* weights, int* values, list<int>& tmp_storage, int max_weight, int curr_weight)
{
	//递归出口
	if(pos >= n)
	{
		int total = sum(tmp_storage, values);
		if(max_value < total )
		{
			max_value = total;
			copyfrom(tmp_storage);
		}

		return;
	}

	
	if(curr_weight + weights[pos] <= max_weight)
	{
		tmp_storage.push_back(pos);
		curr_weight += weights[pos];
		find(pos + 1, n, weights, values, tmp_storage, max_weight, curr_weight);
		//回溯
		curr_weight -= weights[pos];
		tmp_storage.pop_back();
	}
	
	find(pos + 1, n, weights, values, tmp_storage, max_weight, curr_weight);

	return;
}

//对比下基于类的实现
class PackageBackTrack
{
private:
	int m_max_value;
	list<int> m_storage;
	list<int> m_curr_storage;
	int* m_weights;
	int* m_values;
	int m_obj_num;
	int m_current_weight;
	int m_max_weight;

public:
	void init();
	void find(int pos);
	void print();
	int sum();
	void copy_from();
};

void PackageBackTrack::init()
{
	m_max_value = 0;
	m_max_weight = 0;
	m_current_weight = 0;
	
	m_storage.clear();
	m_curr_storage.clear();

	cout << "input obj num:";
	cin >> m_obj_num;

	m_weights = new int[m_obj_num];
	m_values = new int[m_obj_num];

	cout << "input weight of objs:";
	for(int i = 0; i < m_obj_num; ++i)
	{
		cin >> m_weights[i];
	}

	cout << "input value of objs:";
	for(int i = 0; i < m_obj_num; ++i)
	{
		cin >> m_values[i];
	}

	cout << "input weight of package:";
	cin >> m_max_weight;

	return;
}

void PackageBackTrack::find(int pos)
{
	//递归出口
	if(pos >= m_obj_num)
	{
		int total = sum();
		if(total >= m_max_value)
		{
			m_max_value = total;
			copy_from();
		}

		return;
	}
	//搜索+回溯
	//分支搜索，回溯
	/*
		2分法，一个物品放还是不放
		这里只有限制条件，没有限界条件，01背包问题想要快速解决，则需要有
		限界条件，我这里实现的是最原始的回溯法。
		讲真话，你在编写这段代码的时候，被求子集的算法给糊弄住了。导致
		代码编写出来非常丑。
	*/
	if(m_current_weight + m_weights[pos] <= m_max_weight)
	{
		m_current_weight += m_weights[pos];
		m_curr_storage.push_back(pos);
		find(pos + 1);
		m_current_weight -= m_weights[pos];
		m_curr_storage.pop_back();
	}

	find(pos + 1);

	return;
}

void PackageBackTrack::print()
{
	cout << "max value:" << m_max_value << endl;
	cout << "objs in package:";
	list<int>::iterator it = m_storage.begin();
	list<int>::iterator end = m_storage.end();
	while(it != end)
	{
		cout << *it << " ";
		++it;
	}

	cout << endl;

	return;
}

int PackageBackTrack::sum()
{
	int sum = 0;
	list<int>::iterator it = m_curr_storage.begin();
	list<int>::iterator end = m_curr_storage.end();
	while(it != end)
	{
		sum += m_values[*it];
		++it;
	}
	
	return sum;
}

void PackageBackTrack::copy_from()
{
	m_storage.clear();
	list<int>::iterator it = m_curr_storage.begin();
	list<int>::iterator end = m_curr_storage.end();
	while(it != end)
	{
		m_storage.push_back(*it);
		++it;
	}
	return;
}
int main(int argc, char** argv)
{
	int n = 0;
	int* weights = NULL;
	int* values = NULL;
	//weight
	cout << "input obj num:";
	cin >> n;

	weights = new int[n];
	values = new int[n];

	cout << "input weight of objs:";
	for(int i = 0; i < n; ++i)
	{
		cin >> weights[i];
	}

	cout << "input values of objs:";
	for(int i = 0; i < n; ++i)
	{
		cin >> values[i];
	}
	
	int max_weight = 10;
	cout << "input max weight of storage:";
	cin >> max_weight;

	
	int curr_weight = 0;

	//找到符合条件的物品组合
	list<int> tmp_storage;//背包，记录存放的物品序列
	find(0, n, weights, values, tmp_storage, max_weight, curr_weight);

	print();


	//基于类的实现
	PackageBackTrack p;
	p.init();
	p.find(0);
	p.print();
	
	return 0;
}
