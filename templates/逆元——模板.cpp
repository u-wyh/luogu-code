//����ļ�������������Ԫ��
//������������Ԫ
//�������ֵ���Ԫ
//�������ֽ׳���Ԫ
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n,m,mod;
int inv[MAXN];//�������ֵ���Ԫ
int fac[MAXN];//�������ֵĽ׳�
int facinv[MAXN];//�������ֽ׳˵���Ԫ

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

//������������Ԫ
//����С������(a/b)%mod��ֵ
long long compute(long long a,long long b,long long mod){
    long long inv=power(b,mod-2,mod);//��b��%mod������µ���Ԫ
    return (a*inv)%mod;
}

//�������ֵ���Ԫ
// Ԥ����ģ��Ԫ
void build(int n) {
    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = (mod - (long long)inv[mod % i] * (mod / i) % mod + mod) % mod;
    }
}

//�������ֽ׳˵���Ԫ
// ��ʼ���׳˱����Ԫ��
void build() {
    //������׳˱�
    fac[0] = 1; // 0! = 1
    for (int i = 1; i <= n; i++) {
        fac[i] = (fac[i - 1] * i) % mod;
    }

    // �������Ե����Ż�������Ԫ
    facinv[n] = power(fac[n], mod - 2,mod);//������һ�����ֵĽ׳���Ԫ
    for (int i = n - 1; i >= 0; i--) {
        facinv[i] = (facinv[i + 1] * (i + 1)) % mod;//���Ե���
    }
}

int main()
{
    cin>>n>>m>>mod;
    compute(n,m,mod);
    build(n);
    build();
    return 0;
}
