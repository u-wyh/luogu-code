#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5;

int n,k;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int deep[MAXN],maxdeep[MAXN];
// dist[i] : �ӹ涨��ͷ�ڵ�������ߵ�i�ľ���
int dist[MAXN];
// last[i] : �ӹ涨��ͷ�ڵ������i�ڵ����һ���ڵ�
int last[MAXN];
int start,en,diameter;

void dfs(int u,int f){
    last[u]=f;
    dist[u]=dist[f]+1;
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            dfs(to[i],u);
        }
    }
}

void road() {
    dfs(1, 0);
    //�������������  һ�㶼��1
    start = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[start]) {
            start = i;
        }
    }
    //ѡ�������������ĵ�  ��Ϊͷ���
    dfs(start, 0);
    en = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[en]) {
            en = i;
        }
    }
    diameter = dist[en];
}
//���ε���dfs

void dfs1(int u,int f){
    deep[u]=deep[f]+1;
    maxdeep[u]=deep[u];
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs1(to[i],u);
            maxdeep[u]=max(maxdeep[u],maxdeep[v]);
        }
    }
}

bool cmp(int a,int b){
    return a>b;
}

int main()
{
    cin>>n>>k;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;
    }
    road();
    for(int i=1;i<=diameter/2;i++){
        start=last[en];
        en=start;
    }
    dfs1(start,0);
    for(int i=1;i<=n;i++){
        dist[i]=maxdeep[i]-deep[i]+1;
    }
    sort(dist+1,dist+n+1,cmp);
    cout<<dist[k+1];
    return 0;
}
