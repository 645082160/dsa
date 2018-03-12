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
	
 	// 1个计数器，记录当前所操作的节点
	int total = 2 * n - 1;
	int min1 = 0, min2 = 0; // 记录最小的2个权重值，min1最小，min2次小
	int lchild = -1, rchild = -1; // 记录左右子树下标
	for(int j = n; j < total; ++j)
	{
		cout << j << endl;
		min1 = 1000;
		min2 = 1000;
		lchild = -1;
		rchild = -1;
		for(int k = 0; k < j; ++k)
		{
			if(nodes[k].parent == -1) //表示该节点未被处理
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
	char value; //存放字符
	string code;// 存放编码
}code;

bool getcode(node nodes[], int n, code cds[])
{
	if(n <= 1)
	{
		cout << "n need >= 2" << endl;
		return false;
	}

	//遍历前n个叶子节点，根据其parent上溯至根节点得到其编码
	char c[n + 1];
	int pos = 0;

	int curr_node = 0;
	int code_len = 0;
	for(int i = 0; i < n; ++i)// 处理前n个叶子节点
	{
		// pos指向工作空间的最后一个位置，并初始化为\0
		pos = n;
		c[pos] = '\0';
		--pos;

		// 根据parent开始回溯直到根节点
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
		code_len = n - pos - 1; //编码长度要去掉末尾的\0
		++pos;//回退一个位置指向编码的第一个字符
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
