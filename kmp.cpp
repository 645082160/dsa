#include <iostream>
#include <cstring>
using namespace std;

//�����ⷨ
void voilentMath(char* s, char* p)
{
	if(s == NULL || p == NULL)
	{
		cout << "input error, pointer is NULL." << endl;
		return;
	}
	// 2����������¼����λ��
	int s_size = strlen(s);
	int p_size = strlen(p);

	if(s_size <= 0 || p_size <= 0 || s_size < p_size)
	{
		cout << "size error" << endl;
		return;
	}

	int i = 0, j = 0;
	while(i < s_size && j < p_size)
	{
		//���
		if(s[i] == p[j])
		{
			++i;
			++j;
		}
		else
		{
			i = i - j +1;
			j = 0;
		}
	}

	if(j == p_size)
	{
		cout << "pos: " << i - j << " " << *(s+i - j) << endl;
		return;
	}

	cout << "no pos find." << endl;

	return;
}

int next[10] = {0};
void print(int * next)
{
	if(next == NULL)
	{
		cout << "next array is NULL" << endl;
		return;
	}

	for(int i = 0; i < 10; ++i)
	{
		cout << *(next + i) << " ";
	}

	cout << endl;
	return;
}
void makenext(char* p)
{
	if(p == NULL)
	{
		cout << "p is NULL" << endl;
		return;
	}
	//��������ɨ���ַ���
	int i = 0;
	int k = 0; //k��¼ǰһ���ַ����ǰ��׺ƥ�䳤��

	int size = strlen(p);
	if(size <= 0)
	{
		cout << "size error" << endl;
		return;
	}
	
	//��һ���ַ��ƥ��Ϊ0
	next[0] = 0;

	for(i= 1, k = 0; i < size; ++i)
	{
		while(k > 0 && p[i] != p[k])
		{
			k = next[k - 1];//�����0��ʼ����������Խ��K-1���ַ�
		}

		if(p[i] == p[k])
		{
			++k;
		}

		next[i] = k;
	}

	print(next);
	return;
}

void kmp(char* s, char* p)
{
	//�������
	if(s == NULL || p == NULL)
	{
		cout << "s or p is NULL" << endl;
		return;
	}

	int size_s = strlen(s);
	int size_p = strlen(p);
	if(size_s <= 0 || size_p <= 0)
	{
		cout << "size error" << endl;
		return;
	}

	makenext(p);
	
	//��������ɨ�裬��Ҫ2��������

	//��ƥ��ʱ��s�����������䣬p���������޸�Ϊ��ǰλ�õ�nextֵ
	int i = 0, j = 0;
	while(i < size_s && j < size_p)
	{
		//���ʱ������ǰ��
		if(s[i] == p[j])
		{
			++i;
			++j;
		}
		else
		{
			//�����ʱ���޸�ģʽ��������
			if(j == 0)
			{
				++i;
			}
			else
			{
				j = next[j - 1];
			}
		}
		cout << "i: " << i << ", j: " << j << endl;
	}

	if(j == size_p)
	{
		cout << "find pos:" << i - j << " " << *(s+i - j) << endl;
		return;
	}
	else
	{
		cout << "no pos." << endl;
	}
	
	return;
}

int kmp_v1(char T[],char P[])
{
    int n,m;
    int i,q;
    n = strlen(T);
    m = strlen(P);
    makenext(P);

    for (i = 0,q = 0; i < n; ++i)
    {
        while(q > 0 && P[q] != T[i])
            q = next[q-1];
        if (P[q] == T[i])
        {
            q++;
        }
        if (q == m)
        {
        	cout << "i: " << i << ", m: " << m << ", q:" << q << endl;
         	cout << "Pattern occurs with shift:" << (i-m+1) << endl; 
        }
    }    
	return 0;
}
int main(int argc, char** argv)
{
	char* s = "BBC ABCDAB ABCDABCDABDE";
	char* p = "ABCDABD";

	cout << "s:" << s << endl;
	cout << "p:" << p << endl;
	cout << "violent Match:" << endl;
	voilentMath(s, p);

	cout << "kmp match: " << endl;
	kmp(s, p);

	kmp_v1(s, p);
	
	return 0;
}
