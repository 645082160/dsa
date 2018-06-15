#include <iostream>
#include <stack>
#include <queue>
#include <cstdlib>
using namespace std;

typedef struct binary_tree_node
{
	char value;
	binary_tree_node* left;
	binary_tree_node* right;
}node;


node* init()
{
	node* tree = new node();
	tree->value = ' ';
	tree->left = NULL;
	tree->right = NULL;
	return tree;
}

void get_tree(node* & tree)
{
	char tmp;
	cout << "input elem:";
	cin >> tmp;

	if(tmp == '#')
	{
		return;
	}

	tree = new node();
	tree->value = tmp;
	tree->left = NULL;
	tree->right = NULL;

	get_tree(tree->left);
	get_tree(tree->right);

	return;
}

void preorder_print(node* tree)
{
	if(tree == NULL)
	{
		return;
	}

	cout << tree->value << endl;

	preorder_print(tree->left);
	preorder_print(tree->right);

	return;
}

void preorder_iteration(node* tree)
{
	if(tree == NULL)
	{
		cout << "empty tree" << endl;
		return;
	}
	//需要一个栈
	stack<node*> s;

	//栈初始化
	s.push(tree);
	cout << tree->value;

	node* tmp = NULL;
	while(!s.empty())
	{
		tmp = s.top();
		if(tmp->left != NULL)
		{
			cout << tmp->left->value;
			s.push(tmp->left);
		}
		else
		{
			//根节点出栈，访问右子树，此时需要循环处理
			s.pop();

			 
			while(true)
			{
				if(tmp->right != NULL)
				{
					cout << tmp->right->value;
					s.push(tmp->right);
					break;
				}
				if(s.empty())
				{
					break;
				}
				else
				{
					tmp = s.top();
					s.pop();
					
				}
			}
			
		}
	}

	cout << endl;
	return;
}

void preorder_iteration_v1(node* tree)
{
	if(tree == NULL)
	{
		cout << "empty tree" << endl;
		return;
	}

	/*
		下面这段代码真的很有意思，通过简单的修改while条件，
		就将沿着左子树往下，沿着右子树往下表现的非常到位
	*/
	stack<node*> s;
	node* tmp = tree;
	while(tmp != NULL || !s.empty())
	{
		if(tmp != NULL)
		{
			cout << tmp->value;
			s.push(tmp);
			tmp = tmp->left;
		}
		else
		{
			tmp = s.top(); 
			s.pop();
			tmp = tmp->right;
		}
	}

	cout << endl;
	return;
}


void infix_print(node* tree)
{
	if(tree == NULL)
	{
		return;
	}

	infix_print(tree->left);
	cout << tree->value << endl;
	infix_print(tree->right);

	return;
}

void infix_iteration(node* tree)
{
	if(tree == NULL)
	{
		cout << "empty tree" << endl;
		return;
	}
	//需要一个栈
	stack<node*> s;

	//栈初始化
	s.push(tree);

	node* tmp = NULL;
	while(!s.empty())
	{
		tmp = s.top();
		if(tmp->left != NULL)
		{
			s.push(tmp->left);
		}
		else
		{
			s.pop();
			cout << tmp->value << endl;

			while(true)
			{
				if(tmp->right != NULL)
				{
					s.push(tmp->right);
					break;
				}
				if(s.empty())
				{
					break;
				}
				else
				{
					tmp = s.top();
					s.pop();
					cout << tmp->value << endl;
				}
			}
		}
	}

	return;
}

void infix_iteration_v1(node* tree)
{
	if(tree == NULL)
	{
		cout << "empty tree" << endl;
		return;
	}

	stack<node*> s;
	node* tmp = tree;
	while(tmp != NULL || !s.empty())
	{
		if(tmp != NULL)
		{
			s.push(tmp);
			tmp = tmp->left;
		}
		else
		{
			tmp = s.top(); 
			cout << tmp->value << endl;
			s.pop();
			tmp = tmp->right;
		}
	}
	
	return;
}


void followup_print(node* tree)
{
	if(tree == NULL)
	{
		return;
	}

	followup_print(tree->left);
	followup_print(tree->right);
	cout << tree->value << endl;

	return;
}

struct node_wrap
{
	node* n;
	int time;
};

void followup_iteration(node* tree)
{
	if(tree == NULL)
	{
		cout << "empty tree" << endl;
		return;
	}
	//需要一个栈
	stack<node_wrap*> s;


	node* tmp = tree;
	node_wrap* nw= NULL;
	while(tmp != NULL || !s.empty())
	{
		if(tmp != NULL)
		{ 
			nw = new node_wrap();
			nw->n = tmp ;
			nw->time = 1
			s.push(nw);
			
			tmp = tmp->left;
		}
		else
		{
			nw = s.top();
			tmp = nw->n;
			if(tmp->time == 2) //第二次出栈，访问
			{
				cout << tmp->value;
				s.pop();
				tmp = NULL;
			}
			else
			{
				++nw->time;
				tmp = tmp->right;
			}
			
		}
	}
	/*
	node_wrap* nw = new node_wrap();
	nw->n = tree;
	nw->time = 0;
	//栈初始化
	//s.push(nw);
	node_wrap* tmp = NULL;
	
	
	while(!s.empty())
	{
		tmp = s.top();
		if(tmp->n->left != NULL)
		{
			nw = new node_wrap();
			nw->n = tmp->n->left;
			nw->time = 1;
			s.push(nw);
		}
		else
		{
			//左子树为NULL，表示从左子树返回
			++tmp->time; //当前根节点++
			if(tmp->n->right != NULL)
			{			
				nw = new node_wrap();
				nw->n = tmp->n->right;
				nw->time = 1;
				s.push(nw);
			}
			else
			{
				while(true)
				{
					if(tmp->time == 2)
					{
						cout << tmp->n->value;
						s.pop();
						if(s.empty())
						{
							break;
						}
						tmp = s.top();
					}
					else
					{
						++tmp->time;
						if(tmp->n->right != NULL)
						{
							nw = new node_wrap();
							nw->n = tmp->n->right;
							nw->time = 1;
							s.push(nw);
							break;
						}
					}
				}
				
			}
		}
	}	
	*/

	cout << endl;
	return;
}

void levelorder_print(node* tree)
{
	if(tree == NULL)
	{
		return;
	}

	queue<node*> q;
	q.push(tree);

	node* tmp = NULL;
	while(!q.empty())
	{
		tmp = q.front();
		q.pop();
		cout << tmp->value << endl;
		if(tmp->left != NULL)
		{
			q.push(tmp->left);
		}
		if(tmp->right != NULL)
		{
			q.push(tmp->right);
		}
	}

	return;
}

int get_optr_level(char optr)
{
	if(optr == '+' || optr == '-')
	{
		return 0;
	}
	else if(optr == '*' || optr == '/')
	{
		return 1;
	}

	return -1;
}

void get_tree(node* root, node* left, node* right)
{
	root->left = left;
	root->right = right;

	return;
}

node* createnode(char value)
{
	node* n = new node();
	n->value = value;
	n->left = NULL;
	n->right = NULL;

	return n;
}

bool is_optr(char c)
{
	return c == '+' || c== '-' || c == '*' || c == '/';
}

bool is_opnd(char c)
{
	return c <= 'z' && c >= 'a';
}

node* createTree()
{
	char c;
	stack<node*> optr, opnd;
	node* tmp = NULL;
	node* top_optr = NULL;
	node* right = NULL;
	node* left = NULL;
	cout << "input expression:" << endl;
	
	while(true)
	{
		cin >> c;
		if(c == '#')
		{
			cout << "input over" << endl;
			break;
		}
		if(is_optr(c)) //运算符
		{
			tmp = createnode(c);
			if(optr.empty()) //运算符栈为空
			{
				optr.push(tmp);
				tmp = NULL;
				continue;
			}
			
			while(true)
			{
				if(optr.empty())
				{
					optr.push(tmp);
					tmp = NULL;
					break;
				}
				
				top_optr = optr.top();
				//栈顶优先级低，则运算符入栈
				if(get_optr_level(top_optr->value) < get_optr_level(tmp->value))
				{
					optr.push(tmp);
					tmp = NULL;
					break;
				}
				//运算符栈不为空，则判断栈顶的运算符与当前运算符的优先级
				//栈顶优先级高，则先计算，再继续比较
				optr.pop();
				
				if(opnd.empty())
				{
					cout << "format error, " << __LINE__ << endl;
					return NULL;
				}
				right = opnd.top();
				opnd.pop();

				if(opnd.empty())
				{
					cout << "format error, " << __LINE__ << endl;
					return NULL;
				}
				left = opnd.top();
				opnd.pop();

				top_optr->left = left;
				top_optr->right = right;

				opnd.push(top_optr);
			}
		}
		else if(is_opnd(c)) //操作数
		{
			tmp = createnode(c);
			opnd.push(tmp);
		}
		else
		{
			cout << "invalid input, end!" << endl;
			return NULL;
		}
	}

	//扫描完毕，检查运算符栈是否为空，不为空需要计算
	while(!optr.empty())
	{
		top_optr = optr.top();
		optr.pop();

		if(opnd.empty())
		{
			cout << "format error, " << __LINE__ << endl;
			return NULL;
		}
		right = opnd.top();
		opnd.pop();

		if(opnd.empty())
		{
			cout << "format error, " << __LINE__ << endl;
			return NULL;
		}
		left = opnd.top();
		opnd.pop();

		top_optr->left = left;
		top_optr->right = right;

		opnd.push(top_optr);
	}

	node* root = opnd.top();
	opnd.pop();

	if(opnd.empty())
	{
		return root;
	}

	cout << "format error, " << __LINE__ << endl;

	return NULL;
}

node* parse(string inorder_list, string postorder_list, int& i)
{
	node* tmp = NULL;
	if(inorder_list.size() == 1)
	{
		node* tmp = new node();
		tmp->value = inorder_list[0];
		tmp->left = NULL;
		tmp->right = NULL;
		--i;
		return tmp;
	}

	if(inorder_list.size() == 0)
	{
		return NULL;
	}

	char c = postorder_list[i];
	--i;

	tmp = new node();
	tmp->value = c;

	size_t pos = inorder_list.rfind(c);
	if(pos ==  string::npos)
	{
		cout << "format error, i:" << i << ", c:" << c << ", inorder_list:" << inorder_list << endl;
		exit(-1);
	}

	string left = inorder_list.substr(0, pos);
	string right = inorder_list.substr(pos + 1);
	cout << "left:" << left << ", i:" << i << endl;
	cout << "right:" << right << ", i:" << i << endl;

	tmp->right = parse(right, postorder_list, i);
	tmp->left = parse(left, postorder_list, i);
	

	return tmp;
}






int main(int argc, char** argv)
{
	
	string postorder_list, inorder_list;

	cout << "input postorder list:";
	cin >> postorder_list;

	cout << "input inorder list:";
	cin >> inorder_list;

	int i = postorder_list.size() - 1;
	node* root = parse(inorder_list, postorder_list, i);

	cout << "preorder print: i:" << i << endl;
	preorder_print(root);


	cout << "infix_iteration:" << endl;
	infix_iteration(root);

	cout << "infix_iteration_v1:" << endl;
	infix_iteration_v1(root);

	cout << "preorder_iteration:" << endl;
	preorder_iteration(root);

	cout << "preorder_iteration_v1" << endl;
	preorder_iteration_v1(root);

	cout << "followup_iteration:" << endl;
	followup_iteration(root);
	return 0;
/*
	node* root = createTree();
	if(root == NULL)
	{
		cout << "create tree fail." << endl;
		return -1;
	}

	cout << "preorder:" << endl;
	preorder_print(root);

	cout << "postorder:" << endl;
	followup_print(root);

	cout << "levelorder:" << endl;
	levelorder_print(root);
	return 0;

	node* root = init();
	if(root == NULL)
	{
		cout << "init fail." << endl;
		return -1;
	}

	get_tree(root);

	cout << "input tree over, output tree:" << endl;
	cout << "pre order:" << endl;
	preorder_print(root);

	cout << "infix order:" << endl;
	infix_print(root);

	cout << "followup order:" << endl;
	followup_print(root);
	return 0;
*/
}
