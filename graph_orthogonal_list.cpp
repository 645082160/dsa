/*
ͼ��ʮ�������ʾ��
*/

#include <iostream>
#include <stack>
#include <list>
#include <string>
using namespace std;

//���ڵ�
struct ArcNode
{
	int headvex;//��ͷ
	int tailvex;//��β
	ArcNode* hlink;//�����Ըõ�Ϊͷ�ڵ�Ļ�
	ArcNode* tlink;// �����Ըýڵ�Ϊβ�Ļ�
};

//����
struct VexNode
{
	string value;//��������
	ArcNode* firstin;//ָ���Ըö���Ϊͷ�Ļ�
	ArcNode* firstout;//ָ���Ըö���Ϊβ�Ļ�
};

//����ͼ
const int MAX_VEX_NUM = 5;
typedef struct DirectedGraph
{
	VexNode vex[MAX_VEX_NUM];//������
	int vexnum;//������Ŀ
	int arcnum;//������Ŀ
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

	//���붥����Ϣ
	for(int i = 0; i < g.vexnum; ++i)
	{
		cout << "input vex value:";
		cin >> g.vex[i].value;
		g.vex[i].firstin = g.vex[i].firstout = NULL;
	}


	//���뻡����Ϣ
	string tail;
	string head;
	int x = 0, y = 0;
	for(int i = 0; i < g.arcnum; ++i)
	{
		//���뻡�Ļ�β�ͻ�ͷ
		cout << "input tail and head vex:";
		cin >> tail;//��β
		cin >> head;//��ͷ

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

		//�������ڵ�
		ArcNode* p = new ArcNode();
		p->tailvex = x;//��β
		p->headvex = y;//��ͷ
		p->hlink = g.vex[y].firstin;
		p->tlink = g.vex[x].firstout;

		//�����ڵ���뵽����������
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
		//��ͷ��ͬ�Ļ�
		while(it != NULL)
		{
			cout << "(" << it->tailvex << ", " << it->headvex << ")" << " ";
			it = it->hlink;
		}
		cout << endl;
		cout << "out:";
		it = g.vex[i].firstout;
		//��β��ͬ�Ļ�
		while(it != NULL)
		{
			cout << "(" << it->tailvex << ", " << it->headvex << ")" << " ";
			it = it->tlink;
		}
		cout << endl;
	}

	return;
}

//�ѷ�������
bool visit[MAX_VEX_NUM];
stack<int> s;//dfs ��������ջ
list<int> vexset;//ǿ��ͨ���㼯��
void DFS(DG& g, int vex);
void DFS_Traverse(DG& g)
{
	//��ʼ��visit����
	for(int i = 0; i < MAX_VEX_NUM; ++i)
	{
		visit[i] = false;
	}

	//�������� ���ϣ�ִ��DFS����
	for(int i = 0; i < g.vexnum; ++i)
	{
		if(!visit[i]) //����δ�����ʹ�
		{
			DFS(g, i);
		}
	}

	return;
}

void DFS(DG& g, int vex)
{
	//�����ѷ���
	visit[vex] = true;

	//������ö���������Ķ��㣬ִ��������ȷ���
	ArcNode* p = g.vex[vex].firstout;//����
	int connected_vex = 0;
	while(p != NULL)
	{
		//�ж϶����Ƿ��Ѿ����ʹ�
		connected_vex = p->headvex;
		if(visit[connected_vex])
		{
			p = p->tlink;
			continue;
		}
		//δ���ʹ�ʱ��˳�Ÿö���ִ��DFS��ȱ���
		DFS(g, connected_vex);

		//������һ���Ըö���δ��β�ı�
		p = p->tlink;
	}

	//����Ĺ������������ϣ��ö�����ջ
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
	//��ʼ����������
	for(int i = 0; i < g.vexnum; ++i)
	{
		visit[i] = false;
	}
	clear_vexset(vexset);
	//���ʵ�һ��DFS�õ��ĺ�������
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
	//���ö����ѷ���
	visit[vex] = true;
	//�ö��������
	vexset.push_back(vex);
	
	//����������ҵ��Ըö���Ϊ��ͷ�ıߣ�ִ��DFS
	ArcNode* p = g.vex[vex].firstin;
	int connected_vex = 0;
	while(p != NULL)
	{
		connected_vex = p->tailvex;//��Ϊ�����򣬵�ǰ�����ǻ�ͷ������Ӧ��ȡ��β����
		//�ж϶����Ƿ��Ѿ������ʹ�
		if(visit[connected_vex])
		{
			p = p->hlink;
			continue;
		}
		//δ���ʹ�ʱִ��DFS�������
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

	//���ǿ��ͨ����
	Inverted_DFS_Traverse(g);
	return 0;
}
