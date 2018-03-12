#include <iostream>
#include <list>

using namespace std;


void print(list<int> s)
{
	if(s.size() == 0)
	{
		cout << "empty" << endl;
		return;
	}

	list<int>::iterator itr = s.begin();
	list<int>::iterator end = s.end();
	int size = s.size();
	int count = 0;
	while(itr != end)
	{
		cout << *itr;
		++itr;
		++count;
		if(count != size)
		{
			cout << ",";
		}
	}
	cout << endl;

	return;
}
/*
@param i 处理第i个元素
@param n 元素总个数
@ queue 存放当前层的子集数据
*/
void backtrace(int i, int n, int a[], list<int> s, int& sum)
{
	if(i >= n)
	{
		++sum;
		print(s);
		return;
	}

	//选择该元素
	s.push_back(a[i]);
	++i;
	backtrace(i, n, a, s, sum);
	//不选择该元素
	s.pop_back();
	backtrace(i, n, a, s, sum);
	return;
}
int main(int argc, char** argv)
{
	int a[3] = {1, 2, 3};
	int i = 0;
	list<int> s;
	int sum = 0;
	backtrace(i, sizeof(a)/sizeof(a[0]), a, s, sum);
	cout << "total subset count:" << sum << endl;
	return 0;
}
