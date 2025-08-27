#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e4+5;
const int MAXQ = 3e4+5;
const int MAXK = 1e3+5;
const int MAXT = 1e6+5;
const int MAXH = 20;
const int BASE = 1e7+19;
const int MOD = 1e9+7;

int n,k,q;

int v[MAXN];
int w[MAXN];

int op[MAXQ];
int x[MAXQ];
int y[MAXQ];

int from[MAXN];
int to[MAXN];

int head[MAXQ<<2];
int nxt[MAXT];
int tov[MAXT];
int tow[MAXT];
int cnt=1;

long long dp[MAXK];
long long backup[MAXH][MAXK];
long long ans[MAXQ];

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
    nxt[cnt]=head[u];
    tov[cnt]=v;
    tow[cnt]=w;
    head[u]=cnt++;
}

void add(int jobl,int jobr,int jobv,int jobw,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addedge(i,jobv,jobw);
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid){
            add(jobl,jobr,jobv,jobw,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,jobw,mid+1,r,i<<1|1);
        }
    }
}

void prepare(){
    for(int i=1;i<=n;i++){
        from[i]=1,to[i]=q;
    }
    for(int i=1;i<=q;i++){
        if(op[i]==1){
            n++;
            v[n]=x[i];
            w[n]=y[i];
            from[n]=i;
            to[n]=q;
        }
        else if(op[i]==2){
            to[x[i]]=i-1;
        }
    }
    for(int i=1;i<=n;i++){
        if(from[i]<=to[i]){
            add(from[i],to[i],v[i],w[i],1,q,1);
        }
    }
}

void clone(long long *a,long long *b){
    for(int i=0;i<=k;i++){
        a[i]=b[i];
    }
}

void dfs(int l,int r,int i,int d){
    clone(backup[d],dp);
    for(int ei=head[i];ei;ei=nxt[ei]){
        int v=tov[ei];
        int w=tow[ei];
        for(int j=k;j>=w;j--){
            dp[j]=max(dp[j],dp[j-w]+v);
        }
    }
    if(l==r){
        if(op[l]==3){
            long long res=0;
            long long base=1;
            for(int j=1;j<=k;j++){
                res=(res+dp[j]*base)%MOD;
                base=(base*BASE)%MOD;
            }
            ans[l]=res;
        }
    }
    else{
        int mid=(l+r)>>1;
        dfs(l,mid,i<<1,d+1);
        dfs(mid+1,r,i<<1|1,d+1);
    }
    clone(dp,backup[d]);
}

int main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++){
        v[i]=read(),w[i]=read();
    }
    q=read();
    for(int i=1;i<=q;i++){
        op[i]=read();
        if(op[i]==1){
            x[i]=read(),y[i]=read();
        }
        else if(op[i]==2){
            x[i]=read();
        }
    }
    prepare();
    dfs(1,q,1,1);
    for(int i=1;i<=q;i++){
        if(op[i]==3){
            cout<<ans[i]<<endl;
        }
    }
    return 0;
}