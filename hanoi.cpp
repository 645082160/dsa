#include <iostream>
using namespace std;

void move(int n, const char x, const char z)
{
	cout << "move " << n << " from " << x << " to " << z << endl;
	return;
}
void hanoi(int n, const char x, const char y, const char z)
{
	if(n == 1)
	{
		move(1, x, z);
	}
	else
	{
		hanoi(n-1, x, z, y);
		move(n, x, z);
		hanoi(n-1, y, x, z);
	}

	return;
}

int main(int argc, char** argv)
{
	
	int n = 0;

	while(true)
	{
		cout << "input n:";
		cin >> n;
		if(n > 0)
		{
			break;
		}
		n = 0;
	}

	hanoi(n, 'x', 'y', 'z');

	return 0;
}
