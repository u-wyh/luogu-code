// ���ϼ���
// һ����n����ͬ�������ܹ���2^n����ͬ����
// ��2^n���������������ɸ����ϣ�������һ��
// ϣ�������ɸ����ϵĽ�����������k����
// ������ѡ���ϵķ��������𰸶� 1000000007 ȡģ
// 1 <= n <= 10^6
// 0 <= k <= n
// �������� : https://www.luogu.com.cn/problem/P10596
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int MOD = 1e9+7;

long long fac[MAXN];
long long inv[MAXN];
long long g[MAXN];
int n,k;

// �����ݼ��� a^b % MOD
long long power(long long a, int b) {
    long long ans = 1;
    a = a % MOD;
    while (b > 0) {
        if (b & 1) {
            ans = (ans * a) % MOD;
        }
        a = (a * a) % MOD;
        b >>= 1;
    }
    return ans;
}

// �����׳˱����Ԫ��
void build() {
    fac[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
    }
    inv[n]=power(fac[n],MOD-2);
    for (int i = n-1; i >= 1; i--) {
        inv[i] = (inv[i + 1] * (i + 1)) % MOD;
    }
}

// ��Ϲ�ʽ
long long c(int n, int k) {
    return (((fac[n] * inv[k]) % MOD) * inv[n - k]) % MOD;
}

long long compute() {
    build();
    long tmp = 2;
    for (int i = n; i >= 0; i--) {
        g[i] = tmp;
        tmp = tmp * tmp % MOD;
    }
    //�����ַ��ݷ���
    for (int i = 0; i <= n; i++) {
        // -1 �� (MOD-1) ͬ��
        g[i] = (g[i] + MOD - 1) * c(n, i) % MOD;
        //����ǻ�����
    }
    long ans = 0;
    for (int i = k; i <= n; i++) {
        //����iÿ������1  ����Ҫmod-1
        if (((i - k) & 1) == 0) {
            ans = (ans + c(i, k) * g[i] % MOD) % MOD;
        } else {
            // -1 �� (MOD-1) ͬ��
            ans = (ans + c(i, k) * g[i] % MOD * (MOD - 1) % MOD) % MOD;
        }
    }
    return ans;
}

int main()
{
    cin>>n>>k;
    cout<<compute()<<endl;
    return 0;
}
