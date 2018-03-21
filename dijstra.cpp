#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::cin;
using std::string;
/*
1��ʹ���ڽӾ����ʾͼ��
2��ʹ��dijstra�㷨��ô�ĳ��Դ�㿪ʼ�ģ���ͼ�����ඥ�� �����·����
*/
const int MAX_PATH_LEN = 10000;//���·������
const int MAX_WEIGHT = 1000;//��ʾ����֮�������ӣ��������
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
	void init();//��ʼ��
	bool create();//����ͼ
	void print();//���ͼ
	string findVexname(int index);
	int locate(string& vexname); //��������������е�λ��
	
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
	//���붥�����ͱ���
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

	//���붥����Ϣ
	for(int i = 0; i < m_vexnum; ++i)
	{
		cout << "input the " << i << " vertex:";
		cin >> m_vex[i];
	}

	//����ߵ���Ϣ
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
			
			//m_edge[y][x] = m_edge[x][y]; ����ͼ
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

//��¼ÿ��������Զ�����̾��뼰·����Ϣ
struct PathInfo
{
	int dis; //Զ�㵽��ǰ�������̾���
	string path; //Զ�㵽��ǰ������·��
	bool visit;//false:δ���ʣ�true:�Ѿ�����
};

class Dijstra
{
private:
	string m_sv;
	Graph m_g;
	PathInfo m_vexInfo[MAX_VEC_NUM];
public:
	void init(); //��ʼ��·����Ϣ
	void createGraph(); //����ͼ 
	bool minPath(string& vex); //�������·����Ϣ
	void print(); //��ӡ���·����Ϣ
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
	init();//��ʼ��·����Ϣ

	//������ʼ·����Ϣ
	int index = m_g.locate(vex);
	if(index == -1)
	{
		return false;
	}

	m_vexInfo[index].dis = 0;
	m_vexInfo[index].path.clear();
	m_vexInfo[index].visit = true;
	
	//��ʼ״̬��Դ�������Ϊ�ǵ�һ����ѡ�е�·��������С�ĵ㣬
	//������Դ�����ڽӵĶ����·������
	//����ÿ�������·�����Ⱦ���״̬���壬�������Ǹ�һά����
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
		�����һ��̰���㷨�ĵ���ʵ�֣�ע���м��״̬�����״̬ת������
		�Լ���ص���Ϣ����μ�¼�ġ�
		ѡ��ǰ�׶���·��������С�Ķ�����Ϊ��ǰ�׶ε����Ž⣬
		������������Ž����ڽӵĶ��㣬��ʵ����������һ�׶ε����Ž⣬����״̬
		ת�����̣��������һ�׶ε�״̬������״̬��ѡ������Ž⣬�����������
		ֱ�����ж��㶼��������ϡ�

		���⣬ע��path����Ϣ����μ�¼�ģ������ǵ�·�����ȱ����̵�·���޸ĺ�
		path��ϢҲ��Ҫͬ������Ϊ�����µĶ����·����Ϣ
	*/
	for(int i = 1; i < m_g.getVexnum(); ++i)
	{
		pos = -1;
		minPathLen = MAX_PATH_LEN;
		//�ҵ���ǰdis��̵Ķ���===>�ҵ����׶����Ž�Ĺ���
		for(int i = 0; i < m_g.getVexnum(); ++i)
		{
			if(!m_vexInfo[i].visit && m_vexInfo[i].dis <= minPathLen)
			{
				minPathLen = m_vexInfo[i].dis;
				pos = i;
			}
		}
		//ѡ������Ž⣬�������ѷ��ʶ��㼯��
		m_vexInfo[pos].visit = true;
		//���ݵ�ǰ�׶ξ������·���Ķ��㣬���¶�����Ϣ
		//�����Ͻ׶ε����Ž⣬����״̬ת�����̼�����½׶θ������״̬
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