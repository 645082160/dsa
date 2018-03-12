#include <iostream>
using namespace std;


enum ptag {LINK, THREAD};
struct bnode
{
	char value;
	bnode* left;
	ptag ltag;
	bnode* right;
	ptag rtag;
};

bnode* get_tree()
{
//	cout << "input elem:";
	char c;
	cin >> c;
	if(c == '#')
	{
		return NULL;
	}

	bnode* node = new bnode();
	node->value = c;
	node->ltag = LINK;
	node->left = NULL;
	node->rtag = LINK;
	node->right = NULL;


	node->left = get_tree();
	node->right = get_tree();

	return node;
}

void preorder(bnode* root)
{
	if(root == NULL)
	{
		return;
	}

	cout << root->value;
	preorder(root->left);
	preorder(root->right);

	return;
}

bnode* pre = NULL;
void preorder_thread(bnode* root)
{
	if(root == NULL)
	{
		return;
	}

	if(root != NULL &&  pre != NULL && root->left == NULL && root->ltag == LINK)
	{
		root->left = pre;
		root->ltag = THREAD;
	}

	if(pre != NULL && root != NULL && pre->right == NULL && pre->rtag == LINK)
	{
		pre->right = root;
		pre->rtag = THREAD;
	}

	pre = root;

	 //线索化，修改了当前节点的左子树
	if(root->left != NULL && root->ltag == LINK)
	{
		preorder_thread(root->left);
	}
	
	preorder_thread(root->right);
	
	return;
}

void preorder_thread_visit(bnode* root)
{
	if(root == NULL)
	{
		return;
	}

	bnode* p = root;//计数器
	while(p != NULL)
	{
		cout << p->value;
		if(p->left != NULL && p->ltag == LINK)
		{
			p = p->left;
		}
		else
		{
			while(p->right != NULL)
			{
				if(p->rtag == THREAD)
				{
					p = p->right;
					cout << p->value;
				}
				else
				{
					break;
				}
			}
			//先序遍历，某个节点的左子树和右子树都是没有访问过的
			//因此，存在左子树的情况下，需要访问左子树
			if(p->left != NULL && p->ltag == LINK)
			{
				p = p->left;
			}
			else
			{
				p = p->right;
			}
			
		}
	}

	cout << endl;
	
	return;
}

void inorder_thread(bnode* root)
{
	if(root == NULL)
	{
		return;
	}

	inorder_thread(root->left);

	if(root!= NULL && pre != NULL && root->left == NULL && root->ltag == LINK)
	{
		root->left = pre;
		root->ltag = THREAD;
	}

	if(root != NULL && pre != NULL && pre->right == NULL && pre->rtag == LINK)
	{
		pre->right = root;
		pre->rtag = THREAD;
	}

	pre = root;

	inorder_thread(root->right);

	return;
}

void inorder_thread_visit(bnode* root)
{
	if(root == NULL)
	{
		return;
	}

	bnode* p = root;
	while(p != NULL)
	{
		while(p->left != NULL && p->ltag == LINK)
		{
			p = p ->left;
		}

		cout << p->value;
		while(p->right != NULL)
		{
			if(p->rtag == THREAD)
			{
				p = p->right;
				cout << p->value;
			}
			else
			{
				break;
			}
		}

		p = p->right;
		
	}
	

	cout << endl;	
	return;
}

void inorder(bnode* root)
{
	if(root == NULL)
	{
		return;
	}

	inorder(root->left);
	cout << root->value;
	inorder(root->right);

	return;
}

void postorder(bnode* root)
{
	if(root == NULL)
	{
		return;
	}

	postorder(root->left);
	postorder(root->right);
	cout << root->value;

	return;
}

void postorder_thread(bnode* root)
{
	if(root == NULL)
	{
		return;
	}

	postorder_thread(root->left);
	postorder_thread(root->right);

	if(root!= NULL && pre != NULL && root->left == NULL && root->ltag == LINK)
	{
		root->left = pre;
		root->ltag = THREAD;
	}

	if(root != NULL && pre != NULL && pre->right == NULL && pre->rtag == LINK)
	{
		pre->right = root;
		pre->rtag = THREAD;
	}

	pre = root;

	return;
}

void postorder_thread_visit(bnode* root)
{
	if(root == NULL)
	{
		return;
	}

	bnode* p = root;
	while(p != NULL)
	{
		while(p->left != NULL && p->ltag == LINK)
		{
			p = p->left;
		}

		
		cout << p->value;
		while(p->right != NULL)
		{
			if(p->rtag == THREAD)
			{
				p = p->right;
				cout << p->value;
			}
			else
			{
				break;
			}
		}
		

		p = p->right;
	}
	
	return;
}
int main(int argc, char** argv)
{

	bnode* root = get_tree();
	if(root == NULL)
	{
		cout << "create tree fail." << endl;
		return -1;
	}

	cout << "preorder:";
	preorder(root);
	cout << endl;

	cout << "inorder:";
	inorder(root);
	cout << endl;

	cout << "postorder:";
	postorder(root);
	cout << endl;

	/*
	cout << "inorder_thread:" << endl;
	inorder_thread(root);
	cout << "over" << endl;

	cout << "inorder_thread_visit:" << endl;
	inorder_thread_visit(root);
	

	cout << "preorder_thread:" << endl;
	preorder_thread(root);
	cout << "over" << endl;

	cout << "preorder_thread_visit:" << endl;
	preorder_thread_visit(root);
	*/

	
	return 0;
}

