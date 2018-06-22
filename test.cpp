#include <iostream>
#include <climits>
using namespace std;

int MAX = INT_MAX;
int MIN = INT_MIN;

int main(int argc, char** argv)
{
	cout << MAX << ", " << MIN << endl;

	int my_max = 0x7fffffff;
	cout << my_max << endl;

	int my_min = 0x80000000;
	cout << my_min << endl;


	int test = 0xFFFFFFFB;
	cout << test << endl;
	return 0;
}