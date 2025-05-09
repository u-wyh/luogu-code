//����dfs
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
#define int long long

int n,m;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;
// ֱ���Ŀ�ʼ��
int start;
// ֱ���Ľ�����
int en;
// ֱ������
int diameter;
// dist[i] : �ӹ涨��ͷ�ڵ�������ߵ�i�ľ���
int dist[MAXN];
int beg[MAXN];
int ove[MAXN];
int ans=0;

void dfs(int u,int f,int w){
    dist[u]=dist[f]+w;
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            dfs(to[i],u,weight[i]);
        }
    }
}

void road() {
    dfs(1, 0, 0);
    //�������������  һ�㶼��1
    start = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[start]) {
            start = i;
        }
    }
    //ѡ�������������ĵ�  ��Ϊͷ���
    dfs(start, 0, 0);
    en = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[en]) {
            en = i;
        }
    }
    diameter = dist[en];
}
//���ε���dfs

void dfs1(int u,int f,int w){
    beg[u]=beg[f]+w;
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            dfs1(to[i],u,weight[i]);
        }
    }
}

void dfs2(int u,int f,int w){
    ove[u]=ove[f]+w;
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            dfs2(to[i],u,weight[i]);
        }
    }
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;

        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        weight[cnt]=w;
        head[v]=cnt++;
    }
    road();
    ans=diameter;
    dfs1(start,0,0);
    dfs2(en,0,0);
    for(int i=1;i<=n;i++){
        ans=max(ans,min(beg[i],ove[i])+diameter);
    }
    cout<<ans;
    return 0;
}
