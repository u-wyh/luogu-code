#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int LIMIT = 20;

int n,m,power;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int dfn[MAXN];
int sz[MAXN];
int dfncnt;
int deep[MAXN];
int stjump[MAXN][LIMIT];

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

inline void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u, int f) {
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;
    dfn[u]=++dfncnt;
    sz[u]=1;
    for (int p = 1; p <= power; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    //���u��deep  stjump
    for (int e = head[u]; e != 0; e = Next[e]) {
        if (to[e] != f) {
            dfs(to[e], u);
            sz[u]+=sz[to[e]];
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

//�ж�x�ǲ���zΪͷ�������ϵ�һ��
inline bool in(int x,int f) {
    return (dfn[f]<=dfn[x]&&dfn[x]<=dfn[f]+sz[f]-1);
}

int soncount(int x,int f){
    if(x==f){
        //���� ����㲻�ܼ���
        return 0;
    }
    for(int i=power;i>=0;i--){
        if(dfn[stjump[x][i]]>dfn[f]){
            x=stjump[x][i];
        }
    }
    return sz[x];
}

int main()
{
    n=read(),m=read();
    power=log2(n);
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,0);
    for(int i=1;i<=m;i++){
        int x,y,z;
        x=read(),y=read(),z=read();
        if(lca(x,y)==z){
            cout<<(n-soncount(x,z)-soncount(y,z))<<endl;
        }
        else if(in(x,z)&&!in(y,z)){
            cout<<(sz[z]-soncount(x,z))<<endl;
        }
        else if(!in(x,z)&&in(y,z)){
            cout<<(sz[z]-soncount(y,z))<<endl;
        }
        else{
            cout<<0<<endl;
        }
    }
    return 0;
}

