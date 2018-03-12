#include <iostream>
using namespace std;

int sum(int start, int end)
{
	//平凡情况
	if(start == end)
	{
		return start;
	}

	//减小问题规模，并求解
	int mid = (start + end) /2;

	int half1 = sum(start, mid);
	int half2 = sum(mid + 1, end);

	//获得本层结果
	int curr = half1 + half2;

	//向上返回本层结果
	return curr;
}


int main(int argc, char** argv)
{
	int number = 0;
	cout << "please input a number:";
	cin >> number;

	int res = 0;

	res = sum(1, number);

	cout << res << endl;

	return 0;
}
