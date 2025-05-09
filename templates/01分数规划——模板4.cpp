// ��СȦ
// һ����n���ڵ㣬m������ߣ�ÿ������Ȩֵ
// ��������Ȩͼ�У����������ɻ����涨����ƽ��ֵΪ
// ���бߵ�Ȩֵ�� / ���бߵ�����
// �������л���ƽ��ֵ�����ٵ�ƽ��ֵ���������С�����8λ�����ಿ������
// 1 <= n <= 3000
// 1 <= m <= 10000
// -10^7 <= ��Ȩ <= 10^7
// �������� : https://www.luogu.com.cn/problem/P3199
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3001;
const int MAXM = 10001;
const double MAXE = 1e7;
const double sml = 1e-9;

// ��ʽǰ����
int head[MAXN];
int Next[MAXM];
int to[MAXM];
double weight[MAXM];
int cnt=1;

// dfs�жϸ�����ÿ������ۻ���Ȩ
double value[MAXN];
// dfs�жϸ�����ÿ�����Ƿ��ǵݹ�·���ϵĵ�
bool path[MAXN];
int n, m;

void addEdge(int u, int v, double w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

// ��ʵ����spfa�ĵݹ�棬ʱ�临�Ӷ�O(n * m)
bool dfs(int u, double x) {
    if (u == 0) {
        // ��Ϊ0�ŵ��ǳ���Դ�㣬����ͨ�����е�������
        for (int i = 1; i <= n; i++) {
            if (dfs(i, x)) {
                return true;
            }
        }
    } else {
        path[u] = true;
        for (int e = head[u]; e != 0; e = Next[e]) {
            int v = to[e];
            double w = weight[e] - x;
            // ֻ��v���ۻ���Ȩ��С���Ż�ݹ飬�ǳ�ǿ�ļ�֦
            // ����ݹ�·���ص�v�����Ҵ�ʱ��v���ۻ���Ȩ��С�������˵�������˸���
            // ���ߺ����ݹ��ҵ��˸���
            // ֱ�ӷ���true
            if (value[v] > value[u] + w) {
                value[v] = value[u] + w;
                if (path[v] || dfs(v, x)) {
                    return true;
                }
            }
        }
        path[u] = false;
    }
    return false;
}

// ���б߶���ȥx������ͼ���Ƿ���ڸ���
bool check(double x) {
    for(int i=1;i<=n+1;i++){
        path[i]=false;
        value[i]=0;
    }
    return dfs(0, x);
}

int main()
{
    cin>>n>>m;
    for (int i = 1; i <= m; i++) {
        int u,v;
        double w;
        cin>>u>>v>>w;
        addEdge(u, v, w);
    }
    double l = -MAXE, r = MAXE, x, ans = 0;
    while (l < r && r - l >= sml) {
        x = (l + r) / 2;
        if (check(x)) {
            r = x - sml;
        } else {
            ans = x;
            l = x + sml;
        }
    }
    printf("%.8f\n", ans);
    return 0;
}
