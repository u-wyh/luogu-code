#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;
const int LIMIT = 19;

int n,m,power,root;
int sz[MAXN],son[MAXN];
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;
int deep[MAXN],stjump[MAXN][LIMIT];

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u, int f) {
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;
    son[u]=son[f]+sz[u];
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
    return stjump[a][0]==0?root:stjump[a][0];
    //���ǽ�ͷ������������Ϊ0  ʵ����û��0
}
signed main()
{
    cin>>n>>m;
    power=log2(n)+1;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
        sz[u]++,sz[v]++;
    }
    dfs(1,0);
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v;
        w=lca(u,v);
        int ans=son[u]+son[v]-2*son[w]+sz[w];
        cout<<ans<<endl;
    }
    return 0;
}
