#include <iostream>
#include <list>
using namespace std;

const int MAX_VEX_NUM = 5;
struct Graph{
//存储无向图
//存储顶点的数组
char vex[MAX_VEX_NUM];
//存储边的信息
int edge[MAX_VEX_NUM][MAX_VEX_NUM];
int vexnum;
int edgenum;
};



void init(Graph& g)
{
	for(int i = 0; i < MAX_VEX_NUM; ++i)
	{
		g.vex[i] = 'x';
	}

	for(int i = 0; i < MAX_VEX_NUM; ++i)
	{
		for(int j = 0; j < MAX_VEX_NUM; ++j)
		{
			g.edge[i][j] = 0;
		}
	}

	g.vexnum = 0;
	g.edgenum = 0;

	return;
}

int locate(Graph& g, char node)
{
	for(int i = 0; i < g.vexnum; ++i)
	{
		if(g.vex[i] == node)
		{
			return i;
		}
	}

	return -1;
}

void print(list<int>& path)
{
	list<int>::iterator it = path.begin();
	list<int>::iterator end = path.end();
	while(it != end)
	{
		cout << *it << " ";
		++it;
	}

	cout << endl;

	return;
}

void back(list<int>& path, int visit[])
{
	int pre = path.back();
	visit[pre] = 0;

	path.pop_back();

	return;
}
/*
start:起始顶点下标
end:终止顶点下标
*/
void findpath(Graph& g, int start, int end, list<int>& path, int visit[])
{
	//判断是否是出口条件
	if(start == end)
	{
		print(path);
		//回退
		back(path, visit);
		return;
	}

	//尝试所有可能的路径
	for(int i = 0; i < g.vexnum; ++i)
	{
		if(g.edge[start][i] == 1 && visit[i] == 0)//有边存在，并且该点未被访问过 
		{
			path.push_back(i);//节点情况正常,加入当前节点
			visit[i] = 1; //节点染色，这一步刚开始 实现时被遗忘
			
			findpath(g, i, end, path, visit);//继续深入
		}
	}

	//以start为起始点的可能路径都已经尝试过，不符合条件，回退
	back(path, visit);

	return;
}

//记录顶点是否已经被访问过
bool visit[MAX_VEX_NUM];

void DFS(Graph& g, int index)
{
	//访问当前顶点
	cout << g.vex[index] << endl;
	//设置当前顶点已经访问过
	visit[index] = true;
	//访问当前顶点的关联顶点
	for(int i = 0; i < g.vexnum; ++i)
	{
		if(g.edge[index][i] == 1 && !visit[i]) //找到关联的节点，并且该顶点未被访问
		{
			DFS(g, i); //深度遍历
		}
	}

	return;
}
//遍历顶点数组，保证每一个节点都能被访问到
void traverse(Graph& g)
{
	//初始化visit数组
	for(int i = 0; i < g.vexnum; ++i)
	{
		visit[i] = false;
	}

	//遍历顶点数组，深度优先访问
	for(int i = 0; i < g.vexnum; ++i)
	{
		if(!visit[i]) //没有访问过的顶点才需要深度访问
		{
			DFS(g, i);
		}
	}
	
	return;
}

int main(int argc, char** argv)
{
	Graph g;
	

	init(g);
	cout << "input vetex num:";
	cin >> g.vexnum;
	cout << "input edge num:";
	cin >> g.edgenum;
	
	//输入顶点信息
	for(int i = 0; i < g.vexnum; ++i)
	{
		cout << "input vetex:";
		cin >> g.vex[i];
	}

	cout << "vetex:";
	for(int i = 0; i < g.vexnum; ++i)
	{
		cout << g.vex[i] << " ";
	}

	cout << endl;

	//输入边信息
	char start;
	char end;
	int x = 0; 
	int y = 0;
	for(int i = 0; i < g.edgenum; ++i)
	{
		x = y = 0;
		cout << "input edge start vetex:";
		cin >> start;
		cout << "input edge end vetex:";
		cin >> end;

		x = locate(g, start);
		if(x == -1)
		{
			cout << "error x vetex" << endl;
			return -1;
		}

		y = locate(g, end);
		if(y == -1)
		{
			cout << "error y vetex" << endl;
			return -1;
		}

		//设置边，因为是边，因此矩阵中是对称的
		g.edge[x][y] = 1;
		g.edge[y][x] = 1;
	}

	cout << "edges:" << endl;
	for(int i = 0; i < MAX_VEX_NUM; ++i)
	{
		for(int j = 0; j < MAX_VEX_NUM; ++j)
		{
			cout << g.edge[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;


	int visit[MAX_VEX_NUM];//记录是否已经访问过
	list<int> path;

	//判断2个顶点之间是否存在路径
	//初始化visit数组
	for(int i = 0; i < MAX_VEX_NUM; ++i)
	{
		visit[i] = 0;
	}

	cout  << "find path test:" << endl;
	while(true)
	{
		cout << "input start node:";
		cin >> start;
		x = locate(g, start);
		if(start == -1)
		{
			cout << "node fail" << endl;
		}
		else
		{
			break;
		}
	}

	while(true)
	{
		cout << "input end node:";
		cin >> end;
		y = locate(g, end);
		if(y == -1)
		{
			cout << "node fail" << endl;
		}
		else
		{
			break;
		}
	}

	cout << "start:" << x << ", end:" << y << endl;



	
	path.push_back(x);
	visit[x] = 1;
	findpath(g, x, y, path, visit);


	//deep fist search
	traverse(g);
	
	
	return 0;
}
