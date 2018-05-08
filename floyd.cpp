/*
ʵ��floyd�㷨
1���ڽӾ���洢����ͼ��
2��D�����¼·������
3��p�����¼·����Ϣ
*/
#include <iostream>
#include <stack>
using namespace std;

const int MAX_VEX_NUM = 10;
const int MAX_WEIGHT = 100000;//��ʾ�����
class GraphMatrix
{
public:
	int locate(string& vex); //֪���������֣��ҵ���index
	string locate(int vex);// ֪��index���ҵ���������
	bool init();
	bool create();
	void print();
	int get_vex_num()
	{
		return m_vex_num;
	}

	int get_edge_num()
	{
		return m_edge_num;
	}

	int get_edge(int x, int y)
	{
		return m_edge[x][y];
	}
private:
	int m_vex_num;
	int m_edge_num;
	string m_vex[MAX_VEX_NUM]; //��¼������Ϣ
	int m_edge[MAX_VEX_NUM][MAX_VEX_NUM];//��¼����Ϣ,0��ʾ�����
};

int GraphMatrix::locate(string& vex)
{
	for(int i = 0; i < m_vex_num; ++i)
	{
		if(vex == m_vex[i])
		{
			return i;
		}
	}
	return -1;
}

string GraphMatrix::locate(int vex)
{
	if(vex >= m_vex_num)
	{
		return string("error");
	}
	return m_vex[vex];
}

bool GraphMatrix::init()
{
	m_vex_num = 0;
	m_edge_num = 0;
	for(int i = 0; i < MAX_VEX_NUM; ++i)
	{
		for(int j = 0; j < MAX_VEX_NUM; ++j)
		{
			m_edge[i][j] = MAX_WEIGHT;
		}
	}
	return true;
}

bool GraphMatrix::create()
{
	//���붥���Ȩֵ
	cout << "input vex num:";
	cin >> m_vex_num;
	if(m_vex_num <= 0)
	{
		cout << "vex num error." << endl;
		return false;
	}
	for(int i = 0; i < m_vex_num; ++i)
	{
		cout << "input vex " << i << " name:";
		cin >> m_vex[i];
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
	for(int i = 0; i < m_edge_num; ++i)
	{
		cout << "input " << i << " start end weight:";
		cin >> start;
		cin >> end;

		s = locate(start);
		if(s == -1)
		{
			cout << "edge error." << endl;
			return false;
		}
		e = locate(end);
		if(e == -1)
		{
			cout << "edge error." << endl;
			return false;
		}

		//����ͼ
		cin >> m_edge[s][e]; 
	}
	
	return true;
}

void GraphMatrix::print()
{
	for(int i = 0; i < m_vex_num; ++i)
	{
		for(int j = 0; j < m_vex_num; ++j)
		{
			cout << m_edge[i][j] << "               ";
		}
		cout << endl;
	}
	cout << endl;
	return;
}
class Floyd
{
public:
	bool init();//��ʼ����������ͼ��Ϣ
	void find_path();//ִ��floyd�㷨
	void print_path();//��ӡ·����Ϣ����̾���
	void print_p();
private:
	GraphMatrix m_g;
	int m_visited[MAX_VEX_NUM];
	int m_d[MAX_VEX_NUM][MAX_VEX_NUM];//��¼�������
	int m_p[MAX_VEX_NUM][MAX_VEX_NUM];//��¼��¼·����Ϣ
};

bool Floyd::init()
{
	//��ʼ��d��p
	for(int i = 0; i < MAX_VEX_NUM; ++i)
	{
		m_visited[i] = 0;//��ʼ��Ϊδ������
		for(int j = 0; j < MAX_VEX_NUM; ++j)
		{
			m_d[i][j] = MAX_WEIGHT;
		}
	}

	
	if(m_g.init())
	{
		if(m_g.create())
		{
			m_g.print();
		
			int vex_num = m_g.get_vex_num();
			for(int i = 0; i < vex_num; ++i)
			{
				for(int j = 0; j < vex_num; ++j)
				{
					if(m_g.get_edge(i, j) == MAX_WEIGHT)
					{
						m_p[i][j] = -1;//��ʾû��·��
					}
					else
					{
						m_p[i][j] = j;
						m_d[i][j] = m_g.get_edge(i, j);
					}
				}
			}
		}
	}
	
	return true;
}

void Floyd::find_path()
{
	int vex_num = m_g.get_vex_num();
	for(int k = 0; k < vex_num; ++k)
	{
		for(int v = 0; v < vex_num; ++v)
		{
			for(int w = 0; w < vex_num; ++w)
			{
				//�����д���ؼ����� ����ֵ�ĺ���
				if(m_d[v][k] + m_d[k][w] < m_d[v][w])
				{
					m_d[v][w] = m_d[v][k] + m_d[k][w];
					m_p[v][w] = k;
				}
			}
		}
	}
	return;
}

void Floyd::print_path()
{
	string start, end;
	int x = 0, y = 0;
	stack<string> path;
	while(true)
	{
		cout << "input start end:";
		cin >> start;
		cin >> end;
		x = m_g.locate(start);
		y = m_g.locate(end);
		if(x == -1 || y == -1)
		{
			cout << "vertex name error." << endl;
			return;
		}

		if(m_d[x][y] == MAX_WEIGHT)
		{
			cout << "no path" << endl;
			return;
		}

		
		int k = y;
		while(m_p[x][k] != k)
		{
			//cout << "test:" << k << endl;
			path.push(m_g.locate(k));
			k = m_p[x][k];
		}
		path.push(m_g.locate(k));
		path.push(m_g.locate(x));

		cout << "path:" << endl;
		cout << "len:" << m_d[x][y] << endl;
		cout << "seq:";
		while(!path.empty())
		{
			cout << path.top() << " ";
			path.pop();
		}
		cout << endl;
		
	}
	
	return;
}

void Floyd::print_p()
{
	for(int i = 0; i < m_g.get_vex_num(); ++ i)
	{
		for(int j = 0; j < m_g.get_vex_num(); ++j)
		{
			cout << m_p[i][j] << "          ";
		}
		cout << endl;
	}

	cout << endl;
	return;
}

int main(int argc, char** argv)
{
	Floyd f;
	if(f.init())
	{
		f.find_path();
		f.print_path();
	}
	return 0;
}
