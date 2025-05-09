// �������
// ����һ�������ڵ���0~n��0�Žڵ�����������ͷ
// ���1~n�Ľڵ㣬ÿ���ڵ㶼����ļ���Ѻ�ս��ֵ��0�Žڵ�������ֵ����0
// ����ÿ����(a,b)����ʾ�ڵ�a�ĸ��ڵ���b����Щ�ڵ�ĸ��ڵ���0�ڵ�
// ����ļ��ĳ���ڵ㣬��ô�ýڵ㼰���Ϸ����������Ƚڵ㶼��Ҫ��ļ
// ����0�Žڵ�֮�⣬һ��������ļk���ˣ�ϣ����
// ս��ֵ֮�� / ��ļ����֮�ͣ������ֵ�����󣬴�ֻ�豣����λС��������ľ�������
// 1 <= k <= n <= 2500
// 0 <= ��ļ���ѡ�ս��ֵ <= 10^4
// �������� : https://www.luogu.com.cn/problem/P4322
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3001;
const int LIMIT = 10000;
const double NA = -1e9;
const double sml = 1e-6;

// ��ʽǰ����
int head[MAXN];
int Next[MAXN];
int to[MAXN];
int edgeCnt=1;

// ��ļ���ѣ��±�Ϊ�ڵ�ԭʼ���
int cost[MAXN];
// ս��ֵ���±�Ϊ�ڵ�ԭʼ���
int strength[MAXN];
// dfn[a] = b����ʾԭʼa�Žڵ��dfn���Ϊb
int dfn[MAXN];
// dfn�����
int dfnCnt=0;

// (ս��ֵ - x * ��ļ����)�Ľ��࣬�±�Ϊ�ڵ�dfn���
double value[MAXN];
// ������С���±�Ϊ�ڵ�dfn���
int size[MAXN];
// ����dp
double dp[MAXN][MAXN];
int k, n;

void addEdge(int u, int v) {
    Next[edgeCnt] = head[u];
    to[edgeCnt] = v;
    head[u] = edgeCnt++;
}

// ��¼�ڵ�u��dfn��� + ����u��������Ľڵ���
// ����ʵ�ֺͽ���079����Ŀ5��ѡ����������Ž⣬������ȫһ��
int dfs(int u) {
	int i = ++dfnCnt;
	dfn[u] = i;
	size[i] = 1;
	for (int e = head[u], v; e != 0; e = Next[e]) {
		v = to[e];
		size[i] += dfs(v);
	}
	return size[i];
}

// ����x��ֵ������ڵ�Ľ���ֵ��������ѡk+1����
// һ��Ҫ�γ���Ч�ṹ���������Ľ����
// �����߼���ȫ���Խ���079����Ŀ5��ѡ�����⣬�ص���ܵ����Ž�
bool check(double x) {
	// value[�ڵ�i��dfn���] = �ڵ�i��ս��ֵ - x * �ڵ�i����ļ����
	for (int i = 0; i <= n; i++) {
		value[dfn[i]] = (double) strength[i] - x * cost[i];
	}
	// Խ��λ����Ϊ������Ч��
	for (int j = 1; j <= k; j++) {
		dp[dfnCnt + 1][j] = NA;
	}
	// ����079��Ŀ5�����Ž��߼�
	for (int i = dfnCnt; i >= 2; i--) {
		for (int j = 1; j <= k; j++) {
			dp[i][j] = max(dp[i + size[i]][j], value[i] + dp[i + 1][j - 1]);
		}
	}
	// ԭʼ��0�Žڵ㣬dfn�����1�������ڵ��dfn��Ŵ�2��ʼ
	// 0�Žڵ��ս��ֵ����ļ���Ѷ���0�������ڵ�һ����ļk��
	return dp[2][k] >= 0;
}

int main()
{
    cin>>k>>n;
    for (int i = 1; i <= n; i++) {
        int u;
        cin>>cost[i]>>strength[i]>>u;
        addEdge(u, i);
    }
    dfs(0);
    double l = 0, r = LIMIT, x, ans = 0;
    while (l < r && r - l >= sml) {
        x = (l + r) / 2;
        if (check(x)) {
            ans = x;
            l = x + sml;
        } else {
            r = x - sml;
        }
    }
    printf("%.3f\n", ans);
    return 0;
}
