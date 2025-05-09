#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int LIMIT = 17;

int n,m,power;
int head[MAXN];
int Next[MAXN];
int to[MAXN];
int cnt=1;
int deep[MAXN],stjump[MAXN][LIMIT+1];
int fa[MAXN];

inline void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}


void dfs(int u, int f) {
    //cout<<u<<' '<<f<<endl;
    //fa[u]=max(fa[u],fa[f]);//��������д�ǶԵ�
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;
    for (int p = 1; p <= power; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    //���u��deep  stjump
    for (int e = head[u]; e != 0; e = Next[e]) {
        if (to[e] != f) {
            fa[to[e]]=max(fa[u],fa[to[e]]);//��������д ����������Ǹ��ط���д  Ϊʲô�Ǵ�İ�
            //cout<<f<<' '<<to[e]<<' '<<fa[to[e]]<<endl;
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
    n=read();
    power=log2(n);
    fa[1]=1;
    for(int i=2;i<=n;i++){
        int u;
        u=read();
        u++;
        fa[i]=i;
        addedge(u,i);
    }
    dfs(1,1);
//    for(int i=1;i<=n;i++){
//        cout<<i<<": "<<fa[i]<<endl;
//    }
//    cout<<endl;
    m=read();
    int q,ans;
    for(int i=1,u;i<=m;i++){
        q=read();
        u=read();
        u++;
        ans=u;
        for(int i=2;i<=q;i++){
            u=read();
            u++;
            ans=lca(ans,u);
        }
        //cout<<ans<<' ';
        cout<<(fa[ans]-1)<<endl;
    }
    return 0;
}
