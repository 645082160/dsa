#include<iostream>  
using namespace std;  
int main(int argc, char** argv)  
{  
    int N;//�˵��ܸ���  
    int M;//������ٸ���  
  
    cin>>N;  
    cin>>M;  
    int result=0;//N=1���  
    for (int i=2; i<=N; i++)  
    {  
        result=(result+M)%i;  
    }  
    cout<<"�����ɱ�����ǣ�"<<result+1<<endl;//resultҪ��1  
    return 0;  
} 