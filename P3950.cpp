#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n,m;
int val[MAXN];
struct node{
    int u,v;
}edge[MAXN];
int t;

//��ʽǰ���ǽ�ͼ
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int tot=1;

//�߶���
int tree[MAXN<<2];

//�����ʷֲ���
int son[MAXN];//�ض��ӱ��  Ҷ�ӽ��û��
int id[MAXN];//���±�ź�ı��
int rk[MAXN];//���±�ź�ı�Ŷ�Ӧԭ���ı����ʲô
int cnt;
int fa[MAXN];//���׽ڵ���
int deep[MAXN];//�ڵ����
int sz[MAXN];//�Ըýڵ�Ϊ�׵������ڵ�����
int top[MAXN];//����������ͷ���

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
    Next[tot]=head[u];
    to[tot]=v;
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
        dfs1(v,u);
        sz[u]+=sz[v];
        if(sz[son[u]]<sz[v]){
            son[u]=v;
        }
    }
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

//�߶�������
void up(int i){
    tree[i]=min(tree[i<<1],tree[i<<1|1]);
}

//ע��������
void build(int l,int r,int i){
    if(l==r){
        tree[i]=val[rk[l]];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
    //cout<<i<<": "<<l<<' '<<r<<' '<<tree[i]<<endl;
}

void update(int pos,int jobv,int l,int r,int i){
    if(l==r){
        tree[i]=jobv;
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            update(pos,jobv,l,mid,i<<1);
        }
        else{
            update(pos,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl>jobr){
        return 1;
    }
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)/2;
        int ans=1;
        if(jobl<=mid){
            ans=min(ans,query(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=min(ans,query(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

inline int qmin(int x,int y){
    int ans=1;
    while(top[x]!=top[y]){
        if(deep[top[x]]<deep[top[y]])
            swap(x,y);
        ans=min(ans,query(id[top[x]],id[x],1,n,1));
        x=fa[top[x]];
    }
    if(id[x]>id[y])
        swap(x,y);
    ans=min(ans,query(id[x]+1,id[y],1,n,1));
    return ans;
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=1;
    }
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,n,1);
    for(int i=1;i<=m;i++){
        char op;
        int u,v;
        cin>>op;
        if(op=='C'){
            u=read(),v=read();
            edge[++t].u=u;
            edge[t].v=v;
            if(deep[u]>deep[v]){
                update(id[u],0,1,n,1);
            }
            else{
                update(id[v],0,1,n,1);
            }
        }
        else if(op=='Q'){
            u=read(),v=read();
            if(qmin(u,v)==0){
                cout<<"No"<<endl;
            }
            else{
                cout<<"Yes"<<endl;
            }
        }
        else{
            int w=read();
            u=edge[w].u,v=edge[w].v;
            if(deep[u]>deep[v]){
                update(id[u],1,1,n,1);
            }
            else{
                update(id[v],1,1,n,1);
            }
        }
    }
    return 0;
}
