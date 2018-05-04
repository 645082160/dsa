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
	//分支搜索，回溯，这种搜索方法时间复杂度是指数级的，n>10的时候，搜索
	//速度就已经无法接受了====>真的是这样的么?实际测试下。
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

class PackageDP
{
public:
	bool init();//初始化输入
	void dp();//执行DP，找到最大的背包价值
	void print();//打印最大价值
	void dp_memory_optimization();//优化cache存储的方式
	void dp_full();//完全背包问题
	void dp_full_print();//找到选择方案
	void dp_full_op();// 完全背包问题优化
	void dp_multi();//多重背包问题
private:
	int max(int p1, int p2);
private:
	int* m_w;//每个物品的重量数组
	int* m_v;//每个物品的价值数组
	int m_max_value;//最大价值
	int m_c;//背包的最大容量
	int m_n;//物品总个数
	int** m_cache;//记录中间结果的数组
	int* m_optimization;//内存优化后存储子问题的背包最优解
};

bool PackageDP::init()
{
	//输入背包最大容量
	cout << "input max package volumn:";
	cin >> m_c;
	if(m_c <= 0)
	{
		cout << "package volumn error." << endl;
		return false;
	}

	//输入物品个数
	cout << "input objects num:";
	cin >> m_n;
	if(m_n <= 0)
	{
		cout << "objects number error." << endl;
		return false;
	}

	m_w = new int[m_n]();
	//输入 每个物品的体积
	for(int i = 0; i < m_n; ++i)
	{
		cout << "input the " << i << " obj volumn:";
		cin >> m_w[i];
		if(m_w[i] <= 0)
		{
			cout << "obj volumn error." << endl;
			return false;
		}
	}
	
	m_v = new int[m_n]();
	//输入每个物品的价值
	for(int i = 0; i < m_n; ++i)
	{
		cout << "input the " << i << " obj value:";
		cin >> m_v[i];
		if(m_v[i] <= 0)
		{
			cout << "obj value error." << endl;
			return false;
		}
	}

	//初始化cache数组 ，注意，因为添加了为0的情况，因此，数组
	//记录的值的个数比物品个数和容量数量都大1个。
	//这里的下标与物品数组和价值数组之间的下标对应要注意。
	m_cache = new int* [m_n+1]();
	for(int i = 0; i <= m_n; ++i)
	{
		m_cache[i] = new int[m_c + 1];
	}

	//初始化优化内存存储
	m_optimization = new int[m_c + 1]();
	
	return true;
}

void PackageDP::dp()
{
	//初始化，物品个数为0时，最大价值为0
	for(int i = 0; i <= m_c; ++i)
	{
		m_cache[0][i] = 0;
	}

	//容量为0的背包，最大价值也是0
	for(int i = 0; i <= m_n; ++i)
	{
		m_cache[i][0] = 0;
	}

	/*
		对于物品规模为n，计算背包容量从1到m_c的最大价值
	*/
	for(int i = 1; i <= m_n; ++i)
	{
		for(int j = 1; j <= m_c; ++j)
		{
			 /*
			 	容量为j时，
			 	装不下第i个物品,则最大价值等于i-1个物
			 	品装入容量为j的背包时的最大价值
			 */
			if(j < m_w[i - 1])
			{
				m_cache[i][j] = m_cache[i-1][j];
			}
			else
			{
				/*
					背包容量为j的背包可以装下第i个物品，此时的计算法方式为:
						看不装第i个物品时前i-1个物品装进容量为j的背包得到的价值更大，
						还是装下第i个物品后，容量为j的背包得到的价值更大
				*/
				m_cache[i][j] = max(m_cache[i-1][j],  m_cache[i-1][j - m_w[i - 1]] + m_v[i - 1]);
			}
		}
	}
	return;
}

void PackageDP::print()
{
	cout << "max package value:" << m_cache[m_n][m_c] << endl;
	//打印 出选择的物品列表
	//根据DP的状态转移方程，逆向分析
	int value = m_cache[m_n][m_c];
	int i = m_n;//物品下标
	int j = m_c;//背包容量
	while(value > 0)
	{
		//判断是否选取了物品i
		if(m_cache[i][j] != m_cache[i-1][j]) //是否是不选择物品i得到的值
		{
			//不相等的情况下，确认是选择了物品i
			cout << "(" << i - 1 << ", " << m_w[i - 1] << ", " << m_v[i - 1] << ")" << endl;
			j = j - m_w[i - 1];
			--i;	
		}
		else
		{
			//相等的情况下，表示未选择物品i
			--i;
		}
		value  = m_cache[i][j]; //为下次计算做准备
	}
	cout << endl;
	return;
}

int PackageDP::max(int p1, int p2)
{
	return p1 > p2 ? p1 : p2;
}

void PackageDP::dp_memory_optimization()
{
	for(int i = 1; i <= m_n; ++i)
	{
		for(int j = m_c; j>= m_w[i - 1]; --j) //第一次实现的时候，考虑了条件j > m_w[i - 1],导致j=m_w[i - 1]没有被处理，结果错误
		{
			//当j小于第i 个物品时，背包最优解不变
			//当j大于第i个物品体积时，需要计算背包新的最优解
			//大的j值要先更新，小的j值后更新，这样才能保证正确性
			m_optimization[j] = max(m_optimization[j], m_optimization[j - m_w[i - 1]] + m_v[i - 1]);
		}
	}

	cout << "max price:" << m_optimization[m_c] << endl;
	return;
}

void PackageDP::dp_full()
{
	//初始化cache数组
	for(int i = 0; i <= m_n; ++i)
	{
		m_cache[i][0] = 0;
	}

	for(int i = 0; i <= m_c; ++i)
	{
		m_cache[0][i] = 0;
	}

	//执行DP
	int cnt = 0;
	int tmp_cnt = 0;
	int curr_max = 0;
	int tmp_value = 0;
	for(int i = 1; i <= m_n; ++i)
	{
		for(int j = 1; j <= m_c; ++j)
		{
			//连续放物品i，计算背包的最优值
			cnt = j /m_w[i - 1]; //这里兼容了j < m_w[i - 1]这种情形
			for(int k = 0; k <= cnt; ++k) //这里的边界值很重要，需要测试等于的情况，k=0时表示不放
			{
				tmp_value = m_cache[i - 1][j - k * m_w[i - 1]] + k * m_v[i - 1];
				curr_max = max(curr_max, tmp_value);
			}
			
			m_cache[i][j] = curr_max;
			tmp_value = 0;
			curr_max = 0;
		}
	}

	cout << "max value:" << m_cache[m_n][m_c] << endl;
	return;
}



void PackageDP::dp_full_print()
{
	int i = m_n;
	int j = m_c;
	int price = m_cache[i][j];
	int cnt = 0;
	while(price > 0)
	{
		cnt = j / m_w[i - 1];
		for(int k = 0; k <= cnt; ++k)
		{
			if(price == m_cache[i - 1][j - k * m_w[i - 1]] + k * m_v[i - 1])
			{
				for(int m = 0; m < k; ++m)
				{
					cout << "(" << i - 1 << ", " << m_w[i - 1] << ", " << m_v[i - 1] << ")" << endl;
				}
				price = m_cache[i - 1][j - k * m_w[i - 1]];
				--i;
				j -= k * m_w[i - 1];
				break;
			}
		}
	}

	cout << endl;
	return;
}
void PackageDP::dp_full_op()
{
	int cnt = 0;
	int curr_max = 0;
	int tmp_value = 0;
	for(int i = 1; i <= m_n; ++i)
	{
		for(int j = m_c; j - m_w[i - 1] >= 0; --j)
		{
			/*
				关于临时变量的初始化，我觉得即使你在定义的时候初始化过，
				在进入代码逻辑之前还是要再初始化一下，不要觉得麻烦，不这样做
				的话，你可能面临在整个逻辑之后初始化这些变量的问题，你可能搞忘
			*/
			tmp_value = 0;
			curr_max = 0;
			cnt = j / m_w[i - 1];
			for(int k = 0; k <= cnt; ++k)
			{
				tmp_value = m_optimization[j - k * m_w[i -1]] + k * m_v[i - 1];
				curr_max = max(tmp_value, curr_max);
			}
			m_optimization[j] = curr_max;
		}
	}

	cout << "max value:" << m_optimization[m_c] << endl;
	
	return;
}
int main(int argc, char** argv)
{
/*
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
*/
	PackageDP dp;
	if(dp.init())
	{
		dp.dp();
		dp.print();
	}

	dp.dp_memory_optimization();

	cout << endl;
	dp.dp_full();
	dp.dp_full_print();

	cout << endl;
	dp.dp_full_op();
	return 0;
}
