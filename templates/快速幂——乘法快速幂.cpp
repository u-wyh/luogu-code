// �˷�������ģ��
// ��a��b�η�����pȡģ�Ľ��
// �������� : https://www.luogu.com.cn/problem/P1226
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;

long long power(long long a,long long b,long long mod){
    long long ans=1;
    while(b>0){
        if(b&1){
            ans=(ans*a)%mod;
        }
        a=(a*a)%mod;//aÿ���൱�ڱ���  ֻ��b����һλ����1��ʱ�� �ŻὫa�˽�ans��
        b>>=1;//b�����ƶ�һλ
    }
    return ans;
}

int main()
{
    long long a,b,mod;
    cin>>a>>b>>mod;
    cout<<a<<"^"<<b<< " mod "<<mod<<"="<<power(a,b,mod)<<endl;
    return 0;
}
