// ���ز�
// һ����m���ز���arr[i]��ʾi���ز��м���
// һ����n��ͬѧ��ÿ��ͬѧ����Ҫ�õ�һ���ز�
// ���ط����ز��ķ��������𰸶� 1000000007 ȡģ
// 0 <= n��m <= 1000
// 0 <= arr[i] <= 1000
// �������� : https://www.luogu.com.cn/problem/P5505
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1001;
const int MAXK = MAXN * 2;
const int MOD = 1000000007;

int arr[MAXN];
long c[MAXK][MAXK];
long g[MAXN];
int n, k, m;

long compute() {
    for (int i = 0; i <= k; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
        }
    }
    for (int i = 0; i < n; i++) {
        g[i] = c[n][i];
        for (int j = 1; j <= m; j++) {
            g[i] = (int) ((g[i] * c[arr[j] + n - i - 1][n - i - 1]) % MOD);
        }
    }
    g[n] = 0;
    long ans = 0;
    for (int i = 0; i <= n; i++) {
        if ((i & 1) == 0) {
            ans = (ans + g[i]) % MOD;
        } else {
            // -1 �� (MOD-1) ͬ��
            ans = (ans + g[i] * (MOD - 1) % MOD) % MOD;
        }
    }
    return ans;
}

signed main()
{
    cin>>n>>m;
    k=2*n;
    for(int i=1;i<=m;i++){
        cin>>arr[i];
    }
    cout<<compute();
    return 0;
}
