// ���м���
// ��һ������У���������ֵλ�ã���ʾһ�η�Χ��
// ������ֵ��һ������ô���ֵ���ڵ�λ�ã�������������ֵλ��
// ������ֵ�ж����������Ǹ����ڵ�λ�ã�������������ֵλ��
// ����һ������Ϊn������A����ô��Ȼ���ڵȳ�������B����ѡ��ͬ�����ӷ�Χʱ
// ��������η�Χ�ϣ���������ֵλ������ͬ�ģ�������������������B�������������޶�
// ����Ҫ������B�е�ÿ��ֵ����[1,m]��Χ�������ж��ٸ����������飬�𰸶� 1000000007 ȡģ
// 2 <= n��m <= 2 * 10^5    1 <= A[i] <= m    n * m <= 10^6
// �������� : https://www.luogu.com.cn/problem/CF1748E
// �������� : https://codeforces.com/problemset/problem/1748/E
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;
const int MAXN = 1000001;

int arr[MAXN];
int ls[MAXN];
int rs[MAXN];
int stack[MAXN];
long long tmp[MAXN];
int n, m;

void build() {
    int top = 0, pos;
    for (int i = 1; i <= n; i++) {
        pos = top;
        while (pos > 0 && arr[stack[pos]] < arr[i]) {
            pos--;
        }
        if (pos > 0) {
            rs[stack[pos]] = i;
        }
        if (pos < top) {
            ls[i] = stack[pos + 1];
        }
        stack[++pos] = i;
        top = pos;
    }
}

void dfs(int u, vector<vector<int>>& dp) {
    if (u == 0) {
        return;
    }
    dfs(ls[u], dp);
    dfs(rs[u], dp);
    for (int j = 1; j <= m; j++) {
        tmp[j] = (long long)dp[ls[u]][j - 1] * dp[rs[u]][j] % MOD;
    }
    for (int j = 1; j <= m; j++) {
        dp[u][j] = (dp[u][j - 1] + tmp[j]) % MOD;
    }
}

void clear() {
    fill(ls + 1, ls + n + 1, 0);
    fill(rs + 1, rs + n + 1, 0);
}

long long compute() {
    build();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int j = 0; j <= m; j++) {
        dp[0][j] = 1; // û�нڵ�ʱ��Ĭ����1����̬
    }
    dfs(stack[1], dp);
    clear();
    return dp[stack[1]][m];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cases;
    cin >> cases;
    for (int t = 1; t <= cases; t++) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
        }
        cout << compute() << endl;
    }

    return 0;
}
