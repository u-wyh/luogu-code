// ��Ϸ(�ݹ��)
// һ����n���ڵ㣬n <= 5000��nΪż����������m��������СA����m��������СB��mΪn��һ��
// ����n-1���ߣ��ڵ�֮�����һ������1�Žڵ��Ǹ��ڵ�
// ��������Ϊn������arr��arr[i]��ֵ��ʾi�Žڵ���˭ӵ�У�0ΪСAӵ�У�1ΪСBӵ��
// ��Ϸ��m�غϣ�ÿ�غ϶���ʤ����������Ҫѡ��һ���Լ�ӵ�С���֮ǰûѡ���ĵ㣬��Ϊ���غϵ�ǰ��
// СA��ǰ�����������СB��ǰ�㣬��СAʤ��СB��ǰ�����������СA��ǰ�㣬��СBʤ������ƽ��
// ����m�غ����ܳ���k�η�ƽ�ֵ���Ϸ����������ӡk=0..mʱ�����д𰸣��� 998244353 ȡģ
// ������Ϸ��Ϊ��ͬ�Ķ��壺���ҽ�������СAӵ�еĵ�x��СB��СAѡ��x���Ǹ��غ���ѡ��ĵ㲻ͬ
// �������� : https://www.luogu.com.cn/problem/P6478
// �ύ���µ�code���ύʱ��������ĳ�"Main"��ע��dfs�ǵݹ麯��
// C++��ͬѧ����ȫ��ͨ����java��ͬѧ��ʱ����ȫ��ͨ������ʱ��Ϊ�ݹ�չ��̫�����ջ
// dfs�ӵݹ��ĵ������ʵ�֣��뿴Code05_Game2�ļ�
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 5001;
const int MOD = 998244353;

int n, m;
int arr[MAXN];
long long fac[MAXN];
long long c[MAXN][MAXN];

// ��ʽǰ����
int head[MAXN];
int next_[MAXN << 1];
int to[MAXN << 1];
int cnt;

// DFS ��Ҫ
int size[MAXN];
int belong[MAXN][2];
long long dp[MAXN][MAXN];
long long backup[MAXN];

// ������Ҫ
long long g[MAXN];

// ����
long long f[MAXN];

void build() {
    cnt = 1;
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
        fac[i] = fac[i - 1] * i % MOD;
    }
    for (int i = 0; i <= n; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
        }
    }
}

void addEdge(int u, int v) {
    next_[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

// �ݹ�� DFS
void dfs(int u, int fa) {
    size[u] = 1;
    belong[u][arr[u]] = 1;
    dp[u][0] = 1;
    // ���ȼ��㲻����ͷ�ڵ�ķ�����
    for (int e = head[u]; e; e = next_[e]) {
        int v = to[e];
        if (v != fa) {
            dfs(v, u);
            // ֮ǰ����������ϵļ������������� backup
            for (int i = 0; i <= min(size[u] / 2, m); i++) {
                backup[i] = dp[u][i];
                dp[u][i] = 0;
            }
            // ���� DP ��ö����Ϊ���������Ľڵ��������޽��и��Ӷ��Ż�
            for (int l = 0; l <= min(size[u] / 2, m); l++) {
                for (int r = 0; r <= min(size[v] / 2, m - l); r++) {
                    dp[u][l + r] = (dp[u][l + r] + backup[l] * dp[v][r] % MOD) % MOD;
                }
            }
            size[u] += size[v];
            belong[u][0] += belong[v][0];
            belong[u][1] += belong[v][1];
        }
    }
    // ���������ͷ�ڵ�ķ�����
    // ���� dp[u][i]��i ���԰����޶�Ϊ min(����ӵ�еĽڵ�����m)
    // u Ϊͷ�������У������м����ڵ�
    int num = belong[u][arr[u] ^ 1];
    // ������ͷ�ڵ�ķ������������� backup
    for (int i = 1; i <= min(num, m); i++) {
        backup[i] = dp[u][i];
    }
    // �������ͷ�ڵ�ķ��������ۼ���
    for (int i = 1; i <= min(num, m); i++) {
        dp[u][i] = (dp[u][i] + backup[i - 1] * (num - i + 1) % MOD) % MOD;
    }
}

void compute() {
    dfs(1, 0); // DFS �ǵݹ��
    for (int i = 0; i <= m; i++) {
        g[i] = dp[1][i] * fac[m - i] % MOD;
    }
    for (int k = 0; k <= m; k++) {
        for (int i = k; i <= m; i++) {
            if (((i - k) & 1) == 0) {
                f[k] = (f[k] + c[i][k] * g[i] % MOD) % MOD;
            } else {
                // -1 �� (MOD-1) ͬ��
                f[k] = (f[k] + c[i][k] * g[i] % MOD * (MOD - 1) % MOD) % MOD;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    m = n >> 1;
    build();
    string str;
    cin >> str;
    for (int i = 1; i <= n; i++) {
        arr[i] = str[i - 1] - '0';
    }
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    compute();
    for (int k = 0; k <= m; k++) {
        cout << f[k] << '\n';
    }
    return 0;
}
