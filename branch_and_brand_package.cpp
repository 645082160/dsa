/*
��������:
01��������
n=3��w={20,15,15}, p={40,25, 25}, c = 30 n��ʾ��Ʒ������w��ʾÿ����Ʒ����
p��ʾÿ����Ʒ��ֵ��c��ʾ��������װ����Ʒ������
�����װ�����ϼ���ֵ
ʹ�÷�֧���� FIFO��չ��ѡȡ����
*/
#include <iostream>
#include <queue>
#include <vector>
#include <list>
using std::cout;
using std::endl;
using std::cin;
using std::priority_queue;
using std::vector;
using std::list;

class PackageBranchAndBound
{
public:
	struct node
	{
		int step;
		int total_w;
		int total_p;
		list<int> container;//װ����Ʒ�����
	};
	bool init();//��������
	void find_fifo();//��֧��������
	void find_priorityq();//���ȶ��з�֧��չ��ʽ��price������
private:
	void print(node& res);//��ӡ���
	struct local_compare{
		bool operator()(node& left, node& right)
		{
			return left.total_p < right.total_p;
		}
	};
private:	
	int m_n;//����Ʒ����
	int* m_w;//��������
	int* m_p;//��ֵ����
	int m_c;//�����������
};


bool PackageBranchAndBound::init()
{
	cout << "input obj num:";
	cin >> m_n;
	cout << "input package volumn:";
	cin >> m_c;

	cout << "input weight of objs:";
	m_w = new int[m_n];
	for(int i = 0; i < m_n; ++i)
	{
		cin >> m_w[i];
	}

	cout << "input price of objs:";
	m_p = new int[m_n];
	for(int i = 0; i < m_n; ++i)
	{
		cin >> m_p[i];
	}

	return true;
}

void PackageBranchAndBound::find_fifo()
{
	//FIFO ��չ�ڵ�ѡ��ʽ
	list<node> nodeset;
	//��Ե�һ���ڵ㣬���������з�֧�������������ж��Ƿ�Ҫ����list��
	node node1;
	//�����һ����Ʒ
	if(m_c >= m_w[0])
	{
		node1.step = 0;
		node1.total_w = m_w[0];
		node1.total_p = m_p[0]; 
		node1.container.push_back(0);
		nodeset.push_back(node1);
	}

	//���ŵ�һ����Ʒ
	node1.step = 0;
	node1.total_w = 0;
	node1.total_p = 0; 
	node1.container.clear();
	nodeset.push_back(node1);

	//ѭ��������ֱ����ڵ㼯��Ϊ��
	node e_node;
	node tmp_node;
	int tmp_step = 0;
	while(!nodeset.empty())
	{
		//FIFO���򣬻����չ�ڵ�
		e_node = nodeset.front();
		nodeset.pop_front();
		tmp_step = e_node.step + 1;
		//�жϵ�ǰ�ڵ��Ƿ��Ѿ��ǽ��
		if(tmp_step >= m_n)
		{
			if(e_node.total_p != 0)
			{
				cout << "find res:" << endl;
				print(e_node);
			}
			
			continue;
		}
		//ѡ��ǰ�ڵ�Ϊ��չ�ڵ㣬�������֧�ڵ㣬
		//������֧�ڵ���뵽��ڵ㼯��
		//װ��������
		if(m_c >= e_node.total_w + m_w[tmp_step])
		{
			tmp_node.step = tmp_step;
			tmp_node.total_w = e_node.total_w + m_w[tmp_step];
			tmp_node.total_p = e_node.total_p + m_p[tmp_step];
			tmp_node.container = e_node.container;
			tmp_node.container.push_back(tmp_step);

			nodeset.push_back(tmp_node);
		}

		//��ѡ���֧������б���
		++e_node.step;
		nodeset.push_back(e_node);
	}
	
	return;
}


void PackageBranchAndBound::find_priorityq()
{
	priority_queue<node, vector<node>, local_compare> nodeset; //���ȼ����У�price�����������У�topȡ���һ��
	//��ʼ�����Ӹ��ڵ㿪ʼ����֧���뵽���ȶ�����
	node tmp_node;
	int tmp_step = 0;

	//�����һ����Ʒ
	if(m_c >= m_w[tmp_step])
	{
		tmp_node.step = tmp_step;
		tmp_node.total_w = m_w[tmp_step];
		tmp_node.total_p = m_p[tmp_step];
		tmp_node.container.push_back(tmp_step);

		nodeset.push(tmp_node);
	}

	//���ŵ�һ����Ʒ
	tmp_node.step = tmp_step;
	tmp_node.total_w = 0;
	tmp_node.total_p = 0;
	tmp_node.container.clear();
	nodeset.push(tmp_node);

	//�����ȶ��в���ʱ���������ӣ�ֱ���ҵ���һ���������ӡ����˳�
	node e_node;
	while(!nodeset.empty())
	{
		//������ȼ�����Ԫ�أ������У�����Ϊ��չ�ڵ�
		e_node = nodeset.top();
		nodeset.pop();
		cout << "pop :(" << e_node.total_p << ", " << e_node.total_w << ", " << e_node.step << endl;
		tmp_step = e_node.step + 1;
		if(tmp_step >= m_n)
		{
			cout << "meet leaf:(" << e_node.total_p << ", " << e_node.total_w << ",";
			list<int>::iterator it = e_node.container.begin();
			list<int>::iterator end = e_node.container.end();
			while(it != end)
			{
				cout << *it << " ";
				++it;
			}
			cout << ")" << endl;
			
			/*
			if(e_node.total_p > 0)
			{
				print(e_node);
			}
			*/
			continue;
		}
		
		//�����֧
		if(m_c >= e_node.total_w + m_w[tmp_step])
		{
			tmp_node.step = tmp_step;
			tmp_node.total_p = e_node.total_p + m_p[tmp_step];
			tmp_node.total_w = e_node.total_w + m_w[tmp_step];
			
			tmp_node.container.clear();
			tmp_node.container = e_node.container;
			tmp_node.container.push_back(tmp_step);
			
			nodeset.push(tmp_node);
		}

		//��������������Ʒ����� 
		++e_node.step;
		nodeset.push(e_node);
	}
	
}
void PackageBranchAndBound::print(node& res)
{
	cout << "total weight:" << res.total_w << endl;
	cout << "total price:" << res.total_p << endl;
	cout << "obj list:";
	list<int>::iterator it = res.container.begin();
	list<int>::iterator end = res.container.end();
	while(it != end)
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	return;
}


int main(int argc, char** argv)
{

	PackageBranchAndBound p;
	
	p.init();
	p.find_fifo();


	cout << endl;
	p.find_priorityq();
	
	return 0;
}

