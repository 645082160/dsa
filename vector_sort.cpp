#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


struct node{
	int x;
	int y;
	char c;
};

void print(vector<node>& t)
{
	vector<node>::iterator it = t.begin();
	vector<node>::iterator end = t.end();

	while(it != end)
	{
		cout << "(" << it->x << "," << ", " << it->y << ", " << it->c << ") ";
		++it;
	}

	cout << endl;
	return;
}

bool mycompare(node x, node y)
{
	return x.x != y.x ? x.x > y.x : x.y < y.y;
}

bool mycompare1(node x, node y)
{
	return x.x != y.x ? x.x < y.x : x.y < y.y;
}
int main(int argc, char** argv)
{
	vector<node> test;
	node n;
	n.x = 1;
	n.y = 3;
	n.c = '1';
	test.push_back(n);
	n.x = 1;
	n.y = 4;
	n.c = '2';
	test.push_back(n);
	n.x = 0;
	n.y = 3;
	n.c = '0';
	test.push_back(n);


	print(test);
	sort(test.begin(), test.end(), mycompare1);

	print(test);
	return 0;
}
