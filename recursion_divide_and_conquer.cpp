#include <iostream>
using namespace std;

int sum(int start, int end)
{
	//ƽ�����
	if(start == end)
	{
		return start;
	}

	//��С�����ģ�������
	int mid = (start + end) /2;

	int half1 = sum(start, mid);
	int half2 = sum(mid + 1, end);

	//��ñ�����
	int curr = half1 + half2;

	//���Ϸ��ر�����
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
