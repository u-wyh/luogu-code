// ѡ��ڵ�����ʹ���������(�ݹ��)
// ����һ��n����������ߵı�Ȩ������������
// �ӱ������������������ܳ�����������
// ������֪����ĳ���ڵ�����ʱ����������Ҷ�ڵ������������Ƕ���
// �������� : http://poj.org/problem?id=3585
// �ύ���µ�code���ύʱ��������ĳ�"Main"
// C++��ôд��ͨ����java����Ϊ�ݹ����̫�����ջ
// java��ͨ����д���ο����ڿ�Code04_MaximizeFlow2�ļ�
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
const int MAXN = 200001;

int n;

int head[MAXN];
int to[MAXN<<1];
int weight[MAXN<<1];
int Next[MAXN<<1];
int cnt;

// degree[u] : �м����ߺ�u�ڵ�����
int degree[MAXN];
// flow[u] : ��u��������u�ڵ�Ϊͷ�������ϣ����е�Ҷ�ڵ㣬�����Ƕ���
int flow[MAXN];
// dp[u] : ��u��������u�ڵ�Ϊ�����������ϣ����е�Ҷ�ڵ㣬�����Ƕ���
int dp[MAXN];

void build() {
    cnt = 1;
    for(int i=1;i<=n;i++){
        head[i]=0;
        degree[i]=0;
        flow[i]=0;
        dp[i]=0;
    }
}

void addEdge(int u, int v, int w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void dfs1(int u, int f) {
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            dfs1(v, u);
        }
    }
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            if (degree[v] == 1) {
                flow[u] += weight[e];
            } else {
                flow[u] += min(flow[v], weight[e]);
            }
        }
    }
}

void dfs2(int u, int f) {
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            if (degree[u] == 1) {
                dp[v] = flow[v] + weight[e];
            } else {
                // uOut : u�����������
                int uOut = dp[u] - min(flow[v], weight[e]);
                dp[v] = flow[v] + min(uOut, weight[e]);
            }
            dfs2(v, u);
        }
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        build();
        for(int i=1,u,v,w;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
            degree[u]++;
            degree[v]++;
        }
        dfs1(1, 0);
        dp[1] = flow[1];
        dfs2(1, 0);
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            ans = max(ans, dp[i]);
        }
        printf("%d\n",ans);
    }

    return 0;
}
