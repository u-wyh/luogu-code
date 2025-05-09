#include<bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
const int LIMIT = 19;

int n,m;
int power;
int head[MAXN<<1];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int deep[MAXN],stjump[MAXN][LIMIT];
int togather,cost;

void dfs(int u, int f) {
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;
    for (int p = 1; p <= power; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    //���u��deep  stjump
    for (int e = head[u]; e != 0; e = Next[e]) {
        if (to[e] != f) {
            dfs(to[e], u);
        }
        //���µݹ�
    }
}

int lca(int a, int b) {
    if (deep[a] < deep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    //ȷ����С��ϵ
    for (int p = power; p >= 0; p--) {
        if (deep[stjump[a][p]] >= deep[b]) {
            a = stjump[a][p];
        }
    }
    //���Ƚ����߱�Ϊͬһ�߶�
    if (a == b) {
        return a;
    }
    //�����ͬ˵���������ȹ�ϵ
    for (int p = power; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            a = stjump[a][p];
            b = stjump[b][p];
        }
        //�ж�������Ƿ���Ϲ���
    }
    return stjump[a][0]==0?1:stjump[a][0];
    //���ǽ�ͷ������������Ϊ0  ʵ����û��0
}

void compute(int a,int b,int c){
    int h1 = lca(a, b), h2 = lca(a, c), h3 = lca(b, c);
    int high = h1 != h2 ? (deep[h1] < deep[h2] ? h1 : h2) : h1;
    int low = h1 != h2 ? (deep[h1] > deep[h2] ? h1 : h2) : h3;
    togather = low;
    cost = (long) deep[a] + deep[b] + deep[c] - deep[high] * 2 - deep[low];
}

int main()
{
    cin>>n>>m;
    power=log2(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;

    }
    dfs(1,0);
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v>>w;
        compute(u,v,w);
        cout<<togather<<' '<<cost<<endl;
    }
    return 0;
}
//#include <iostream>
//#include <algorithm>
//#include <cmath>
//#include <cstdio>
//
//using namespace std;
//
//const int maxn = 500001;
//const int limit = 19;
//
//int power;
//int head[maxn];
//int edgenext[maxn << 1];
//int edgeto[maxn << 1];
//int cnt;
//int deep[maxn];
//int stjump[maxn][limit];
//int togather;
//long long cost;
//
//int log2(int n) {
//    int ans = 0;
//    while ((1 << ans) <= (n >> 1)) {
//        ans++;
//    }
//    return ans;
//}
//
//void build(int n) {
//    power = log2(n);
//    cnt = 1;
//    fill(head, head + n + 1, 0);
//}
//
//void addedge(int u, int v) {
//	edgenext[cnt] = head[u];
//	edgeto[cnt] = v;
//    head[u] = cnt++;
//}
//
//void dfs(int u, int f) {
//    deep[u] = deep[f] + 1;
//    stjump[u][0] = f;
//    for (int p = 1; p <= power; p++) {
//        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
//    }
//    for (int e = head[u]; e != 0; e = edgenext[e]) {
//        if (edgeto[e] != f) {
//            dfs(edgeto[e], u);
//        }
//    }
//}
//
//int lca(int a, int b) {
//    if (deep[a] < deep[b]) swap(a, b);
//    for (int p = power; p >= 0; p--) {
//        if (deep[stjump[a][p]] >= deep[b]) {
//            a = stjump[a][p];
//        }
//    }
//    if (a == b) return a;
//    for (int p = power; p >= 0; p--) {
//        if (stjump[a][p] != stjump[b][p]) {
//            a = stjump[a][p];
//            b = stjump[b][p];
//        }
//    }
//    return stjump[a][0];
//}
//
//void compute(int a, int b, int c) {
//	int h1 = lca(a, b), h2 = lca(a, c), h3 = lca(b, c);
//	int high = h1 != h2 ? (deep[h1] < deep[h2] ? h1 : h2) : h1;
//	int low = h1 != h2 ? (deep[h1] > deep[h2] ? h1 : h2) : h3;
//	togather = low;
//	cost = (long) deep[a] + deep[b] + deep[c] - deep[high] * 2 - deep[low];
//}
//
//int main() {
//    int n, m;
//    scanf("%d %d", &n, &m);
//    build(n);
//    for (int i = 1, u, v; i < n; i++) {
//        scanf("%d %d", &u, &v);
//        addedge(u, v);
//        addedge(v, u);
//    }
//    dfs(1, 0);
//    for (int i = 1, a, b, c; i <= m; i++) {
//        scanf("%d %d %d", &a, &b, &c);
//        compute(a, b, c);
//        printf("%d %lld\n", togather, cost);
//    }
//    return 0;
//}
