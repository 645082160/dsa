/*
问题描述:
01背包问题
n=3，w={20,15,15}, p={40,25, 25}, c = 30 n表示物品个数，w表示每个物品重量
p表示每个物品价值，c表示背包最大可装入物品总重量
求可以装入的组合及价值
使用分支定界 FIFO扩展点选取方法
*/
#include <iostream>
#include <queue>
#include <vector>
#include <list>
using std::cout;
using std::endl;
using std::cin;
using std::priority_queue;
using std::vector;
using std::list;

class PackageBranchAndBound
{
public:
	struct node
	{
		int step;
		int total_w;
		int total_p;
		list<int> container;//装的物品的序号
	};
	bool init();//输入数据
	void find_fifo();//分支定界主体
	void find_priorityq();//优先队列分支扩展方式，price最大策略
private:
	void print(node& res);//打印结果
	struct local_compare{
		bool operator()(node& left, node& right)
		{
			return left.total_p < right.total_p;
		}
	};
private:	
	int m_n;//总物品个数
	int* m_w;//重量数组
	int* m_p;//价值数组
	int m_c;//背包最大容量
};


bool PackageBranchAndBound::init()
{
	cout << "input obj num:";
	cin >> m_n;
	cout << "input package volumn:";
	cin >> m_c;

	cout << "input weight of objs:";
	m_w = new int[m_n];
	for(int i = 0; i < m_n; ++i)
	{
		cin >> m_w[i];
	}

	cout << "input price of objs:";
	m_p = new int[m_n];
	for(int i = 0; i < m_n; ++i)
	{
		cin >> m_p[i];
	}

	return true;
}

void PackageBranchAndBound::find_fifo()
{
	//FIFO 扩展节点选择方式
	list<node> nodeset;
	//针对第一个节点，计算其所有分支，并根据条件判断是否要存入list中
	node node1;
	//放入第一个物品
	if(m_c >= m_w[0])
	{
		node1.step = 0;
		node1.total_w = m_w[0];
		node1.total_p = m_p[0]; 
		node1.container.push_back(0);
		nodeset.push_back(node1);
	}

	//不放第一个物品
	node1.step = 0;
	node1.total_w = 0;
	node1.total_p = 0; 
	node1.container.clear();
	nodeset.push_back(node1);

	//循环遍历，直到活动节点集合为空
	node e_node;
	node tmp_node;
	int tmp_step = 0;
	while(!nodeset.empty())
	{
		//FIFO规则，获得扩展节点
		e_node = nodeset.front();
		nodeset.pop_front();
		tmp_step = e_node.step + 1;
		//判断当前节点是否已经是结果
		if(tmp_step >= m_n)
		{
			if(e_node.total_p != 0)
			{
				cout << "find res:" << endl;
				print(e_node);
			}
			
			continue;
		}
		//选择当前节点为扩展节点，计算其分支节点，
		//并将分支节点加入到活动节点集中
		//装进背包中
		if(m_c >= e_node.total_w + m_w[tmp_step])
		{
			tmp_node.step = tmp_step;
			tmp_node.total_w = e_node.total_w + m_w[tmp_step];
			tmp_node.total_p = e_node.total_p + m_p[tmp_step];
			tmp_node.container = e_node.container;
			tmp_node.container.push_back(tmp_step);

			nodeset.push_back(tmp_node);
		}

		//不选择分支加入进列表中
		++e_node.step;
		nodeset.push_back(e_node);
	}
	
	return;
}


void PackageBranchAndBound::find_priorityq()
{
	priority_queue<node, vector<node>, local_compare> nodeset; //优先级队列，price按照升序排列，top取最后一个
	//初始化，从根节点开始将分支加入到优先队列中
	node tmp_node;
	int tmp_step = 0;

	//放入第一个物品
	if(m_c >= m_w[tmp_step])
	{
		tmp_node.step = tmp_step;
		tmp_node.total_w = m_w[tmp_step];
		tmp_node.total_p = m_p[tmp_step];
		tmp_node.container.push_back(tmp_step);

		nodeset.push(tmp_node);
	}

	//不放第一个物品
	tmp_node.step = tmp_step;
	tmp_node.total_w = 0;
	tmp_node.total_p = 0;
	tmp_node.container.clear();
	nodeset.push(tmp_node);

	//当优先队列不空时，继续出队，直到找到第一个结果，打印结果退出
	node e_node;
	while(!nodeset.empty())
	{
		//获得优先级最大的元素，出队列，并作为扩展节点
		e_node = nodeset.top();
		nodeset.pop();
		cout << "pop :(" << e_node.total_p << ", " << e_node.total_w << ", " << e_node.step << endl;
		tmp_step = e_node.step + 1;
		if(tmp_step >= m_n)
		{
			cout << "meet leaf:(" << e_node.total_p << ", " << e_node.total_w << ",";
			list<int>::iterator it = e_node.container.begin();
			list<int>::iterator end = e_node.container.end();
			while(it != end)
			{
				cout << *it << " ";
				++it;
			}
			cout << ")" << endl;
			
			/*
			if(e_node.total_p > 0)
			{
				print(e_node);
			}
			*/
			continue;
		}
		
		//计算分支
		if(m_c >= e_node.total_w + m_w[tmp_step])
		{
			tmp_node.step = tmp_step;
			tmp_node.total_p = e_node.total_p + m_p[tmp_step];
			tmp_node.total_w = e_node.total_w + m_w[tmp_step];
			
			tmp_node.container.clear();
			tmp_node.container = e_node.container;
			tmp_node.container.push_back(tmp_step);
			
			nodeset.push(tmp_node);
		}

		//计算出不放入的物品的情况 
		++e_node.step;
		nodeset.push(e_node);
	}
	
}
void PackageBranchAndBound::print(node& res)
{
	cout << "total weight:" << res.total_w << endl;
	cout << "total price:" << res.total_p << endl;
	cout << "obj list:";
	list<int>::iterator it = res.container.begin();
	list<int>::iterator end = res.container.end();
	while(it != end)
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	return;
}


int main(int argc, char** argv)
{

	PackageBranchAndBound p;
	
	p.init();
	p.find_fifo();


	cout << endl;
	p.find_priorityq();
	
	return 0;
}

