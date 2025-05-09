#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m,k;
int val[MAXN];
int fun[MAXN];
int visit[MAXN];//dj�㷨��

//��ʽǰ���ǽ�ͼ
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int tot=1;

//�߶���
int tree[MAXN<<2];//��Ȩת��Ȩ
int cost[MAXN<<2];//��Ȩ

//�����ʷֲ���
int son[MAXN];//�ض��ӱ��  Ҷ�ӽ��û��
int id[MAXN];//���±�ź�ı��
int rk[MAXN];//���±�ź�ı�Ŷ�Ӧԭ���ı����ʲô
int cnt;
int fa[MAXN];//���׽ڵ���
int deep[MAXN];//�ڵ����
int sz[MAXN];//�Ըýڵ�Ϊ�׵������ڵ�����
int top[MAXN];//����������ͷ���

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // ע�������Ǵ��ڣ���Ϊ������ҪС����
};
priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);

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

inline void addedge(int u,int v,int w){
    Next[tot]=head[u];
    to[tot]=v;
    weight[tot]=w;
    head[u]=tot++;
}

//��һ��dfs ���sz��deep��fa��son�����ͳ��
void dfs1(int u,int f){
    fa[u]=f;
    deep[u]=deep[f]+1;
    sz[u]=1;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v==f){
            continue;
        }
        val[v]=weight[i];//����仯
        dfs1(v,u);
        sz[u]+=sz[v];
        if(sz[son[u]]<sz[v]){
            son[u]=v;
        }
    }
    //cout<<u<<' '<<sz[u]<<endl;
}

//�ڶ���dfs ���top��rk��id
void dfs2(int u,int t){
    top[u]=t;
    id[u]=++cnt;
    rk[cnt]=u;
    if(son[u]){
        //�����ض���  ���ȱ���
        dfs2(son[u],t);
    }
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v!=fa[u]&&v!=son[u]){
            dfs2(v,v);
            //�����ڿ�һ������
        }
    }
}

void dfs(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=f){
            if(fun[v]>(fun[u]+2*w)){
                fun[v]=fun[u]+2*w;
                dfs(v,u);
            }
        }
    }
}

//ע��������
void build(int l,int r,int i){
    cost[i]=1e9;
    if(l==r){
        tree[i]=val[rk[l]];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        tree[i]=tree[i<<1]+tree[i<<1|1];
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl>jobr){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)/2;
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans;
    }
}

int querymin(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return cost[i];
    }
    else{
        int mid=(l+r)/2;
        int ans=INT_MAX;
        if(jobl<=mid){
            ans=min(ans,querymin(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=min(ans,querymin(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

void build1(int l,int r,int i){
    if(l==r){
        cost[i]=fun[rk[l]];
    }
    else{
        int mid=(l+r)/2;
        build1(l,mid,i<<1);
        build1(mid+1,r,i<<1|1);
        cost[i]=min(cost[i<<1],cost[i<<1|1]);
    }
}

inline int qsum(int x,int y){
    int ans=0;
    while(top[x]!=top[y]){
        if(deep[top[x]]<deep[top[y]])
            swap(x,y);
        ans+=query(id[top[x]],id[x],1,n,1);
        x=fa[top[x]];
    }
    if(id[x]>id[y])
        swap(x,y);
    ans+=query(id[x]+1,id[y],1,n,1);
    return ans;
}

inline int qmin(int x,int y){
    int ans=1e9;
    while(top[x]!=top[y]){
        if(deep[top[x]]<deep[top[y]])
            swap(x,y);
        ans=min(ans,querymin(id[top[x]],id[x],1,n,1));
        x=fa[top[x]];
    }
    if(id[x]>id[y])
        swap(x,y);
    ans=min(ans,querymin(id[x],id[y],1,n,1));
    return ans;
}

int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,n,1);
    for(int i=1;i<=n;i++){
        fun[i]=1e9;
    }
    for(int i=1;i<=k;i++){
        int u;
        u=read();
        fun[u]=0;
        heap.push({u,0});
        //dfs(u,0);
    }
    while(!heap.empty()){
        int u=heap.top().first;
        heap.pop();
        if(visit[u]){
            continue;
        }
        visit[u]=true;
        for(int i=head[u];i>0;i=Next[i]){
            int v=to[i];
            int w=weight[i];
            if(!visit[v]&&(2*w+fun[u])<fun[v]){
                fun[v]=2*w+fun[u];
                heap.push({v,fun[u]+2*w});
            }
        }
    }
    build1(1,n,1);
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        //cout<<qsum(u,v)<<' '<<qmin(u,v)<<endl;
        cout<<qsum(u,v)+qmin(u,v)<<endl;
    }
    return 0;
}

