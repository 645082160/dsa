#include <iostream>
#include <list>
using namespace std;


const int MAX_VEX_NUM = 5;

//�߽ڵ�
struct EdgeNode
{
	int ivex;//��һ�������ڵ�
	int jvex;//�ڶ��������ڵ�
	EdgeNode* ilink;//ָ����һ��������ivex�ı�
	EdgeNode* jlink;//ָ����һ��������jvex�ı�
};


//����
struct VexNode
{
	string data; //�����ֵ
	EdgeNode* firstedge;//��������ı߹��ɵ�����ͷָ��
};

//ͼ
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
//����UDG
int createUDG(UDG& g)
{
	//���붥������ͱߵ�����
	cout << "input vex num:";
	cin >> g.vexnum;

	cout << "input edge num:";
	cin  >> g.edgenum;
	
	//��ʼ������
	for(int i = 0; i < g.vexnum; ++i)
	{
		cout << "input vertex data:";
		cin >> g.vex[i].data;
		
		g.vex[i].firstedge = NULL;
	}

	//�����
	string ivex, jvex;
	int x, y;
	for(int i = 0; i < g.edgenum; ++i)
	{
		//�����������2������
		cout << "input vertex of edge:";
		cin >> ivex;
		cin >> jvex;

		//��λ�����±�
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
		//������
		EdgeNode* p = new EdgeNode();
		p->ivex = x;
		p->jvex = y;
		p->ilink = g.vex[x].firstedge;
		p->jlink = g.vex[y].firstedge;

		//���߼��뵽2�������������
		g.vex[x].firstedge = g.vex[y].firstedge = p;
	}

	return 0;
}


void print(UDG& g)
{
	//����ÿ�����㣬��ӡ��������ı���Ϣ
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


//visit�����¼�ڵ��Ƿ��Ѿ�������
bool visit[MAX_VEX_NUM];
//DFSִ����ȱ���
void DFS(UDG& g, int index)
{
	//���ʵ�ǰ����
	cout << g.vex[index].data << endl;
	//���ö����ѷ���
	visit[index] = true;
	
	//������ǰ��������й������㣬ִ����ȱ���
	EdgeNode* p = g.vex[index].firstedge;
	int i = 0;
	while(p != NULL)
	{
		//�õ���һ���������㣬���δ���ʣ���ִ����ȱ���
		i = p->ivex == index ? p->jvex : p->ivex;
		if(!visit[i])
		{
			DFS(g, i);
		}
		//ȡ��һ�������ı�
		p = p->ivex == index ? p->jlink : p->ilink;
	}

	return;
}

//traverse����ÿһ�����㣬ִ����ȱ���
void traverse(UDG& g)
{
	//��ʼ��visit����
	for(int i = 0; i < MAX_VEX_NUM; ++i)
	{
		visit[i] = false;
	}
	//�����������飬ѡȡδ���ʹ��Ķ���Ϊ��ʼ�������ȱ���
	for(int i = 0; i < g.vexnum; ++i)
	{
		//����δ�����ʹ�����ѡ��ö�����Ϊ��ʼ�� ��ʼ��ȱ���
		if(!visit[i])
		{
			DFS(g, i);
		}
	}

	return;
}

//�����������
//�Ƿ��������visit��������
//���У���·�����ȼ�¼�ڵ�
list<int> q;

void BFS(UDG& g)
{
	//��ʼ��visit����
	for(int i = 0; i < MAX_VEX_NUM; ++i)
	{
		visit[i] = false;
	}

	//�������㣬��ʼ������ȱ���
	for(int i = 0; i < g.vexnum; ++i)
	{
		if(visit[i]) //�Ѿ����ʹ��Ķ��㲻�ٷ���
		{
			cout << i << "already visited" << endl;
			continue;
		}
		//���ʽڵ�
		cout << g.vex[i].data << endl;
		//���ýڵ��Ѿ����ʹ�
		visit[i] = true;
		//��ǰ���ʵĶ��������
		q.push_back(i);
		//BFS���ʣ�ֱ��ջΪ��
		EdgeNode* p = NULL;
		int curr_vex = 0;
		int connected_vex = 0;
		while(!q.empty())
		{
			//����Ķ����ջ
			curr_vex = q.front();
			q.pop_front();

			//���Ҹö���������Ķ�����з��ʲ���ջ
			p = g.vex[curr_vex].firstedge;
			//cout << "node:" << curr_vex << endl;
			while(p != NULL)
			{
				connected_vex  = p->ivex == curr_vex ? p->jvex : p->ivex;
				//���ö����Ƿ���Է���
				if(visit[connected_vex])
				{
					//�����һ����������
					p = p->ivex == curr_vex ? p->ilink : p->jlink;
					continue;
				}
				//���ʸö���
				cout << g.vex[connected_vex].data << endl;
				//���øö����ѷ���
				visit[connected_vex] = true;
				//�����
				q.push_back(connected_vex);
				//cout << "push back:" << connected_vex << endl;
				//�鿴��һ����������
				p = p->ivex == curr_vex ? p->ilink : p->jlink;
			}
		}
	}


	return;
}

//�������ڵ����ݽṹ
struct TreeNode
{
	int vex;//�ڵ�����ʾ�Ķ���
	TreeNode* lchild;//��һ������
	TreeNode* nextsibling;//��һ���ֵ�
};

void DFSTree(UDG& g, int vex, TreeNode*& root);

//��ȱ�������������
void DFSForeast(UDG& g, TreeNode*& root)
{
	//��ʼ��visit����
	for(int i = 0; i < MAX_VEX_NUM; ++i)
	{
		visit[i] = false;
	}

	root = NULL;
	TreeNode* p = NULL;
	TreeNode* q = NULL;
	//�����������飬ѡȡδ���ʹ��Ķ���Ϊ��ʼ�������ȱ���
	for(int i = 0; i < g.vexnum; ++i)
	{
		//����δ�����ʹ�����ѡ��ö�����Ϊ��ʼ�� ��ʼ��ȱ���
		if(!visit[i])
		{
			//���ö����Ѿ������ʹ�
			visit[i] = true;
			
			//��ǰ�ڵ�δ�����ʹ�������һ�����ڵ�
			p = new TreeNode();
			p->vex = i;
			p->lchild = NULL;
			p->nextsibling = NULL;

			//����ǵ�һ�����ڵ㣬Ϊroot��ֵ
			if(root == NULL)
			{
				root = p;
			}
			else
			{
				//���Ǹ��ڵ��ʱ����ô�Ǹ��ڵ���ֵܣ����������
				q->nextsibling = p;
			}
			q = p;
			
			//��pΪ����������ȱ���������������
			DFSTree(g, i, p);
		}
	}
}

void DFSTree(UDG& g, int vex, TreeNode*& root)
{
	//Ѱ��vex�Ĺ����ڵ㣬��ȱ�������������
	TreeNode* p = NULL;
	TreeNode* q = NULL;

	EdgeNode* ep = NULL;

	//�ҵ�vex�Ĺ����ڵ㣬ִ����ȱ���
	bool first = true;
	int connected_vex = 0;
	ep = g.vex[vex].firstedge;
	while(ep != NULL)
	{
		connected_vex = ep->ivex == vex ? ep->jvex : ep->ivex;
		//�ж϶����Ƿ񱻷��ʹ�
		if(visit[connected_vex])
		{
			ep = ep->ivex == vex ? ep->ilink : ep->jlink;
			continue;
		}

		visit[connected_vex] = true;

		//����δ�����ʹ�
		p = new TreeNode();
		p->vex = connected_vex;
		p->lchild = NULL;
		p->nextsibling = NULL;

		if(first) //��һ����������
		{
			root->lchild = p;
			first = false;
		}
		else
		{
			q->nextsibling = p;
		}

		q = p;
		
		DFSTree(g, connected_vex, p);//��ȱ���������������ȱ���������

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
