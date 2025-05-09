//P5782
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 16005;
const int MAXM = 40005;

int n,m;
int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
bool instack[MAXN];

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;

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
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,(v%2)?(v+1):(v-1));
        addedge(v,(u%2)?(u+1):(u-1));
    }
    for(int i=1;i<=2*n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=2*n;i+=2){
        if(col[i]==col[i+1]){
            //������Ҫ�� ֱ���˳�
            cout<<"NIE"<<endl;
            return 0;
        }
    }
    for(int i=1;i<=2*n;i+=2){
        if(col[i]>col[i+1])
            cout<<i+1<<endl;
        else
            cout<<i<<endl;
    }
    return 0;
}

