/*
图的十字链表表示法
*/

#include <iostream>
#include <stack>
#include <list>
#include <string>
using namespace std;

//弧节点
struct ArcNode
{
	int headvex;//弧头
	int tailvex;//弧尾
	ArcNode* hlink;//连接以该点为头节点的弧
	ArcNode* tlink;// 连接以该节点为尾的弧
};

//顶点
struct VexNode
{
	string value;//顶点名字
	ArcNode* firstin;//指向以该顶点为头的弧
	ArcNode* firstout;//指向以该顶点为尾的弧
};

//有向图
const int MAX_VEX_NUM = 5;
typedef struct DirectedGraph
{
	VexNode vex[MAX_VEX_NUM];//顶点结合
	int vexnum;//顶点数目
	int arcnum;//弧的数目
}DG;

int locate(DG& g, string vex)
{
	for(int i = 0; i < g.vexnum; ++i)
	{
		if(g.vex[i].value == vex)
		{
			return i;
		}
	}

	return -1;
}
int createDG (DG& g)
{
	cout << "input vexnum:";
	cin >> g.vexnum;

	cout << "input arcnum:";
	cin >> g.arcnum;

	//输入顶点信息
	for(int i = 0; i < g.vexnum; ++i)
	{
		cout << "input vex value:";
		cin >> g.vex[i].value;
		g.vex[i].firstin = g.vex[i].firstout = NULL;
	}


	//输入弧的信息
	string tail;
	string head;
	int x = 0, y = 0;
	for(int i = 0; i < g.arcnum; ++i)
	{
		//输入弧的弧尾和弧头
		cout << "input tail and head vex:";
		cin >> tail;//弧尾
		cin >> head;//弧头

		x = locate(g, tail);
		if(x == -1)
		{
			cout << "invalid start, " << tail << endl;
			return -1;
		}

		y = locate(g, head);
		if(y == -1)
		{
			cout << "invalid end, " << head << endl;
			return -1;
		}

		//创建弧节点
		ArcNode* p = new ArcNode();
		p->tailvex = x;//弧尾
		p->headvex = y;//弧头
		p->hlink = g.vex[y].firstin;
		p->tlink = g.vex[x].firstout;

		//将弧节点插入到顶点链表中
		g.vex[x].firstout = g.vex[y].firstin = p;
	}
	
	return 0;
}

void print(DG& g)
{
	for(int i = 0; i < g.vexnum; ++i)
	{
		cout << "vertex:" << g.vex[i].value << endl;
		cout << "in:";
		ArcNode* it = g.vex[i].firstin;
		//弧头相同的弧
		while(it != NULL)
		{
			cout << "(" << it->tailvex << ", " << it->headvex << ")" << " ";
			it = it->hlink;
		}
		cout << endl;
		cout << "out:";
		it = g.vex[i].firstout;
		//弧尾相同的弧
		while(it != NULL)
		{
			cout << "(" << it->tailvex << ", " << it->headvex << ")" << " ";
			it = it->tlink;
		}
		cout << endl;
	}

	return;
}

//已访问数组
bool visit[MAX_VEX_NUM];
stack<int> s;//dfs 后续遍历栈
list<int> vexset;//强连通顶点集合
void DFS(DG& g, int vex);
void DFS_Traverse(DG& g)
{
	//初始化visit数组
	for(int i = 0; i < MAX_VEX_NUM; ++i)
	{
		visit[i] = false;
	}

	//遍历顶点 集合，执行DFS访问
	for(int i = 0; i < g.vexnum; ++i)
	{
		if(!visit[i]) //顶点未被访问过
		{
			DFS(g, i);
		}
	}

	return;
}

void DFS(DG& g, int vex)
{
	//设置已访问
	visit[vex] = true;

	//遍历与该顶点相关联的顶点，执行深度优先访问
	ArcNode* p = g.vex[vex].firstout;//出边
	int connected_vex = 0;
	while(p != NULL)
	{
		//判断顶点是否已经访问过
		connected_vex = p->headvex;
		if(visit[connected_vex])
		{
			p = p->tlink;
			continue;
		}
		//未访问过时，顺着该顶点执行DFS深度遍历
		DFS(g, connected_vex);

		//访问下一条以该顶点未弧尾的边
		p = p->tlink;
	}

	//顶点的关联顶点访问完毕，该顶点入栈
	s.push(vex);
	
	return;
}

void print(stack<int>& s)
{
	cout << "DFS stack:";
	int vex = 0;
	while(!s.empty())
	{
		vex = s.top();
		s.pop();
		cout << vex << " ";
	}

	cout << endl;
	
	return;
}

void clear_vexset(list<int>& vexset)
{
	while(!vexset.empty())
	{
		vexset.pop_back();
	}

	return;
}

void print_set(DG& g, list<int>& vexset);
void Inverted_DFS(DG& g, int vex);

void Inverted_DFS_Traverse(DG& g)
{
	//初始化访问数组
	for(int i = 0; i < g.vexnum; ++i)
	{
		visit[i] = false;
	}
	clear_vexset(vexset);
	//访问第一次DFS得到的后续序列
	int vex = 0;
	while(!s.empty())
	{
		vex = s.top();
		s.pop();
		if(!visit[vex])
		{
			Inverted_DFS(g, vex);
			print_set(g, vexset);
			clear_vexset(vexset);
		}
	}


	return;
}

void Inverted_DFS(DG& g, int vex)
{
	//设置顶点已访问
	visit[vex] = true;
	//该顶点入队列
	vexset.push_back(vex);
	
	//逆向遍历，找到以该顶点为弧头的边，执行DFS
	ArcNode* p = g.vex[vex].firstin;
	int connected_vex = 0;
	while(p != NULL)
	{
		connected_vex = p->tailvex;//因为是逆向，当前顶点是弧头，这里应该取弧尾顶点
		//判断顶点是否已经被访问过
		if(visit[connected_vex])
		{
			p = p->hlink;
			continue;
		}
		//未访问过时执行DFS逆向遍历
		Inverted_DFS(g, connected_vex);
		
		p = p->hlink;
	}

	return;
}

void print_set(DG&g, list<int>& vexset)
{
	cout << "vex set:";
	list<int>::iterator it = vexset.begin();
	list<int>::iterator end = vexset.end();
	while(it != end)
	{
		cout << g.vex[*it].value << " ";
		++it;
	}

	cout << endl;
	return;
}


int main(int argc, char** argv)
{
	DG g;

	int res = createDG(g);
	if(res != 0)
	{
		cout << "create dg fail." << endl;
		return -1;
	}

	print(g);


	//dfs
	DFS_Traverse(g);
	//print(s);

	//获得强连通集合
	Inverted_DFS_Traverse(g);
	return 0;
}
