// ������������Ԫ
//���Բ��÷���С����  һ��������%mod������µ���Ԫ ����������ֵ�mod-2�η�  ��modȡ��Ľ��
// ��������֤
#include<bits/stdc++.h>
using namespace std;

//�˷�������  ��a��b�η���modȡ��
long long power(long long a,long long b,long long mod){
    long long ans=1;
    while(b){
        if(b&1){
            ans*=a;
            ans%=mod;
        }
        b>>=1;
        a*=a;
        a%=mod;
    }
    return ans;
}

//����С������(a/b)%mod��ֵ
long long compute2(long long a,long long b,long long mod){
    long long inv=power(b,mod-2,mod);//��b��%mod������µ���Ԫ
    return (a*inv)%mod;
}

//������
long long compute1(long long a,long long b,long long mod){
    return (a/b)%mod;
}

int main()
{
    long long a,b,mod;
    cin>>a>>b>>mod;
    // 1) ���뱣֤a/b��������
    // 2) ���뱣֤mod������
    // 3) ���뱣֤b��mod�����Լ��Ϊ1
    cout<<"��������֤�� "<<compute1(a,b,mod)<<endl;
    cout<<"����С���� "<<compute2(a,b,mod)<<endl;
    return 0;
}
/*
247143614256
3671613
41
*/
