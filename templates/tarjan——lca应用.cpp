//P7103
//tarjan��lca����
//�����������������tarjan��lca
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e6+5;

int n,m;
int fa[MAXN];
int ans[MAXN];
int dep[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXN];
int to[MAXN];

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
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

inline int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void dfs(int u,int f){
    dep[u]=dep[f]+1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v,u);
        fa[v]=u;//������������  ��ô�������Ҫ�͵�ǰ�ڵ�ϲ� ���Ҵ���ڵ����óɵ�ǰ�ڵ�  
        //tarjan�ľ������
    }
    ans[dep[u]]= ans[dep[u]]?find(ans[dep[u]]):u;
	//ans[d[x]]��ʾ��x�ڵ�֮ǰ����Ⱥ�d[x]һ���Ľڵ��lca  �����0  �ͱ�ʾ��ǰû����������ͬ��ȵ�  ��ô���ó��Լ�
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=n;i++){
        int f;
        f=read();
        addedge(f,i);
    }
    dfs(1,0);
    for(int i=1;i<=m;i++){
        cout<<ans[read()]<<endl;
    }
    return 0;
}