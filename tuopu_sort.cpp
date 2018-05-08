#include <iostream>
#include <stack>
#include <list>
using namespace std;


const int MAX_VEX_NUM = 20;

struct Node
{
	int vex;
	int weight;//AOE������ʾ��ĳ���ʱ�䣬AOV��������Ϊ0
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
	bool init();//��ʼ��
	bool create();//����ͼ��Ϣ
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
	Vertex m_vex[MAX_VEX_NUM];//��������
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
	//�������Ϣ
	for(int i = 0; i < m_edge_num; ++i)
	{
		cout << "input start , end, weight  of edge:";
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
		cin >> tmp->weight;
		
		m_vex[s].first = tmp;

		/* ����ͼ��������ԳƵ��㷨
		tmp = new Node();
		tmp->vex = s;
		tmp->next = m_vex[e].first;

		m_vex[e].first = tmp;
		*/
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
			cout << "(" << locate_vex(p->vex) << "," << p->weight << ")";
			p = p->next;
		}
		cout << endl;
	}

	return;
}

class TopoSort
{
public:
	bool init();
	void sort();
	void print();
private:
	GraphAdjTable m_g;
	stack<int> m_node;//���Ϊ0�Ķ���
	int m_in[MAX_VEX_NUM];//��¼ÿ������Ķ�
	list<int> m_list;//��¼������������
	int m_count;//�ж��Ƿ��л�
};

bool TopoSort::init()
{
	for(int i = 0; i < MAX_VEX_NUM; ++i)
	{
		m_in[i] = 0;
	}

	m_count = 0;

	if(m_g.init())
	{
		if(m_g.create())
		{
			//�������ж��㣬���¶������
			for(int i = 0; i < m_g.get_vex_num(); ++i)
			{
				Node* p = m_g.get_vex(i)->first;//�õ������ͷָ��
				while(p)
				{
					//���¹����������ȡ�
					++m_in[p->vex];
					p = p->next;
				}
			}

			//����������飬�����Ϊ0�Ķ�����뵽ջ��
			for(int i = 0; i < m_g.get_vex_num(); ++i)
			{
				cout << "i:" << i << ", " << m_in[i] << endl;
				if(m_in[i] == 0)
				{
					m_node.push(i);
				}
			}
		}
	}
	
	return true;
}

void TopoSort::sort()
{
	//������Ϊ0�Ķ���ջ���գ�ջ����ջ�����뵽��������������
	//�������ڽӶ���������ȥ��ȣ��������Ϊ0�Ķ�����ջ
	Node* p = NULL;
	Vertex* v = NULL;
	int i = 0;
	while(!m_node.empty())
	{
		++m_count;
		i = m_node.top();
		m_node.pop();
		
		m_list.push_back(i);

		v = m_g.get_vex(i);
		p = v->first;
		while(p)
		{
			--m_in[p->vex];
			if(m_in[p->vex] == 0)
			{
				m_node.push(p->vex);
			}

			p = p->next;
		}
	}
	if(m_count < m_g.get_vex_num())
	{
		cout << "error, graph has circle." << endl;
	}
	else
	{
		cout << "topo list:";
		print();
	}
	return;
}

void TopoSort::print()
{
	list<int>::iterator it = m_list.begin();
	list<int>::iterator end = m_list.end();
	while(it != end)
	{
		cout << m_g.locate_vex(*it) << " ";
		++it;
	}
	cout << endl;
	return;
}

class CirticalPath
{
public:
	bool init();
	void find_path();
private:
	GraphAdjTable m_g;
	stack<int> m_node;//���Ϊ0�Ķ���
	int m_in[MAX_VEX_NUM];//��¼ÿ������Ķ�
	list<int> m_list;//��¼������������
	int m_count;//�ж��Ƿ��л�
	stack<int> m_topo_stack;//��¼���������������ڼ���vlֵ
	int m_ve[MAX_VEX_NUM];//�洢ve��ֵ
	int m_vl[MAX_VEX_NUM];//�洢vl��ֵ
};

bool CirticalPath::init()
{
	//��ʼ��ve��vl
	for(int i = 0; i < MAX_VEX_NUM; ++i)
	{
		m_ve[i] = 0;
		m_vl[i] = 0;
		m_in[i] = 0; //��ʱ����ʱ����Ϊû�г�ʼ�����´���
	}

	m_count = 0;

	//����ͼ
	if(m_g.init())
	{
		if(m_g.create())
		{
			Vertex* v = NULL;
			Node* p = NULL;
			for(int i = 0; i < m_g.get_vex_num(); ++i)
			{
				v = m_g.get_vex(i);
				p = v->first;
				while(p)
				{
					++m_in[p->vex];
					p = p->next;
				}
			}

			//�����Ϊ0�Ķ�����뵽ջ��
			for(int i = 0; i < m_g.get_vex_num(); ++i)
			{
				if(m_in[i] == 0)
				{
					m_node.push(i);
				}
			}
		}
	}
	return true;
}

void CirticalPath::find_path()
{
	//ջ��Ϊ�գ���ջ��ȡ��ջ�����㣬�뵽vl����ջ��m_list�У� �������������
	//��С���ǵ����, ����veֵ
	Vertex* v = NULL;
	Node* p = NULL;
	int i = 0;
	while(!m_node.empty())
	{
		++m_count;
		i = m_node.top();
		m_node.pop();

		m_list.push_back(i);
		m_topo_stack.push(i);

		v = m_g.get_vex(i);
		p = v->first;
		while(p)
		{
			//�������
			--m_in[p->vex];
			if(m_in[p->vex] == 0)
			{
				m_node.push(p->vex);
			}

			//����veֵ����ʼveֵ��Ϊ0��veֵȥ���ֵ
			if(p->weight + m_ve[i] > m_ve[p->vex])
			{
				m_ve[p->vex] = p->weight + m_ve[i];
			}

			//�ƶ�ָ��
			p = p->next;
		}
		
	}
	if(m_count < m_g.get_vex_num())
	{
		cout << "error, graph has circle." << endl;
		return;
	}
	//����vlֵ
	//��ʼ�����е�vlֵΪ�ս�ڵ��veֵ
	int last_vex = m_topo_stack.top();
	for(int i = 0; i < m_g.get_vex_num(); ++i)
	{
		m_vl[i] = m_ve[last_vex];
	}

	//����topo���е����򣬱���ÿһ������Ĺ�����������vlֵ
	while(!m_topo_stack.empty())
	{
		i = m_topo_stack.top();
		v = m_g.get_vex(i);
		m_topo_stack.pop();
		p = v->first;
		while(p)
		{
			//��δ��������vlֵ�Ĺؼ������Խ��ͼ��������
			if(m_vl[p->vex] - p->weight < m_vl[i])
			{
				m_vl[i] = m_vl[p->vex] - p->weight;
			}
			//�ƶ�ָ��
			p = p->next;
		}
	}

	//�жϹؼ�·��������ӡ
	int e = 0;
	int l = 0;
	for(int i = 0; i < m_g.get_vex_num(); ++i)
	{
		v = m_g.get_vex(i);
		p = v->first;
		e = m_ve[i];
		while(p)
		{
			//�ж��Ƿ�Ϊ�ؼ�·��
			l = m_vl[p->vex] - p->weight;
			if(e == l)
			{
				cout << "(" << m_g.locate_vex(i) << ", " << m_g.locate_vex(p->vex) << ", " << p->weight << ")" << endl;
			}
			//�ƶ�ָ��
			p = p->next;
		}
	}

	return;
}


int main(int argc, char** argv)
{
	CirticalPath cp;
	if(cp.init())
	{
		cp.find_path();
	}
	return 0;
}

