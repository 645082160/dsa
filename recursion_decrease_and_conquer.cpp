#include <iostream>
using namespace std;
int sum(int left)
{
	//ƽ�������
	if(left == 1)
	{
		return 1;
	}

	//����ģ��С�������Ľ�
	int lower_level = sum(left - 1);

	//������һ��Ľ������Ȿ��Ľ��
	int curr = left + lower_level;
	return curr;//���ر���Ľ��
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
