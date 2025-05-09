#include<bits/stdc++.h>
using namespace std;
const int MAXN = 30005;
const int MAXM = 60005;
const int LIMIT = 16;

int n,m,power;
int sum[MAXN];
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
    return stjump[a][0];
    //���ǽ�ͷ������������Ϊ0  ʵ����û��0
}

int main()
{
    cin>>n;
    sum[0]=-1;
    power=log2(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,0);
    cin>>m;
    int pre,ans=0;
    cin>>pre;
    for(int i=1;i<m;i++){
        int v,w;
        cin>>v;
        w=lca(pre,v);
        ans+=deep[pre]+deep[v]-2*deep[w];
        pre=v;
    }
    cout<<ans<<endl;
    return 0;
}
