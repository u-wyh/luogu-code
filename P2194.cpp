#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 3e5+5;
const int MOD = 1e9+7;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;

int cost[MAXN];
int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
int val[MAXN],sz[MAXN];
bool instack[MAXN];
int n,m;
int ans=0,kind=1;

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
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void tarjan(int x){
    //cout<<x<<' '<<777<<endl;
    dfn[x]=++Time;
    low[x]=Time;
    st[++top]=x;
    instack[x]=true;
    for(int i=head[x];i;i=Next[i]){
        int v=to[i];
        if(!dfn[v]){
            //��ʾ����ڵ�û�б����ʹ�
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(instack[v]){
            //��ʾ��������ǻ����� һ����ͬһ�����ϵ�
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x]){
        col[x]=++color;
        //�����нڵ㰴����ɫ����  �������
        while(st[top]!=x){
            //cout<<top<<endl;
            //����ͬһ��ǿ��ͨ����
            col[st[top]]=color;
            instack[st[top]]=false;
            top--;
        }
        instack[x]=false;
        top--;
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        cost[i]=read();
    }
    m=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=color;i++){
        val[i]=INT_MAX;
    }
    for(int i=1;i<=n;i++){
        if(cost[i]<val[col[i]]){
            val[col[i]]=cost[i];
            sz[col[i]]=1;
        }
        else if(cost[i]==val[col[i]]){
            sz[col[i]]++;
        }
    }
    for(int i=1;i<=color;i++){
        kind*=sz[i];
        kind%=MOD;
        ans+=val[i];
    }
    cout<<ans<<' '<<kind<<endl;
    return 0;
}
