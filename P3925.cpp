#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+5;

int n,k;
int cnt1=0;
int cnt=1;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int sz[MAXN<<1];

void clear(){
    for(int i=1;i<=n;i++){
        head[i]=0;
    }
    for(int i=1;i<=cnt;i++){
        Next[i]=0;
        to[i]=0;
        sz[i]=0;
    }
    cnt1=0;
    cnt=1;
}

void dfs(int u,int f){
    sz[u]=1;
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs(v,u);
            sz[u]+=sz[v];
        }
    }
    if(sz[u]==k){
        cnt1++;
        sz[u]=0;
    }
}

int main()
{
    int t;
    cin>>t;
    while(t--){
        cin>>n>>k;
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
        cout<<(cnt1==n/k?"YES":"NO")<<endl;
        clear();
    }
    return 0;
}
