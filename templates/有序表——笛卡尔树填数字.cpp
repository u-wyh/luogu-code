// �������
// ����һ������Ϊn������arr��arr[i]��ʾiλ���Ϸ��������θ�������
// ��ô��1λ�õ�nλ�ã�ÿ��λ�þ���һ��ֱ��ͼ�����е�ֱ��ͼ������һ��
// ����Ƭ�����У���Ҫ����k����ͬ���֣���������������������ͬһ�л���ͬһ��
// ע������Ƭ�����У����ĳһ���м�Ͽ��ˣ�ʹ�����������޷�����һ����ͨ������Υ��
// �����������ֵķ��������𰸶� 1000000007 ȡģ
// 1 <= n��k <= 500    0 <= arr[i] <= 10^6
// �������� : https://www.luogu.com.cn/problem/P6453
// ��Ϊ��������Ŀ��ÿռ���٣���������Ϊint���ͣ�����long����
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1000000007;
const int MAXN = 501;
const int MAXH = 1000000;

// ��������
int arr[MAXN];
// �׳�������
int fac[MAXH + 1];
// �׳���Ԫ��
int inv[MAXH + 1];
// �ѿ�������Ҫ
int ls[MAXN];
int rs[MAXN];
int sta[MAXN];
// dfs��Ҫ
int size[MAXN];
// dp�Ƕ�̬�滮��
int dp[MAXN][MAXN];
// tmp�Ƕ�̬�滮����ʱ���
int tmp[MAXN];
int n, k;

int power(int x, int p) {
    int ans = 1;
    while (p > 0) {
        if ((p & 1) == 1) {
            ans = (ans * x) % MOD;
        }
        x = (x * x) % MOD;
        p >>= 1;
    }
    return  ans;
}

int c(int n, int k) {
    return n < k ? 0 : ((long long) fac[n] * inv[k] % MOD * inv[n - k] % MOD);
}

void build() {
    fac[0] = fac[1] = inv[0] = 1;
    for (int i = 2; i <= MAXH; i++) {
        fac[i] = ( fac[i - 1] * i % MOD);
    }
    inv[MAXH] = power(fac[MAXH], MOD - 2);
    for (int i = MAXH - 1; i >= 1; i--) {
        inv[i] =  ( inv[i + 1] * (i + 1) % MOD);
    }
    for (int i = 1, top = 0, pos; i <= n; i++) {
        pos = top;
        while (pos > 0 && arr[sta[pos]] > arr[i]) {
            pos--;
        }
        if (pos > 0) {
            rs[sta[pos]] = i;
        }
        if (pos < top) {
            ls[i] = sta[pos + 1];
        }
        sta[++pos] = i;
        top = pos;
    }
}

void dfs(int u, int fa) {
    if (u == 0) {
        return;
    }
    dfs(ls[u], u);
    dfs(rs[u], u);
    size[u] = size[ls[u]] + size[rs[u]] + 1;
    for(int i=0;i<=k;i++){
        tmp[i]=0;
    }
    // ����dfs���̶����ϣ���һ���ֵ��ܸ��Ӷ�O(n^2)
    for (int l = 0; l <= min(size[ls[u]], k); l++) {
        for (int r = 0; r <= min(size[rs[u]], k - l); r++) {
            tmp[l + r] = (int) (tmp[l + r] + (long) dp[ls[u]][l] * dp[rs[u]][r] % MOD) % MOD;
        }
    }
    // ����dfs���̶����ϣ���һ���ֵ��ܸ��Ӷ�O(min(n��3�η�, n * kƽ��))
    for (int i = 0; i <= min(size[u], k); i++) {
        for (int p = 0; p <= i; p++) {
            dp[u][i] = (int) (dp[u][i] + (long) c(size[u] - p, i - p) * c(arr[u] - arr[fa], i - p) % MOD
                    * fac[i - p] % MOD * tmp[p] % MOD) % MOD;
        }
    }
}

int compute() {
    build();
    dp[0][0] = 1;
    dfs(sta[1], 0);
    return dp[sta[1]][k];
}

signed main()
{
    cin>>n>>k;
    for (int i = 1; i <= n; i++) {
        cin>>arr[i];
    }
    cout<<compute()<<endl;
    return 0;
}
