#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;
const int MAXM = 5e4+5;

//������ʽǰ����
int head[MAXN];
int Next[MAXM<<1];
int to[MAXM<<1];
int cnt0=1;

//��ɫ��ʽǰ����
int head1[MAXN];
int Next1[MAXM<<1];
int to1[MAXM<<1];
int cnt1=1;

//tarjan
int dfn[MAXN],low[MAXN];
int st[MAXN],top1;
int color,Time;
int col[MAXN];
int val[MAXN];
int n,m;

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

int read(){
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

void addedge(int u,int v){
    Next[cnt0]=head[u];
    to[cnt0]=v;
    head[u]=cnt0++;
}

void addedge1(int u,int v){
    Next1[cnt1]=head1[u];
    to1[cnt1]=v;
    head1[u]=cnt1++;
}

void tarjan(int u,int f,int tot){
    dfn[u] = low[u] = ++Time;
	st[++top1]=u;

	for (int i = head[u]; i ; i=Next[i]) {
		int v = to[i];
		if(v==f&&(i-1)==((tot-1)^1)){
            continue;
		}
		if (!dfn[v]) {
			tarjan(v, u,i);
			low[u] = min(low[u], low[v]);
		}
		else {
            low[u]=min(low[u],dfn[v]);
		}
	}
	if(dfn[u]==low[u]){
        col[u]=++color;
        while(st[top1]!=u){
            col[st[top1--]]=color;
        }
        top1--;
    }
}

//����Ϊ�����ʷ�
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

//ע��������
void build(int l,int r,int i){
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
    return ans;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i,0,0);
        }
    }
    for(int i=1;i<=n;i++){
        val[col[i]]++;
    }
    for(int i=1;i<=n;i++){
        for(int j=head[i];j;j=Next[j]){
            int v=to[j];
            if(col[i]!=col[v]){
                addedge1(col[i],col[v]);
                addedge1(col[v],col[i]);
            }
        }
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,color,1);
    for(int i=1;i<=m;i++){
        int u,v;
        u=read();
        v=read();
        cout<<sum(col[u],col[v])<<endl;
    }
    return 0;
}
