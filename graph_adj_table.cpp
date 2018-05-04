#include <iostream>
using namespace std;


const int MAX_VEX_NUM = 20;

struct Node
{
	int vex;
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
		cout << "input start and end vertex of edge:";
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

		m_vex[s].first = tmp;

		tmp = new Node();
		tmp->vex = s;
		tmp->next = m_vex[e].first;

		m_vex[e].first = tmp;
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
			cout << locate_vex(p->vex) << " ";
			p = p->next;
		}
		cout << endl;
	}

	return;
}


class CutPoint
{
public:
	bool init();
	void find(GraphAdjTable& g);
	void dfs(GraphAdjTable& g, int vex);
private:
	int m_visited[MAX_VEX_NUM];
	int m_low[MAX_VEX_NUM];
	int m_count;
	
};

bool CutPoint::init()
{
	m_count = 0;
	for(int i = 0; i < MAX_VEX_NUM; ++i)
	{
		m_visited[i] = 0;
		m_low[i] = 0;
	}
	
	return true;
}

void CutPoint::find(GraphAdjTable& g)
{
	//0号顶点为root，开始DFS遍历
	Node* p = g.get_vex(0)->first;
	int i = p->vex;
	m_count = 1;
	m_visited[0] = 1;
	
	dfs(g, i);

	//不止1棵子树
	if(m_count < g.get_vex_num())
	{
		//root为割点
		cout << g.get_vex(0)->vex << endl;

		//访问其他邻接点，寻找割点
		p = p->next;
		while(p)
		{
			i = p->vex;
			if(m_visited[i] == 0) //顶点未被访问过
			{
				dfs(g, i);
			}
			p = p->next;
		}
	}
	return;
}

void CutPoint::dfs(GraphAdjTable& g, int vex)
{
	//设置顶点先序dfs访问序号
	m_visited[vex] = ++m_count;
	int min = m_visited[vex];
	//遍历顶点的所有关联节点
	Node* p  = g.get_vex(vex)->first;
	int i = 0;
	while(p)
	{
		i = p->vex;
		//关联顶点已访问,必然是祖先节点
		if(m_visited[i] != 0)
		{
			if(m_visited[i] < min) //有回路，祖先节点的先序序号是否更小
			{
				min = m_visited[i];
			}
		}
		else
		{
			//关联节点未访问，dfs访问，获得其low值
			dfs(g, i);
			//关联节点返回后，重新计算当前顶点的low值
			//如果子孙节点有回路到当前顶点的祖先节点，更新low值
			if(m_low[i] < min)
			{
				min = m_low[i];
			}

			if(m_low[i] >= m_visited[vex]) //子树中所有顶点都没有回路到该顶点 的祖先节点，该顶点是割点
			{
				cout << g.get_vex(vex)->vex << endl;
			}
		}

		//访问下一个关联顶点
		p = p->next;
		
	}

	//找到顶点的low值
	m_low[vex] = min;
	return;
}
int main(int argc, char** argv)
{

	GraphAdjTable g;
	if(g.init())
	{
		if(g.create())
		{
			g.print();
		}
	}

	CutPoint c;
	if(c.init())
	{
		c.find(g);
	}
	return 0;
}
