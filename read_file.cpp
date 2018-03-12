#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		cout << "usage: " << argv[0] << " filename" << endl;
		return -1;
	}

	ifstream file(argv[1]);

	char buf[100] = {0};
	while(!file.eof())
	{
		file.getline(buf, sizeof(buf));
		cout << buf << endl;
	}

	file.close();
	
	return 0;
}

