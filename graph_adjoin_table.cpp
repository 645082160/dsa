#include <iostream>
#include <list>
using namespace std;

const int MAX_VEX_NUM = 5;
struct Graph{
//�洢����ͼ
//�洢���������
char vex[MAX_VEX_NUM];
//�洢�ߵ���Ϣ
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
start:��ʼ�����±�
end:��ֹ�����±�
*/
void findpath(Graph& g, int start, int end, list<int>& path, int visit[])
{
	//�ж��Ƿ��ǳ�������
	if(start == end)
	{
		print(path);
		//����
		back(path, visit);
		return;
	}

	//�������п��ܵ�·��
	for(int i = 0; i < g.vexnum; ++i)
	{
		if(g.edge[start][i] == 1 && visit[i] == 0)//�бߴ��ڣ����Ҹõ�δ�����ʹ� 
		{
			path.push_back(i);//�ڵ��������,���뵱ǰ�ڵ�
			visit[i] = 1; //�ڵ�Ⱦɫ����һ���տ�ʼ ʵ��ʱ������
			
			findpath(g, i, end, path, visit);//��������
		}
	}

	//��startΪ��ʼ��Ŀ���·�����Ѿ����Թ�������������������
	back(path, visit);

	return;
}

//��¼�����Ƿ��Ѿ������ʹ�
bool visit[MAX_VEX_NUM];

void DFS(Graph& g, int index)
{
	//���ʵ�ǰ����
	cout << g.vex[index] << endl;
	//���õ�ǰ�����Ѿ����ʹ�
	visit[index] = true;
	//���ʵ�ǰ����Ĺ�������
	for(int i = 0; i < g.vexnum; ++i)
	{
		if(g.edge[index][i] == 1 && !visit[i]) //�ҵ������Ľڵ㣬���Ҹö���δ������
		{
			DFS(g, i); //��ȱ���
		}
	}

	return;
}
//�����������飬��֤ÿһ���ڵ㶼�ܱ����ʵ�
void traverse(Graph& g)
{
	//��ʼ��visit����
	for(int i = 0; i < g.vexnum; ++i)
	{
		visit[i] = false;
	}

	//�����������飬������ȷ���
	for(int i = 0; i < g.vexnum; ++i)
	{
		if(!visit[i]) //û�з��ʹ��Ķ������Ҫ��ȷ���
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
	
	//���붥����Ϣ
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

	//�������Ϣ
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

		//���ñߣ���Ϊ�Ǳߣ���˾������ǶԳƵ�
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


	int visit[MAX_VEX_NUM];//��¼�Ƿ��Ѿ����ʹ�
	list<int> path;

	//�ж�2������֮���Ƿ����·��
	//��ʼ��visit����
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
