#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 6005;
const int INF = 1e18;

int n,m;
int val[MAXN];
int need[MAXN];//��ʾ��������ڵ�Ϊ�׵������� ����ж��ٸ�ƻ���Ϳ���׬Ǯ

int cnt=1;
int head[MAXN];
int nxt[MAXN];
int to[MAXN];

struct node{
    int need,id;
};
struct cmp{
    bool operator()(node a,node b){
        return a.need>b.need;
    }
};
priority_queue<node,vector<node>,cmp>q;

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

inline void clear(){
    while(!q.empty()){
        q.pop();
    }
}

inline void dfs(int u){
    clear();
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
    }
    if(val[u]>=0){
        //������λ����ƻ��  ��ô�϶�ֱ�Ӿ���׬Ǯ��
        need[u]=0;
        return ;
    }
    clear();
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        q.push({need[v],v});//�����ӽڵ����
    }
    need[u]-=val[u];//����Ŀǰ����ͻ���
    bool flag=false;
    int tot=0;//����Ŀǰӵ�е�ƻ������
    while(!q.empty()){
        if(tot-need[u]>=0){
            //��ʾƻ���Ѿ�����Ҫ�Ķ��� ��ô����׬��
            flag=true;
            break;
        }
        node x=q.top();
        q.pop();
        if(tot<need[x.id]){
            //��ʾ�����е�ƻ�������޷������������׬Ǯ
            need[u]+=need[x.id]-tot;//��ô����Ҫ�����������׬Ǯ  ��Ϊ���Ѿ��������׵���
            tot=need[x.id];//��ӵ�е�ƻ��������Ϊ��ʱ��Ҫ��
        }
        tot+=val[x.id];
        for(int i=head[x.id];i;i=nxt[i]){
            int v=to[i];
            q.push({need[v],v});
        }
    }
    if(tot-need[u]>=0){
        flag=true;
    }
    if(!flag){
        need[u]=INF;
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=2;i<=n;i++){
        int u;
        cin>>u;
        addedge(u,i);
    }
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    dfs(1);
    clear();
    q.push({need[1],1});
    int ans=m;
    while(!q.empty()){
        node x=q.top();
        q.pop();
        if(ans<need[x.id]){
            break;
        }
        ans+=val[x.id];
        for(int i=head[x.id];i;i=nxt[i]){
            int v=to[i];
            q.push({need[v],v});
        }
    }
    cout<<ans<<endl;
    return 0;
}