#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::cin;
using std::string;
/*
1、使用邻接矩阵表示图；
2、使用dijstra算法求得从某个源点开始的，到图中其余顶点 的最短路径；
*/
const int MAX_PATH_LEN = 10000;//最短路径长度
const int MAX_WEIGHT = 1000;//表示顶点之间无连接，边无穷大
const int MAX_VEC_NUM = 100;

class Graph
{
private:
	int m_vexnum;
	int m_edgenum;
	string m_vex[MAX_VEC_NUM];
	int m_edge[MAX_VEC_NUM][MAX_VEC_NUM];
	
public:
	int getEdge(int x, int y);
	int getVexnum();
	void init();//初始化
	bool create();//输入图
	void print();//输出图
	string findVexname(int index);
	int locate(string& vexname); //输出顶点在数组中的位置
	
};

int Graph::getEdge(int x, int y)
{
	return m_edge[x][y];
}

int Graph::getVexnum()
{
	return m_vexnum;
}

void Graph::init()
{
	m_vexnum = 0;
	m_edgenum = 0;
	for(int i = 0; i < MAX_VEC_NUM; ++i)
	{
		for(int j = 0; j < MAX_VEC_NUM; ++j)
		{
			m_edge[i][j] = MAX_WEIGHT;
		}
	}

	return;
}

bool Graph::create()
{
	init();
	//输入顶点数和边数
	while(true)
	{
		cout << "input vertex num:";
		cin >> m_vexnum;
		if(m_vexnum <= 0 || m_vexnum > MAX_VEC_NUM)
		{
			cout << "error input!" << endl;
			m_vexnum = 0;
		}
		else
		{
			break;
		}
	}

	while(true)
	{
		cout << "input edge num:";
		cin >> m_edgenum;
		if(m_edgenum <= 0 || m_edgenum > (MAX_VEC_NUM - 1) * MAX_VEC_NUM /2 )
		{
			cout << "error input!" << endl;
			m_edgenum = 0;
		}
		else
		{
			break;
		}
	}

	//输入顶点信息
	for(int i = 0; i < m_vexnum; ++i)
	{
		cout << "input the " << i << " vertex:";
		cin >> m_vex[i];
	}

	//输入边的信息
	string start, end;
	int x = 0, y = 0;
	for(int i = 0; i < m_edgenum; ++i)
	{
		while(true)
		{
			cout << "input the " << i << " edge start , end, weight:";
			cin >> start;
			x = locate(start);
			if(x == -1)
			{
				cout << "input start error!" << endl;
				continue;
			}
			cin >> end;
			y = locate(end);
			if(y == -1)
			{
				cout << "inuput end error!" << endl;
				continue;
			}
			cin >> m_edge[x][y];
			
			//m_edge[y][x] = m_edge[x][y]; 有向图
			break;
		}
		
	}
	
	return true;
}

void Graph::print()
{
	for(int i = 0; i < m_vexnum; ++i)
	{
		cout << m_vex[i] << ":" << i << endl; 
	}
	cout << endl;
	for(int i = 0; i < m_vexnum; ++i)
	{
		for(int j = 0; j < m_vexnum; ++j)
		{
			cout << m_edge[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;

	return;
}

int Graph::locate(string& vexname)
{
	for(int i = 0; i < m_vexnum; ++i)
	{
		if(vexname == m_vex[i])
		{
			return i;
		}
	}

	return -1;
}
string Graph::findVexname(int index)
{
	if(index < 0 || index >= m_vexnum)
	{
		return string();
	}

	return m_vex[index];
}

//记录每个顶点离远点的最短距离及路径信息
struct PathInfo
{
	int dis; //远点到当前顶点的最短距离
	string path; //远点到当前点的最短路径
	bool visit;//false:未访问，true:已经访问
};

class Dijstra
{
private:
	string m_sv;
	Graph m_g;
	PathInfo m_vexInfo[MAX_VEC_NUM];
public:
	void init(); //初始化路径信息
	void createGraph(); //创建图 
	bool minPath(string& vex); //计算最短路径信息
	void print(); //打印最短路径信息
};

void Dijstra::init()
{
	for(int i = 0; i < MAX_VEC_NUM; ++i)
	{
		m_vexInfo[i].dis = MAX_WEIGHT;
		m_vexInfo[i].path.clear();
		m_vexInfo[i].visit = false;
	}

	return;
}

void Dijstra::createGraph()
{
	m_g.create();
	cout << "graph info:" << endl;
	m_g.print();

	return;
}

bool Dijstra::minPath(string& vex)
{
	m_sv = vex;
	init();//初始化路径信息

	//输入起始路径信息
	int index = m_g.locate(vex);
	if(index == -1)
	{
		return false;
	}

	m_vexInfo[index].dis = 0;
	m_vexInfo[index].path.clear();
	m_vexInfo[index].visit = true;
	
	//初始状态，源点可以认为是第一个被选中的路径长度最小的点，
	//更新与源点相邻接的顶点的路径长度
	//这里每个顶点的路径长度就是状态定义，而且它是个一维数组
	for(int i = 0; i < m_g.getVexnum(); ++i)
	{
		if(!m_vexInfo[i].visit && m_g.getEdge(index, i) != MAX_WEIGHT)
		{
			m_vexInfo[i].dis = m_g.getEdge(index, i);
			m_vexInfo[i].path = vex;
		}
	}
	int pos = -1;
	int minPathLen = 0;
	/*
		这就是一个贪心算法的典型实现，注意中间的状态定义和状态转换方程
		以及相关的信息是如何记录的。
		选择当前阶段中路径长度最小的顶点作为当前阶段的最优解，
		并更新与该最优解相邻接的顶点，其实就是利用上一阶段的最优解，根据状态
		转换方程，计算出下一阶段的状态，并从状态中选择出最优解，持续这个过程
		直到所有顶点都被处理完毕。

		另外，注意path的信息是如何记录的，当我们的路径长度被更短的路径修改后，
		path信息也需要同步更新为经过新的顶点的路径信息
	*/
	for(int i = 1; i < m_g.getVexnum(); ++i)
	{
		pos = -1;
		minPathLen = MAX_PATH_LEN;
		//找到当前dis最短的顶点===>找到本阶段最优解的过程
		for(int i = 0; i < m_g.getVexnum(); ++i)
		{
			if(!m_vexInfo[i].visit && m_vexInfo[i].dis <= minPathLen)
			{
				minPathLen = m_vexInfo[i].dis;
				pos = i;
			}
		}
		//选择出最优解，并放入已访问顶点集合
		m_vexInfo[pos].visit = true;
		//根据当前阶段具有最短路径的顶点，更新顶点信息
		//基于上阶段的最优解，根据状态转换方程计算出新阶段各顶点的状态
		for(int i = 0; i < m_g.getVexnum(); ++i)
		{
			if(!m_vexInfo[i].visit && m_g.getEdge(pos, i) != MAX_WEIGHT)
			{
				if(m_vexInfo[i].dis > m_vexInfo[pos].dis + m_g.getEdge(pos, i))
				{
					m_vexInfo[i].dis = m_vexInfo[pos].dis + m_g.getEdge(pos, i);
					m_vexInfo[i].path = m_vexInfo[pos].path + "->" + m_g.findVexname(pos);
				}
			}
		}
	}

	return true;
	
}

void Dijstra::print()
{
	cout << "source vertex:" << m_sv << endl;
	for(int i = 0; i < m_g.getVexnum(); ++i)
	{
		string vexname = m_g.findVexname(i);
		if(m_sv == vexname)
		{
			continue;
		}
		cout << "dst vertex:" << vexname  << "   ";
		if(m_vexInfo[i].dis != MAX_WEIGHT)
		{
			cout << "path:" << m_vexInfo[i].path << "->" << m_g.findVexname(i)<< "          dis:" << m_vexInfo[i].dis << endl;
		}
		else
		{
			cout << "no path" << endl;
		}
	}
	cout << endl;

	return;
}

int main()
{
	Dijstra d;
	d.createGraph();

	cout << "input the source vertex:";
	string sv;
	cin >> sv;
	d.minPath(sv);
	d.print();
	
	return 0;
}