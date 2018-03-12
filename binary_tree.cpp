#include <iostream>
#include <cmath>
using namespace std;

struct binary_tree_array{
	int* root;
	int size;
};

void init_binary_tree_array(int n, binary_tree_array& tree)
{
	if(n <= 0)
	{
		cout << "total elem error" << endl;
		return;
	}

	tree.size = n;
	tree.root = new int[n + 1];
	
	return;
}

void input_binary_tree_array(binary_tree_array& tree, int sub)
{
/*
	if(tree.size <= 0 || tree.root == NULL)
	{
		cout << "invalid tree struct" << endl;
		return false;
	}

	int i = 1;//第一个元素不适用，方便数组下标和编号一致
	int elem = 0;
	while(i <= tree.size)
	{
		//0 表示该元素未被占用
		cout << "input " << i << " elem:";
		cin >> tree.root[i];
		++i;
	}

	cout << "input over" << endl;

	return true;
*/
	//cout << "sub:" << sub << endl;
	if(sub > tree.size)
	{
		return;
	}
	int elem = 0;
	cin >> elem;

	tree.root[sub] = elem;
	if(elem == 0)
	{
		return;
	}
	
	input_binary_tree_array(tree, 2 * sub);
	input_binary_tree_array(tree, 2 * sub + 1);
	
	return;
}

//这是先序遍历
void print_v1(binary_tree_array& tree, int sub)
{
	if(sub > tree.size)
	{
		return;
	}

	if(tree.root[sub] == 0)
	{
		return;
	}

	cout << tree.root[sub] << endl;
	print_v1(tree, 2 * sub);
	print_v1(tree, 2 * sub + 1);

	return;
}
void print_binary_tree_array(binary_tree_array& tree)
{
	double depth = 1;//层数
	double max = 0;//本层最大的编号
	double i = 0;
	double max_elem_num = 0;
	double k = 1;
	while(true)
	{
		max_elem_num = pow(2, k) - 1;
		if(max_elem_num >= tree.size)
		{
			break;
		}
		++k;
	}
	double max_depth_elem_num = pow(2, k - 1);
	cout << "k:" << k << endl;
	int max_print_len = max_depth_elem_num * 5;
	int curr_print_len = 0;
	int curr_level_num = 0;
	int j = 0;
	while(true)
	{	
		max = pow(2, depth) - 1;
		curr_level_num = pow(2, depth - 1);
		curr_print_len = max_print_len / (curr_level_num + 1);
		cout << "curr_level_num: " << curr_level_num << ", curr_print_len:" << curr_print_len << endl;
		i = pow(2, depth - 1);
		while(i <= max && i <= tree.size)
		{
			for(j = 0; j < curr_print_len; ++j)
			{
				cout << " ";
			}
			cout << tree.root[(int)i];
			++i;
		}
		cout << endl;
		++depth;
		
		if(i > tree.size)
		{
			break;
		}
	}

	return;
}
void test_binary_tree_array()
{
	int n = 0;

	while(true)
	{
		cout << "input total n:";
		cin >> n;
		if(n <= 0)
		{
			cout << "n need >= 1" << endl;
		}
		else
		{
			break;
		}

		n = 0;
	}	

	binary_tree_array tree;
	init_binary_tree_array(n, tree);

	/*
	bool res = input_binary_tree_array(tree);
	if(res)
	{
		print_binary_tree_array(tree);
	}
	*/

	input_binary_tree_array(tree, 1);

	cout << "output tree:" << endl;
	print_v1(tree, 1);
	
	return;
}
int main(int argc, char** argv)
{
	
	test_binary_tree_array();
	
	return 0;
}
