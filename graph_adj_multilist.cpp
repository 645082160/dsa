#include <iostream>
#include <list>
using namespace std;


const int MAX_VEX_NUM = 5;

//边节点
struct EdgeNode
{
	int ivex;//第一个依赖节点
	int jvex;//第二个依赖节点
	EdgeNode* ilink;//指向下一条依附于ivex的边
	EdgeNode* jlink;//指向下一条依附于jvex的边
};


//顶点
struct VexNode
{
	string data; //顶点的值
	EdgeNode* firstedge;//依赖顶点的边构成的链表头指针
};

//图
struct UDG
{
	VexNode vex[MAX_VEX_NUM];
	int vexnum;
	int edgenum;
};

int locate(UDG& g, string data)
{
	for(int i = 0; i < g.vexnum; ++i)
	{
		if(g.vex[i].data == data)
		{
			return i;
		}
	}

	return -1;
}
//创建UDG
int createUDG(UDG& g)
{
	//输入顶点个数和边的条数
	cout << "input vex num:";
	cin >> g.vexnum;

	cout << "input edge num:";
	cin  >> g.edgenum;
	
	//初始化顶点
	for(int i = 0; i < g.vexnum; ++i)
	{
		cout << "input vertex data:";
		cin >> g.vex[i].data;
		
		g.vex[i].firstedge = NULL;
	}

	//输入边
	string ivex, jvex;
	int x, y;
	for(int i = 0; i < g.edgenum; ++i)
	{
		//输入边依赖的2个顶点
		cout << "input vertex of edge:";
		cin >> ivex;
		cin >> jvex;

		//定位顶点下标
		x  = locate(g, ivex);
		if(x == -1)
		{
			cout << "invalid vertex: " << ivex << endl;
			return -1;
		}

		y = locate(g, jvex);
		if(y == -1)
		{
			cout << "invalid vertex: " << jvex << endl;
			return -1;
		}
		//创建边
		EdgeNode* p = new EdgeNode();
		p->ivex = x;
		p->jvex = y;
		p->ilink = g.vex[x].firstedge;
		p->jlink = g.vex[y].firstedge;

		//将边加入到2个顶点的链表中
		g.vex[x].firstedge = g.vex[y].firstedge = p;
	}

	return 0;
}


void print(UDG& g)
{
	//遍历每个顶点，打印其相关联的边信息
	for(int i = 0; i < g.vexnum; ++i)
	{
		cout << "vertex:";
		cout << g.vex[i].data << endl;

		cout << "edge ilink list:";
		EdgeNode* it = g.vex[i].firstedge;
		while(it != NULL)
		{
			cout << "(" << it->ivex << ", " << it->jvex << ") ";
			if(it->ivex == i)
			{
				it = it->ilink;
			}
			else if(it->jvex == i)
			{
				it = it->jlink;
			}
			else
			{
				cout << "it null" << endl;
				it = NULL;
			}
			
		}
		cout << endl;
	}

	cout << endl;
	return;
}


//visit数组记录节点是否已经被访问
bool visit[MAX_VEX_NUM];
//DFS执行深度遍历
void DFS(UDG& g, int index)
{
	//访问当前顶点
	cout << g.vex[index].data << endl;
	//设置顶点已访问
	visit[index] = true;
	
	//遍历当前顶点的所有关联顶点，执行深度遍历
	EdgeNode* p = g.vex[index].firstedge;
	int i = 0;
	while(p != NULL)
	{
		//得到下一个关联顶点，如果未访问，则执行深度遍历
		i = p->ivex == index ? p->jvex : p->ivex;
		if(!visit[i])
		{
			DFS(g, i);
		}
		//取下一条关联的边
		p = p->ivex == index ? p->jlink : p->ilink;
	}

	return;
}

//traverse遍历每一个顶点，执行深度遍历
void traverse(UDG& g)
{
	//初始化visit数组
	for(int i = 0; i < MAX_VEX_NUM; ++i)
	{
		visit[i] = false;
	}
	//遍历顶点数组，选取未访问过的顶点为起始点进行深度遍历
	for(int i = 0; i < g.vexnum; ++i)
	{
		//顶点未被访问过，则选择该顶点作为起始点 开始深度遍历
		if(!visit[i])
		{
			DFS(g, i);
		}
	}

	return;
}

//广度优先搜索
//是否访问数组visit，已声明
//队列，按路径长度记录节点
list<int> q;

void BFS(UDG& g)
{
	//初始化visit数组
	for(int i = 0; i < MAX_VEX_NUM; ++i)
	{
		visit[i] = false;
	}

	//遍历顶点，开始宽度优先遍历
	for(int i = 0; i < g.vexnum; ++i)
	{
		if(visit[i]) //已经访问过的顶点不再访问
		{
			cout << i << "already visited" << endl;
			continue;
		}
		//访问节点
		cout << g.vex[i].data << endl;
		//设置节点已经访问过
		visit[i] = true;
		//当前访问的顶点入队列
		q.push_back(i);
		//BFS访问，直到栈为空
		EdgeNode* p = NULL;
		int curr_vex = 0;
		int connected_vex = 0;
		while(!q.empty())
		{
			//最早的顶点出栈
			curr_vex = q.front();
			q.pop_front();

			//查找该顶点相关联的顶点进行访问并入栈
			p = g.vex[curr_vex].firstedge;
			//cout << "node:" << curr_vex << endl;
			while(p != NULL)
			{
				connected_vex  = p->ivex == curr_vex ? p->jvex : p->ivex;
				//检查该顶点是否可以访问
				if(visit[connected_vex])
				{
					//检查下一个关联顶点
					p = p->ivex == curr_vex ? p->ilink : p->jlink;
					continue;
				}
				//访问该顶点
				cout << g.vex[connected_vex].data << endl;
				//设置该顶点已访问
				visit[connected_vex] = true;
				//入队列
				q.push_back(connected_vex);
				//cout << "push back:" << connected_vex << endl;
				//查看下一个关联顶点
				p = p->ivex == curr_vex ? p->ilink : p->jlink;
			}
		}
	}


	return;
}

//二叉树节点数据结构
struct TreeNode
{
	int vex;//节点所表示的顶点
	TreeNode* lchild;//第一个孩子
	TreeNode* nextsibling;//下一个兄弟
};

void DFSTree(UDG& g, int vex, TreeNode*& root);

//深度遍历创建生成树
void DFSForeast(UDG& g, TreeNode*& root)
{
	//初始化visit数组
	for(int i = 0; i < MAX_VEX_NUM; ++i)
	{
		visit[i] = false;
	}

	root = NULL;
	TreeNode* p = NULL;
	TreeNode* q = NULL;
	//遍历顶点数组，选取未访问过的顶点为起始点进行深度遍历
	for(int i = 0; i < g.vexnum; ++i)
	{
		//顶点未被访问过，则选择该顶点作为起始点 开始深度遍历
		if(!visit[i])
		{
			//设置顶点已经被访问过
			visit[i] = true;
			
			//当前节点未被访问过，生成一个树节点
			p = new TreeNode();
			p->vex = i;
			p->lchild = NULL;
			p->nextsibling = NULL;

			//如果是第一个根节点，为root赋值
			if(root == NULL)
			{
				root = p;
			}
			else
			{
				//不是根节点的时候，那么是根节点的兄弟，即另外的树
				q->nextsibling = p;
			}
			q = p;
			
			//以p为根，深度优先遍历，构造生成树
			DFSTree(g, i, p);
		}
	}
}

void DFSTree(UDG& g, int vex, TreeNode*& root)
{
	//寻找vex的关联节点，深度遍历，并构造树
	TreeNode* p = NULL;
	TreeNode* q = NULL;

	EdgeNode* ep = NULL;

	//找到vex的关联节点，执行深度遍历
	bool first = true;
	int connected_vex = 0;
	ep = g.vex[vex].firstedge;
	while(ep != NULL)
	{
		connected_vex = ep->ivex == vex ? ep->jvex : ep->ivex;
		//判断顶点是否被访问过
		if(visit[connected_vex])
		{
			ep = ep->ivex == vex ? ep->ilink : ep->jlink;
			continue;
		}

		visit[connected_vex] = true;

		//顶点未被访问过
		p = new TreeNode();
		p->vex = connected_vex;
		p->lchild = NULL;
		p->nextsibling = NULL;

		if(first) //第一个关联顶点
		{
			root->lchild = p;
			first = false;
		}
		else
		{
			q->nextsibling = p;
		}

		q = p;
		
		DFSTree(g, connected_vex, p);//深度遍历，继续构造深度遍历生成树

		ep = ep->ivex == vex ? ep->ilink : ep->jlink;
	}
	
	return;
}

void preorder(TreeNode* root)
{
	if(root == NULL)
	{
		return;
	}

	cout << root->vex << endl;
	preorder(root->lchild);
	preorder(root->nextsibling);
	
	return;
}

void inorder(TreeNode* root)
{
	if(root == NULL)
	{
		return;
	}
	inorder(root->lchild);
	cout << root->vex << endl;
	inorder(root->nextsibling);
	
	return;
}	
int main(int argc, char** argv)
{
	UDG g;
	int res = createUDG(g);
	if(res == -1)
	{
		cout << "create UDG fail." << endl;
		return -1;
	}

	print(g);


	//DFS
	cout << "DFS order:" << endl;
	traverse(g);


	cout << "BFS order:" << endl;
	BFS(g);

	cout << "DFS forest:" << endl;

	TreeNode* root = NULL;
	DFSForeast(g, root);

	cout << "preorder:" << endl;
	preorder(root);

	cout << "inorder:" << endl;
	inorder(root);
	
	return 0;
}
