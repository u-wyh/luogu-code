// �Ѿ�û��ʲô�ú��µ���
// ������������Ϊn�����飬a[i]��ʾ��i���ǹ���������b[i]��ʾ��i��ҩƬ������
// ����������ֵ������ͬ��ÿһ���ǹ�Ҫѡһ��ҩƬ�������
// ������֮���ǹ����� > ҩƬ��������Ϊ�ǹ�������
// ������֮���ǹ����� < ҩƬ��������ΪҩƬ������
// ϣ���������ǹ����������� = ҩƬ���������� + k
// ������Է��������𰸶� 1000000009 ȡģ
// ������a = [5, 35, 15, 45]��b = [40, 20, 10, 30]��k = 2������4����Ϊ��4����Է���
// (5-40��35-20��15-10��45-30)��(5-40��35-30��15-10��45-20)
// (5-20��35-30��15-10��45-40)��(5-30��35-20��15-10��45-40)
// 1 <= n <= 2000
// 0 <= k <= n
// �������� : https://www.luogu.com.cn/problem/P4859
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 2001;
const int MOD = 1000000009;

int n, k;
int a[MAXN], b[MAXN];
long long fac[MAXN];
long long c[MAXN][MAXN];
long long small[MAXN];
long long dp[MAXN][MAXN];
long long g[MAXN];

// Ԥ����׳˺������
void build() {
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    for (int i = 0; i <= n; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
        }
    }
}

// ������Է�����
long long compute() {
    build();
    sort(a + 1, a + n + 1);
    sort(b + 1, b + n + 1);
    for (int i = 1, cnt = 0; i <= n; i++) {
        while (cnt + 1 <= n && b[cnt + 1] < a[i]) {
            cnt++;
        }
        small[i] = cnt;
    }
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i][0] = dp[i - 1][0];
        for (int j = 1; j <= i; j++) {
            dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1] * (small[i] - j + 1) % MOD) % MOD;
        }
    }
    for (int i = 0; i <= n; i++) {
        g[i] = fac[n - i] * dp[n][i] % MOD;
    }
    long long ans = 0;
    for (int i = k; i <= n; i++) {
        if (((i - k) & 1) == 0) {
            ans = (ans + c[i][k] * g[i] % MOD) % MOD;
        } else {
            ans = (ans + c[i][k] * g[i] % MOD * (MOD - 1) % MOD) % MOD;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    if (((n + k) & 1) == 0) {
        k = (n + k) / 2;
        cout << compute() << endl;
    } else {
        cout << 0 << endl;
    }
    return 0;
}
