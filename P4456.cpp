#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e7+5;

int n,m,a,b;

long long fac[MAXN];
long long inv[MAXN];

// 快速幂计算 a^b % MOD
long long power(long long a, int b) {
    long long ans = 1;
    a = a % m;
    while (b > 0) {
        if (b & 1) {
            ans = (ans * a) % m;
        }
        a = (a * a) % m;
        b >>= 1;
    }
    return ans;
}

// 构建阶乘表和逆元表
void build() {
    fac[0] = inv[0] = 1;
    for (int i = 1; i <= n+1; i++) {
        fac[i] = (fac[i - 1] * i) % m;
    }
    inv[n+1]=power(fac[n+1],m-2);
    for (int i = n; i >= 1; i--) {
        inv[i] = (inv[i + 1] * (i + 1)) % m;
    }
}

// 组合公式
long long c(int n, int k) {
    return (((fac[n] * inv[k]) % m) * inv[n - k]) % m;
}

signed main()
{
    cin>>n>>a>>b>>m;
    build();
    int ans=0;
    for(int i=n/2;i<=n;i++){
        ans+=c(i+1,n-i)*power(i,a)*power(n-i,b);
        ans%=m;
    }
    cout<<(ans+m)%m<<endl;
    return 0;
}
