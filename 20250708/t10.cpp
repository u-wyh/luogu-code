#include <bits/stdc++.h>
#define ll long long
#define for1(a,b,c) for(ll a=b;a<=c;a++)
#define for2(a,b,c) for(ll a=b;a>=c;a--)
#define pii pair<int,int>
using namespace std;
const ll N=2e5+10, M=998244353;

vector<int> e[N];
ll a[N];

void dfs(int x,int fa){
    a[x]=0;
    priority_queue<int> Q;
    for (auto v:e[x])
    {
        if(v==fa)continue;
        dfs(v,x);
        Q.push(-a[v]);
    }
    while (!Q.empty())
    {
        int p=-Q.top();Q.pop();
        if(p>=a[x]){
            a[x]++;
        }
    }
}

void solve(){
    int n;
    cin>>n;
    for1(i,1,n)e[i].clear();
    for1(i,2,n){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1,0);
    ll ans=0;
    for1(i,1,n)ans+=a[i];
    cout<<ans<<endl;
}

int main()
{
    int _=1;
    cin>>_;
    while(_--)solve();
    return 0;
}