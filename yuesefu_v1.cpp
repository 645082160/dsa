#include<iostream>  
using namespace std;  
int main(int argc, char** argv)  
{  
    int N;//�˵��ܸ���  
    int M;//������ٸ���  
    int k;//�ӱ��Ϊ���ٵ��˿�ʼ��������0��ʼ���

    cout << "input n and m:";
    cin>>N;  
    cin>>M;  
    cout << "input k:";
    cin >> k;//�ӵڼ����˿�ʼ����
    int result=0;//N=1���  
    for (int i=2; i<=N; i++)  
    {  
        result=(result+M)%i;  
    }  
    cout<<"from 1, last over:"<<result+1<<endl;//resultҪ��1  
    //����ӱ��ΪK�Ŀ�ʼ��������ô������Ƕ�����?
    /*
    ���Ǽ����˴ӱ��Ϊ0�Ŀ�ʼ��
    */
    
   cout << "from " << k << " last over:" << (result +1 + k - 1)%N << endl;
    return 0;  
} 