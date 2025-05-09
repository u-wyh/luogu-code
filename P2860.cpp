//P2860
//��ʵ���Ǳ�˫
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
const int MAXM = 20010;

int n,m;
int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
int in[MAXN];

bool vis[MAXM];
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=2;

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

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void tarjan(int x){
    dfn[x]=++Time;
    low[x]=Time;
    st[++top]=x;
    for(int i=head[x];i;i=Next[i]){
        if(vis[i]){
            continue;
        }
        vis[i]=vis[i^1]=true;
        int v=to[i];
        if(!dfn[v]){
            //��ʾ����ڵ�û�б����ʹ�
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else{
            //��ʾ��������ǻ����� һ����ͬһ�����ϵ�
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x]){
        col[x]=++color;
        //�����нڵ㰴����ɫ����  �������
        while(st[top]!=x){
            //����ͬһ��ǿ��ͨ����
            col[st[top]]=color;
            top--;
        }
        top--;
    }
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
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=head[i];j;j=Next[j]){
            int v=to[j];
            if(col[i]!=col[v]){
                in[col[i]]++,in[col[v]]++;
            }
        }
    }
    int cnt1=0;
    for(int i=1;i<=color;i++){
        if(in[i]==2){
            //��Ϊ����in++��ʱ��  ʵ�����Ǽ�������
            //���ֻ��һ�εĻ�  ����in==1
            cnt1++;
        }
    }
    cout<<(cnt1+1)/2<<endl;
    return 0;
}
