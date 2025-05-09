// �ֲݵķ�����(��ͨ״ѹdp)
// ����һ��n*m�Ķ�ά����grid
// ������ֻ��0��1����ֵ��0��ʾ����ز����ֲݣ�1��ʾ����ؿ����ֲ�
// �ֲݵ�ʱ���κ��������˲ݵ���ز������ڣ����ڰ����ϡ��¡������ĸ�����
// �������������ֶ��ٲݣ�ֻҪ���ƻ�����Ĺ��򼴿�
// �����ֲݵķ��������𰸶�100000000ȡģ
// 1 <= n, m <= 12
// �������� : https://www.luogu.com.cn/problem/P1879
// �ύ���µ�code���ύʱ��������ĳ�"Main"
// ��ͨ״ѹdp�İ汾�޷�ͨ�����в�������
// ��Щ���������ᳬʱ������dfs���̺ܷ�ʱ���µ�
#include <iostream>
#include <vector>
#include <cstring> // for memset

using namespace std;

const int MAXN = 12;
const int MAXM = 12;
const int MOD = 100000000;
const int MAXS = 1 << MAXM;

int grid[MAXN][MAXM];
int dp[MAXN][MAXS];
int n, m;

int f(int i, int s);

// ������������ȡ״̬s�е�jλ��״̬
int get(int s, int j) {
    return (s >> j) & 1;
}

// ��������������״̬s�е�jλ��״̬Ϊv���������µ�״̬
int set(int s, int j, int v) {
    return v == 0 ? (s & (~(1 << j))) : (s | (1 << j));
}

// ���������������
// ��ǰ����i��j��
// i-1��ÿ���ֲݵ�״��s
// i��ÿ���ֲݵ�״��ss
// ���غ����м��ַ���
int dfs(int i, int j, int s, int ss) {
    if (j == m) {
        // �ݹ鵽��һ��
        return f(i + 1, ss);
    }
    // ���ֵ�ǰλ��  ֱ�ӵݹ鵽��һ��λ��
    int ans = dfs(i, j + 1, s, ss);
    // ��������ֵ�ǰλ��
    if (grid[i][j] == 1 && (j == 0 || !get(ss, j - 1)) && !get(s, j)) {
        // �ֵ�ǰλ�ã����ݹ鵽��һ��λ��
        ans = (ans + dfs(i, j + 1, s, set(ss, j, 1))) % MOD;
    }
    return ans;
}

// ���仯��������
int f(int i, int s) {
    if (i == n) {
        return 1; // �����ж�������ϣ�����1�ַ��������ɹ���
    }
    if (dp[i][s] != -1) {
        return dp[i][s]; // ����Ѿ��������ֱ�ӷ��ؽ��  ���仯����
    }
    int ans = dfs(i, 0, s, 0); // �ӵ�ǰ�еĵ�0�п�ʼ����
    dp[i][s] = ans; // ��¼���
    return ans;
}

// �����㺯��
int compute() {
    memset(dp, -1, sizeof(dp)); // ��ʼ��dp����Ϊ-1
    return f(0, 0); // �ӵ�0�С�״̬0��ʼ����
}

int main() {
    // ����
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    // ���㲢������
    cout << compute() << endl;
    return 0;
}
