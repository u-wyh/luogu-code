#include<bits/stdc++.h>
using namespace std;
const int MAXN = 250005;

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
int change[MAXN<<2];
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
    change[i]=-1;
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

void changelazy(int i,int v){
    tree[i]=v;
    change[i]=v;
}

void down(int i){
    if(change[i]!=-1){
        changelazy(i<<1,change[i]);
        changelazy(i<<1|1,change[i]);
        change[i]=-1;
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl>jobr){
        return ;
    }
    if(jobl<=l&&r<=jobr){
        changelazy(i,jobv);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            update(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
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
        update(id[top[x]],id[x],val,1,n,1);//�������������ϴ��ڵĹ���
        //�����Ȩ��ʱ��  ͷ���ҲҪ�仯  ��Ϊx���ͷ���ĸ�����
        x=fa[top[x]];
    }
    //������ͬһ��������
    if(id[x]>id[y])
        swap(x,y);
    update(id[x]+1,id[y],val,1,n,1);
    //update(id[x],id[x],-val,1,n,1);//����仯
    //���㹱������
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

signed main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=1;
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,n,1);
    m=read();
    for(int i=1;i<=(m+n-1);i++){
        char op;
        int u,v;
        cin>>op;
        u=read();
        if(op=='A'){
            v=read();
            update(u,v,0);
        }
        else{
            cout<<qsum(1,u)<<endl;
        }
    }
    return 0;
}

