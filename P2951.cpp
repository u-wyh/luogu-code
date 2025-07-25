#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20005;
const int MAXM = 100005;

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};

priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
int n,m;
int dis[MAXN];
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;
bool vis[MAXN];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w=1;
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        weight[cnt]=w;
        head[v]=cnt++;
    }
    for(int i=1;i<=n;i++){
        dis[i]=INT_MAX;
    }
    dis[1]=0;
    heap.push({1,0});
    while(!heap.empty()){
        int u=heap.top().first;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=head[u];i>0;i=Next[i]){
            int v=to[i];
            int w=weight[i];
            if(!vis[v]&&dis[u]<dis[v]-w){
                dis[v]=w+dis[u];
                heap.push({v,dis[v]});
            }
        }
    }
    int ans1=0,ans2=0,ans3=0;
    for(int i=2;i<=n;i++){
        if(dis[i]>ans1&&dis[i]!=INT_MAX){
            ans1=dis[i];
            ans2=i;
            ans3=0;
        }
        if(ans1=dis[i]){
            ans3++;
        }
    }
    cout<<ans2<<' '<<ans1<<' '<<ans3;
    return 0;
}

