#include <iostream>
using namespace std;
int sum(int left)
{
	//平凡的情况
	if(left == 1)
	{
		return 1;
	}

	//求解规模减小后的问题的解
	int lower_level = sum(left - 1);

	//利用下一层的结果，求解本层的结果
	int curr = left + lower_level;
	return curr;//返回本层的结果
}
int main(int argc, char** argv)
{
	int end = 0;
	int total = 0;

	cout << "please input a number:";
	cin >> end;
	
	total = sum(end);
	cout << total << endl;

	return 0;
}
