#include <iostream>
using namespace std;

class CMyString
{
public:
	CMyString(char* pData = NULL);
	CMyString(const CMyString& str);
	~CMyString();

	CMyString& operator=(const CMyString& str);

private:
	char* m_pData;
};
CMyString::CMyString(char* pData)
{
	m_pData = pData;
}

CMyString::CMyString(const CMyString& str)
{
	m_pData = str.m_pData;
}

CMyString::~CMyString()
{
	cout << "CMyString Destruct!" << endl;
}

CMyString& CMyString::operator=(const CMyString& str)
{
	if(this == &str)
	{
		return *this;
	}
	m_pData = str.m_pData;

	return *this;
}

int main(int argc, char** argv)
{
	CMyString str;
	CMyString s1;
	str = s1;
	return 0;
}



