#include <iostream>
#include <list>
using std::endl;
using std::cout;
using std::cin;
using std::list;

bool res = false; 
void check(int* c, int* w, int c_num, int n, int step)
{
	//参数检查
	//递归出口
	if(step >= n)
	{
		res = true;
		return;
	}
	
	//分支回溯, 简单的说:
	//集装箱的总重跟货轮总重一样，只有货轮装的下的时候才继续往下，否则终止
	//那么当装完最后一个集装箱，说明货轮可以装下所有集装箱
	for(int i = 0; i < c_num; ++i)
	{
		if(c[i] >= w[step]) //剪枝操作
		{
			c[i] -= w[step];
			check(c, w, c_num, n, step + 1);
			c[i] += w[step];
		}
	}

	//返回

	return;
}
//使用分支限界法求解，并使用优化的剪枝方法
/*
1 找到第一个货轮最多可以装的集装箱
2 计算剩下的集装箱第二个货轮是否可以装上
关于剩余集装箱重量的说明:
每次进入新的一层的时候，就减去当前层的集装箱，
然后计算ew + r 的重量，即右分支的最大可能的重量，如果这个重量比左分支求
得的bestw还大，说明在右分支中可能存在最大的解，否则不存在，可以直接剪枝
*/
class NLoad
{
public:
	bool init();
	void find();
	void check();
private:
	int m_r;//剩下的集装箱重量
	int m_c[2]; // 2艘船的重量
	int m_n;//物品个数
	int* m_w; //物品重量
	int m_bestw;//当前最大重量
	list<int> m_q; //存放扩展点的队列
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

//-1表示当前层结束
void NLoad::find()
{
	int level = 0; //层数，从第0层开始
	int ew = 0; //当前扩展点重量，这里是前面所有已选择重量的总和
	int tmp_w = 0;
	
	m_r -= m_w[level]; //去掉第一个物品的重量
	
	//初始化m_q
	m_q.push_back(-1);//-1表示当前层结束
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

		//检查右分支是否存在更优的值
		if(m_r + ew > m_bestw)
		{
			m_q.push_back(ew);
		}

		//为下一轮操作做初始化
		ew = m_q.front();
		m_q.pop_front();
		if(ew == -1) //上一层已经遍历完毕
		{
			//增加层数
			++level;
			if(level >= m_n) //层数超过限制，表示搜索完毕
			{
				break;
			}
			
			m_q.push_back(-1);//添加本层结束，这里在第一次实现的时候，忘记了，导致了无限循环
			
			//取队列头部的节点作为扩展节点
			ew = m_q.front();
			m_q.pop_front();

			//计算剩余集装箱重量，在每一层开始的时候做这个操作
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

	//看下剩余的集装箱重量是否可以全部装到第二个货轮上
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
	//输入2个货轮重量和集装箱个数
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

	//检查是否可以将集装箱转入2个货轮
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
