#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using std::endl;
using std::cout;
using std::priority_queue;
using std::vector;
using std::sort;

struct compare
{
	bool operator()(int a, int b)
	{
		return a > b; //a 应该排在b之前
	}
};

struct compare_1
{
	bool operator()(int a, int b)
	{
		return a < b; //a 应该排在b之前
	}
};


bool com(int a, int b)
{
	return a > b;
}

int main(int argc, char** argv)
{
	priority_queue<int, vector<int>, compare> test;
	test.push(1);
	test.push(2);
	test.push(3);
	
	int val = 0;
	while(!test.empty())
	{
		cout << test.top() << endl;
		test.pop();
	}

	cout << endl;

	vector<int> tmp;
	tmp.push_back(1);
	tmp.push_back(2);

	sort(tmp.begin(), tmp.end(), com);
	vector<int>::iterator it = tmp.begin();
	vector<int>::iterator end = tmp.end();
	while(it != end)
	{
		cout << *it << endl;
		++it;
	}
	return 0;
}
