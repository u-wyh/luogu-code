#include<bits/stdc++.h>
using namespace std;

int n;
int X[42],Y[42];
map<pair<int,int>,int>vis;
int tot=0;
vector<int>vec[10000005];
int ans[42];

void dfs1(int u,int x,int y,int now){
    if(u==n/2+1){
        if(vis[{x,y}]==0){
            vis[{x,y}]=++tot;
        }
        vec[vis[{x,y}]].push_back(now);
        return ;
    }
    dfs1(u+1,x+X[u],y+Y[u],now+1);
    dfs1(u+1,x,y,now);
}

void dfs2(int u,int x,int y,int now){
    if(u==n+1){
        int k=vis[{X[n+1]-x,Y[n+1]-y}];
        if(k!=0){
            for(int i=0;i<vec[k].size();i++){
                ans[now+vec[k][i]]++;
            }
        }
        return ;
    }
    dfs2(u+1,x+X[u],y+Y[u],now+1);
    dfs2(u+1,x,y,now);
}

int main()
{
    cin>>n;
    cin>>X[n+1]>>Y[n+1];
    for(int i=1;i<=n;i++){
        cin>>X[i]>>Y[i];
    }
    dfs1(1,0,0,0);
    dfs2(n/2+1,0,0,0);
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}