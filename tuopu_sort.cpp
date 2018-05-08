#include <iostream>
#include <stack>
#include <list>
using namespace std;


const int MAX_VEX_NUM = 20;

struct Node
{
	int vex;
	int weight;//AOE网，表示活动的持续时间，AOV网，设置为0
	Node* next;
};
struct Vertex
{
	string vex;
	Node* first;
};
class GraphAdjTable
{
public:
	bool init();//初始化
	bool create();//输入图信息
	int locate_vex(string& vex);
	string locate_vex(int i);
	void print();
	int get_vex_num()
	{
		return m_vex_num;
	}
	Vertex* get_vex(int i)
	{
		return &m_vex[i];
	}
private:
	int m_vex_num;
	int m_edge_num;
	Vertex m_vex[MAX_VEX_NUM];//顶点数组
};

bool GraphAdjTable::init()
{
	m_vex_num = 0;
	m_edge_num = 0;
	for(int i = 0; i < MAX_VEX_NUM; ++i)
	{
		m_vex[i].first = NULL;
	}
	
	return true;
}

bool GraphAdjTable::create()
{
	cout << "input vex num:";
	cin >> m_vex_num;
	if(m_vex_num <= 0)
	{
		cout << "vex num error." << endl;
		return false;
	}

	for(int i = 0; i < m_vex_num; ++i)
	{
		cout << "input " << i << " vertex:";
		cin >> m_vex[i].vex;
	}

	cout << "input edge num:";
	cin >> m_edge_num;
	if(m_edge_num <= 0)
	{
		cout << "edge num error." << endl;
		return false;
	}

	string start, end;
	int s = 0, e = 0;
	Node* tmp  = NULL;
	//输入边信息
	for(int i = 0; i < m_edge_num; ++i)
	{
		cout << "input start , end, weight  of edge:";
		cin >> start;
		cin >> end;

		s = locate_vex(start);
		if(s == -1)
		{
			cout << "edge start error." << endl;
			return false;
		}
		e = locate_vex(end);
		if(e == -1)
		{
			cout << "edge end error." << endl;
			return false;
		}

		tmp = new Node();
		tmp->vex = e;
		tmp->next = m_vex[s].first;
		cin >> tmp->weight;
		
		m_vex[s].first = tmp;

		/* 无向图才有这个对称的算法
		tmp = new Node();
		tmp->vex = s;
		tmp->next = m_vex[e].first;

		m_vex[e].first = tmp;
		*/
	}
	return true;
}


int GraphAdjTable::locate_vex(string& vex)
{
	for(int i = 0; i < m_vex_num; ++i)
	{
		if(m_vex[i].vex == vex)
		{
			return i;
		}
	}
	return  -1;
}

string GraphAdjTable::locate_vex(int i)
{
	return m_vex[i].vex;
}


void GraphAdjTable::print()
{
	Node* p = NULL;
	for(int i = 0; i < m_vex_num; ++i)
	{
		cout << "vex: " << m_vex[i].vex << "==>";
		p = m_vex[i].first;
		while(p)
		{
			cout << "(" << locate_vex(p->vex) << "," << p->weight << ")";
			p = p->next;
		}
		cout << endl;
	}

	return;
}

class TopoSort
{
public:
	bool init();
	void sort();
	void print();
private:
	GraphAdjTable m_g;
	stack<int> m_node;//入度为0的顶点
	int m_in[MAX_VEX_NUM];//记录每个顶点的度
	list<int> m_list;//记录拓扑排序序列
	int m_count;//判断是否有环
};

bool TopoSort::init()
{
	for(int i = 0; i < MAX_VEX_NUM; ++i)
	{
		m_in[i] = 0;
	}

	m_count = 0;

	if(m_g.init())
	{
		if(m_g.create())
		{
			//遍历所有顶点，更新顶点入度
			for(int i = 0; i < m_g.get_vex_num(); ++i)
			{
				Node* p = m_g.get_vex(i)->first;//拿到链表的头指针
				while(p)
				{
					//更新关联顶点的入度。
					++m_in[p->vex];
					p = p->next;
				}
			}

			//遍历入度数组，将入度为0的顶点加入到栈中
			for(int i = 0; i < m_g.get_vex_num(); ++i)
			{
				cout << "i:" << i << ", " << m_in[i] << endl;
				if(m_in[i] == 0)
				{
					m_node.push(i);
				}
			}
		}
	}
	
	return true;
}

void TopoSort::sort()
{
	//如果入度为0的顶点栈不空，栈顶出栈，加入到拓扑排序序列中
	//遍历其邻接顶点链表，减去入度，并将入度为0的顶点入栈
	Node* p = NULL;
	Vertex* v = NULL;
	int i = 0;
	while(!m_node.empty())
	{
		++m_count;
		i = m_node.top();
		m_node.pop();
		
		m_list.push_back(i);

		v = m_g.get_vex(i);
		p = v->first;
		while(p)
		{
			--m_in[p->vex];
			if(m_in[p->vex] == 0)
			{
				m_node.push(p->vex);
			}

			p = p->next;
		}
	}
	if(m_count < m_g.get_vex_num())
	{
		cout << "error, graph has circle." << endl;
	}
	else
	{
		cout << "topo list:";
		print();
	}
	return;
}

void TopoSort::print()
{
	list<int>::iterator it = m_list.begin();
	list<int>::iterator end = m_list.end();
	while(it != end)
	{
		cout << m_g.locate_vex(*it) << " ";
		++it;
	}
	cout << endl;
	return;
}

class CirticalPath
{
public:
	bool init();
	void find_path();
private:
	GraphAdjTable m_g;
	stack<int> m_node;//入度为0的顶点
	int m_in[MAX_VEX_NUM];//记录每个顶点的度
	list<int> m_list;//记录拓扑排序序列
	int m_count;//判断是否有环
	stack<int> m_topo_stack;//记录拓扑排序逆序，用于计算vl值
	int m_ve[MAX_VEX_NUM];//存储ve的值
	int m_vl[MAX_VEX_NUM];//存储vl的值
};

bool CirticalPath::init()
{
	//初始化ve和vl
	for(int i = 0; i < MAX_VEX_NUM; ++i)
	{
		m_ve[i] = 0;
		m_vl[i] = 0;
		m_in[i] = 0; //当时编码时，因为没有初始化导致错误
	}

	m_count = 0;

	//创建图
	if(m_g.init())
	{
		if(m_g.create())
		{
			Vertex* v = NULL;
			Node* p = NULL;
			for(int i = 0; i < m_g.get_vex_num(); ++i)
			{
				v = m_g.get_vex(i);
				p = v->first;
				while(p)
				{
					++m_in[p->vex];
					p = p->next;
				}
			}

			//将入度为0的顶点加入到栈中
			for(int i = 0; i < m_g.get_vex_num(); ++i)
			{
				if(m_in[i] == 0)
				{
					m_node.push(i);
				}
			}
		}
	}
	return true;
}

void CirticalPath::find_path()
{
	//栈不为空，从栈中取出栈顶顶点，入到vl计算栈，m_list中， 遍历其关联顶点
	//减小他们的入度, 计算ve值
	Vertex* v = NULL;
	Node* p = NULL;
	int i = 0;
	while(!m_node.empty())
	{
		++m_count;
		i = m_node.top();
		m_node.pop();

		m_list.push_back(i);
		m_topo_stack.push(i);

		v = m_g.get_vex(i);
		p = v->first;
		while(p)
		{
			//减少入度
			--m_in[p->vex];
			if(m_in[p->vex] == 0)
			{
				m_node.push(p->vex);
			}

			//计算ve值，初始ve值都为0，ve值去最大值
			if(p->weight + m_ve[i] > m_ve[p->vex])
			{
				m_ve[p->vex] = p->weight + m_ve[i];
			}

			//移动指针
			p = p->next;
		}
		
	}
	if(m_count < m_g.get_vex_num())
	{
		cout << "error, graph has circle." << endl;
		return;
	}
	//计算vl值
	//初始化所有的vl值为终结节点的ve值
	int last_vex = m_topo_stack.top();
	for(int i = 0; i < m_g.get_vex_num(); ++i)
	{
		m_vl[i] = m_ve[last_vex];
	}

	//依照topo序列的逆序，遍历每一个顶点的关联链表，计算vl值
	while(!m_topo_stack.empty())
	{
		i = m_topo_stack.top();
		v = m_g.get_vex(i);
		m_topo_stack.pop();
		p = v->first;
		while(p)
		{
			//这段代码是求解vl值的关键，可以结合图形来看。
			if(m_vl[p->vex] - p->weight < m_vl[i])
			{
				m_vl[i] = m_vl[p->vex] - p->weight;
			}
			//移动指针
			p = p->next;
		}
	}

	//判断关键路径，并打印
	int e = 0;
	int l = 0;
	for(int i = 0; i < m_g.get_vex_num(); ++i)
	{
		v = m_g.get_vex(i);
		p = v->first;
		e = m_ve[i];
		while(p)
		{
			//判断是否为关键路径
			l = m_vl[p->vex] - p->weight;
			if(e == l)
			{
				cout << "(" << m_g.locate_vex(i) << ", " << m_g.locate_vex(p->vex) << ", " << p->weight << ")" << endl;
			}
			//移动指针
			p = p->next;
		}
	}

	return;
}


int main(int argc, char** argv)
{
	CirticalPath cp;
	if(cp.init())
	{
		cp.find_path();
	}
	return 0;
}

