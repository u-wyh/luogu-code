// P4255
// �����ǳ����صĵط���������ͨ��������������Ϣ
// ����  a�ų���  ��3��������A  4��������B  ��ô����a->A ȨֵΪ3   a->B ȨֵΪ4
// ��ô��� a�ų��к�b�ų��кϲ���  ��ô����������
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 19260817;
const int MAXN = 4e5+5;
const int MAXT = 3*MAXN;

int n,m,q;

struct Edge{
    int u,v;
}edge[MAXN];
bool ok[MAXN];//��ʾ����·�Ƿ���Դ���

int cnt=1;
int head[MAXN];
int nxt[MAXT];
int to[MAXT];
int weight[MAXT];
map<int,int>vis[MAXN];//vis[i][j]���������  ����  ����i  ��������Ϊj��  ��  ����Ƕ���

struct node{
    int op,x,n,c;
}nums[MAXN];

int sz[MAXN];
int fa[MAXN];

stack<int>ans;

int fac[MAXN*10];

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

int power(int a,int b){
    long long ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return (int)ans;
}

inline void addedge(int u,int v,int w){
    int num=vis[u][v];//��ʾ�Ƿ��й�u���к�����v������
    if(num==0){
        vis[u][v]=cnt;

        nxt[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;
    }
    else{
        weight[num]+=w;
    }
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx==fy){
        return ;
    }
    if(vis[fx].size()>vis[fy].size()){
        swap(fx,fy);//����ʽ�ϲ�  �����ٵĸ�����������ȥ
    }
    for(int i=head[fx];i;i=nxt[i]){
        addedge(fy,to[i],weight[i]);
    }
    sz[fy]+=sz[fx];
    fa[fx]=fy;
}

int query(int x,int num,int c){
    long long res=1;
    int all=sz[x];
    c=vis[x][c];
    if(weight[c]<num){
        return 15578602;
    }
    int need=weight[c];
    // cout<<' '<<all<<' '<<need<<' '<<num<<endl;
    int t1=(long long)(fac[need]*fac[all-num])%MOD;
    int t2=(long long)(fac[need-num]*fac[all])%MOD;
    res=t1*power(t2,MOD-2);
    res=(res%MOD+MOD)%MOD;
    return (int)res;
}

signed main()
{
    n=read(),m=read(),q=read();
    fac[0]=1;
    for(int i=1;i<=10*n;i++){
        fac[i]=(long long)(fac[i-1]*i)%MOD;
    }
    for(int i=1;i<=n;i++){
        int v,w;
        w=read(),v=read();
        addedge(i,v,w);//��ʾ����i  ��w������v ����
        sz[i]=w;
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        edge[i].u=read(),edge[i].v=read();
        ok[i]=true;
    }
    for(int i=1;i<=q;i++){
        nums[i].op=read();
        if(nums[i].op==1){
            nums[i].x=read(),nums[i].n=read(),nums[i].c=read();
            addedge(nums[i].x,nums[i].c,nums[i].n);
            sz[nums[i].x]+=nums[i].n;
        }
        else if(nums[i].op==2){
            nums[i].x=read();
            ok[nums[i].x]=false;
        }
        else{
            nums[i].x=read(),nums[i].n=read(),nums[i].c=read();
        }
    }
    for(int i=1;i<=m;i++){
        if(ok[i]){
            un(edge[i].u,edge[i].v);
        }
    }
    for(int i=q;i>0;i--){
        if(nums[i].op==3){
            ans.push(query(nums[i].x,nums[i].n,nums[i].c));
        }
        else if(nums[i].op==2){
            un(edge[nums[i].x].u,edge[nums[i].x].v);
        }
        else{
            int x=find(nums[i].x);
            sz[x]-=nums[i].n;
            int pos=vis[x][nums[i].c];
            weight[pos]-=nums[i].n;
        }
    }
    while(!ans.empty()){
        printf("%lld\n",ans.top());
        ans.pop();
    }
    return 0;
}