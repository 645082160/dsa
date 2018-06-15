#include<iostream>  
using namespace std;  
int main(int argc, char** argv)  
{  
    int N;//人的总个数  
    int M;//间隔多少个人  
    int k;//从编号为多少的人开始报数，从0开始编号

    cout << "input n and m:";
    cin>>N;  
    cin>>M;  
    cout << "input k:";
    cin >> k;//从第几个人开始报数
    int result=0;//N=1情况  
    for (int i=2; i<=N; i++)  
    {  
        result=(result+M)%i;  
    }  
    cout<<"from 1, last over:"<<result+1<<endl;//result要加1  
    //如果从编号为K的开始报数，那么结果又是多少呢?
    /*
    我们假设了从编号为0的开始，
    */
    
   cout << "from " << k << " last over:" << (result +1 + k - 1)%N << endl;
    return 0;  
} 