// ����ϵ��
// ����ʽΪ��(ax + by)��k�η�������a��b��kΪ����
// �����������ʽչ����x��n�η� * y��m�η�����һ���ϵ��
// 0 <= k <= 1000
// 0 <= a��b <= 10^6
// n + m == k
// �������� : https://www.luogu.com.cn/problem/P1313
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MOD = 10007;

long long fac[1005];
long long inv[1005];

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
    fac[0] = 1;
    for (int i = 1; i <= 1005; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
    }
    inv[1005] = power(fac[1005], MOD - 2);
    for (int i = 1004; i >= 0; i--) {
        inv[i] = (inv[i + 1] * (i + 1)) % MOD;
    }
}

// ��Ϲ�ʽ
long long c(int n, int k) {
    return (((fac[n] * inv[k]) % MOD) * inv[n - k]) % MOD;
}


int main()
{
    int a,b,k,n,m;
    cin>>a>>b>>k>>n>>m;
    build();
    cout<<((((power(a, n) * power(b, m)) % MOD) * c(k, k - n)) % MOD)<<endl;
    return 0;
}
