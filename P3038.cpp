//P3038
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n,m;
int val[MAXN];

//��ʽǰ���ǽ�ͼ
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int tot=1;

//�߶���
int tree[MAXN<<2];
int lazy[MAXN<<2];
int len[MAXN<<2];//Ҫ��¼���� ��Ϊ����ӵĻ���ÿһ��Ԫ�ض�Ҫ��

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

//�߶�������
void up(int i){
    tree[i]=tree[i<<1]+tree[i<<1|1];
}

//ע��������
void build(int l,int r,int i){
    lazy[i]=0;
    len[i]=r-l+1;
    if(l==r){
        tree[i]=val[rk[l]];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void downlazy(int i,int v){
    tree[i]+=len[i]*v;
    lazy[i]+=v;
}

void down(int i){
    if(lazy[i]){
        downlazy(i<<1,lazy[i]);
        downlazy(i<<1|1,lazy[i]);
        lazy[i]=0;
    }
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    //cout<<i<<':'<<l<<' '<<r<<' '<<jobl<<' '<<jobr<<endl;
    if(jobl<=l&&r<=jobr){
        downlazy(i,jobv);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)/2;
        down(i);
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

inline void update(int x,int y,int val){
    while(top[x]!=top[y]){
        if(deep[top[x]]<deep[top[y]])
            swap(x,y);
        add(id[top[x]],id[x],val,1,n,1);//�������������ϴ��ڵĹ���
        x=fa[top[x]];
    }
    //������ͬһ��������
    if(id[x]>id[y])
        swap(x,y);
    add(id[x],id[y],val,1,n,1);
    add(id[x],id[x],-val,1,n,1);//����仯
    //���㹱������
}

inline int sum(int x,int y){
    int ans=0;
    while(top[x]!=top[y]){
        if(deep[top[x]]<deep[top[y]])
            swap(x,y);
        ans+=query(id[top[x]],id[x],1,n,1);
        x=fa[top[x]];
    }
    if(id[x]>id[y])
        swap(x,y);
    ans+=query(id[x],id[y],1,n,1);
    ans-=query(id[x],id[x],1,n,1);//����仯
    return ans;
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<n;i++){
        int u,v,w=0;
        u=read(),v=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int u,v;
        char op;
        cin>>op;
        u=read(),v=read();
        if(op=='P'){
            update(u,v,1);
        }
        else{
            cout<<sum(u,v)<<endl;
        }
    }
    return 0;
}
