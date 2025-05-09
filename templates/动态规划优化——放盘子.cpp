// �����ӵķ���
// һ����n������k�ֲˣ����������ų�һ�ţ�ÿ������ֻ�ܷ�һ�ֲ�
// Ҫ����������������Ӳ�Ʒһ�����������ظ������ǲ������
// ���ذ��̵ķ��������𰸶� 1000000007 ȡģ
// 1 <= n <= 1000
// 1 <= k <= 1000
// ������ʵ�󳧱��ԣ���������֤
#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

int n,k;

// ��ʽ�����ĳ���˼·
int f1(int i) {
    if (i == 0) {
        return 1;
    }
    if (i == 1) {
        return k - 1;
    }
    long p1 = f1(i - 1);
    long p2 = f1(i - 2);
    return (int) (((p1 + p2) * (k - 1)) % MOD);
}

int dp1() {
    if (n == 1) {
        return k;
    }
    return (int) ((((long) f1(n - 1) + f1(n - 2)) * k) % MOD);
}

// ��ʽ��������ͨ��̬�滮�汾
// ʱ�临�Ӷ�O(n)
int dp2() {
	if (n == 1) {
		return k;
	}
	int dp[n];
	dp[0] = 1;
	dp[1] = k - 1;
	for (int i = 2; i < n; i++) {
		long p1 = dp[i - 1];
		long p2 = dp[i - 2];
		dp[i] = (int) (((p1 + p2) * (k - 1)) % MOD);
	}
	return (int) ((((long) dp[n - 1] + dp[n - 2]) * k) % MOD);
}

// ���Ž�İ汾����̬�滮 + ����������Ż�
// ʱ�临�Ӷ�O(log n)
// �����ͬѧ������098
typedef vector<vector<long long>> Matrix;

Matrix multiply(const Matrix& a, const Matrix& b) {
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    Matrix ans(n, vector<long long>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int c = 0; c < k; ++c) {
                ans[i][j] = (ans[i][j] + a[i][c] * b[c][j]) % MOD;
            }
        }
    }
    return ans;
}

Matrix power(const Matrix& m, int p) {
    int n = m.size();
    Matrix ans(n, vector<long long>(n, 0));
    for (int i = 0; i < n; ++i) {
        ans[i][i] = 1;
    }
    Matrix base = m;
    while (p > 0) {
        if (p % 2 == 1) {
            ans = multiply(ans, base);
        }
        base = multiply(base, base);
        p /= 2;
    }
    return ans;
}

int dp3() {
    if (n == 1) {
        return k;
    }
    int s = k - 1;
    Matrix start = { {1, s} };
    Matrix base = { {0, s}, {1, s} };
    Matrix ans = multiply(start, power(base, n - 2));
    return ((ans[0][0] + ans[0][1]) * k) % MOD;
}

int main()
{
    cin>>n>>k;
    cout<<dp1()<<endl;
    cout<<dp2()<<endl;
    cout<<dp3()<<endl;
    return 0;
}
