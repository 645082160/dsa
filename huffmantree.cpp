#include <iostream>
#include <string>
using namespace std;

typedef struct HuffmanTreeNode
{
	char value;
	int weight;
	int lchild;
	int rchild;
	int parent;
}node;

bool init(node nodes[], int n)
{
	if(n <= 1)
	{
		cout << "n need >= 2!" << endl;
		return false;
	}

	int total = 2 * n - 1;
	for(int i = 0; i < total; ++i)
	{
		nodes[i].value = -1;
		nodes[i].weight = -1;
		nodes[i].lchild = nodes[i].rchild = nodes[i].parent = -1;
	}

	for(int i = 0; i < n; ++i)
	{
		cout << "input value:";
		cin >> nodes[i].value;
		cout << "input weight:";
		cin >> nodes[i].weight;
	}

	return true;
}
void printNodes(node nodes[], int n)
{
	int total = 2 * n - 1;
	for(int i = 0; i < total; ++i)
	{
		cout << "i:" << i << ", value:" << nodes[i].value << ", weight:" << nodes[i].weight  << ", lchild:" << nodes[i].lchild << ", rchild:" << nodes[i].rchild << ", parent:" << nodes[i].parent << endl;
	}

	return;
}
void createHuffmanTree(node nodes[], int n)
{
	if(n <= 1)
	{
		cout << "n needs >= 2!" << endl;
		return;
	}

	cout << "n=" << n << endl;
	cout << "2n-1=" << 2*n - 1 << endl;
	
 	// 1������������¼��ǰ�������Ľڵ�
	int total = 2 * n - 1;
	int min1 = 0, min2 = 0; // ��¼��С��2��Ȩ��ֵ��min1��С��min2��С
	int lchild = -1, rchild = -1; // ��¼���������±�
	for(int j = n; j < total; ++j)
	{
		cout << j << endl;
		min1 = 1000;
		min2 = 1000;
		lchild = -1;
		rchild = -1;
		for(int k = 0; k < j; ++k)
		{
			if(nodes[k].parent == -1) //��ʾ�ýڵ�δ������
			{
				if(nodes[k].weight < min1)
				{
					min2 = min1;
					min1 = nodes[k].weight;
					rchild = lchild;
					lchild = k;
				}
				else if(nodes[k].weight < min2)
				{
					min2 = nodes[k].weight;
					rchild = k;
				}
			}
		}

		cout << "lchild:" << lchild << ", rchild:" << rchild << endl;
		printNodes(nodes, n);
		nodes[lchild].parent = j;
		nodes[rchild].parent = j;
		nodes[j].weight = nodes[lchild].weight + nodes[rchild].weight;
		nodes[j].value = 't';
		nodes[j].lchild = lchild;
		nodes[j].rchild = rchild;
	}
	return;
}

typedef struct huffmancode
{
	char value; //����ַ�
	string code;// ��ű���
}code;

bool getcode(node nodes[], int n, code cds[])
{
	if(n <= 1)
	{
		cout << "n need >= 2" << endl;
		return false;
	}

	//����ǰn��Ҷ�ӽڵ㣬������parent���������ڵ�õ������
	char c[n + 1];
	int pos = 0;

	int curr_node = 0;
	int code_len = 0;
	for(int i = 0; i < n; ++i)// ����ǰn��Ҷ�ӽڵ�
	{
		// posָ�����ռ�����һ��λ�ã�����ʼ��Ϊ\0
		pos = n;
		c[pos] = '\0';
		--pos;

		// ����parent��ʼ����ֱ�����ڵ�
		curr_node = i;
		while(nodes[curr_node].parent != -1)
		{
			if(nodes[nodes[curr_node].parent].lchild == curr_node)
			{
				c[pos] = '0';
				--pos;
			}
			else if(nodes[nodes[curr_node].parent].rchild == curr_node)
			{
				c[pos] = '1';
				--pos;
			}
			else
			{
				cout << "invalid huffman tree, curr_node:" << curr_node << endl;
				return false;
			}

			curr_node = nodes[curr_node].parent;
		}

		cds[i].value = nodes[i].value;
		code_len = n - pos - 1; //���볤��Ҫȥ��ĩβ��\0
		++pos;//����һ��λ��ָ�����ĵ�һ���ַ�
		cds[i].code.assign(&c[pos]);
		cout << "value:" << cds[i].value << ", code:" << cds[i].code << ", code_len:" << code_len << endl;
	}


	return true;
}

void preorder(int index, node nodes[])
{
	if(index == -1)
	{
		return;
	}

	cout << nodes[index].weight << endl;
	preorder(nodes[index].lchild, nodes);
	preorder(nodes[index].rchild, nodes);

	return;
}

void printcds(code cds[], int n)
{
	if(n <= 1)
	{
		cout << "n need >= 2" << endl;
		return;
	}

	for(int i = 0; i < n; ++i)
	{
		cout << cds[i].value << ": " << cds[i].code << endl;
	}

	return;
}
int main(int argc, char* argv[])
{
	int n = 0;
	cout << "input n:";
	cin >> n;
	node nodes[2 * n  - 1];
	if(!init(nodes, n))
	{
		cout << "init fail." << endl;
		return -1;
	}
	printNodes(nodes, n);
	createHuffmanTree(nodes, n);
	printNodes(nodes, n);

	cout << "preorder:" << endl;
	preorder(2 * n - 2, nodes);


	code cds[n];
	if(getcode(nodes, n, cds))
	{
		cout << "OK" << endl;
	}
	else
	{
		cout << "FAIL." << endl;
	}
	printcds(cds, n);
	
	
	return 0;
}
