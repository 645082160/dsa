#include<iostream>  
using namespace std;  
int main(int argc, char** argv)  
{  
    int N;//人的总个数  
    int M;//间隔多少个人  
  
    cin>>N;  
    cin>>M;  
    int result=0;//N=1情况  
    for (int i=2; i<=N; i++)  
    {  
        result=(result+M)%i;  
    }  
    cout<<"最后自杀的人是："<<result+1<<endl;//result要加1  
    return 0;  
} 