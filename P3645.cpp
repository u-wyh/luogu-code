#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e4+5;

int n,m,s,t;
struct node{
    int pos,abil,step;
};
vector<int>vec[MAXN];
queue<node>q;
bitset<MAXN>vis[MAXN];
bool visit[MAXN];

void insert(int pos,int abil,int step){
    if(!visit[pos]){
        visit[pos]=true;
        for(int i=0;i<(int)vec[pos].size();i++){
            int v=vec[pos][i];
            if(!vis[pos].test(v)){
                vis[pos].set(v);
                q.push({pos,v,step});
            }
        }
    }
    if(!vis[pos].test(abil)){
        vis[pos].set(abil);
        q.push({pos,abil,step});
    }
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++){
        int pos,val;
        scanf("%d %d",&pos,&val);
        if(i==1){
            s=pos;
        }
        if(i==2){
            t=pos;
        }
        vec[pos].push_back(val);
    }
    if(s==t){
        cout<<0<<endl;
        return 0;
    }
    visit[s]=true;
    for(int i=0;i<(int)vec[s].size();i++){
        int v=vec[s][i];
        if(!vis[s].test(v)){
            vis[s].set(v);
            q.push({s,v,0});
        }
    }
    while(!q.empty()){
        node u=q.front();
        q.pop();
        if(u.pos-u.abil==t||u.pos+u.abil==t){
            printf("%d",u.step+1);
            return 0;
        }
        if(u.pos-u.abil>=0){
            insert(u.pos-u.abil,u.abil,u.step+1);
        }
        if(u.pos+u.abil<n){
            insert(u.pos+u.abil,u.abil,u.step+1);
        }
    }
    cout<<-1<<endl;
    return 0;
}