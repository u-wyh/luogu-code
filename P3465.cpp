#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;

int n,m;
int ans[MAXN];
bool vis[MAXN];
bool fanzu;

int head[MAXN];
int to[MAXM<<1];
int Next[MAXM<<1];
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

void dfs2(int u,int v){
    if(ans[u]){
        //ֻ�п�ʼ�趨�ĸ� ans��0
        dfs2(ans[u],u);
    }
    ans[u]=v;
}

void dfs(int u,int f){
    vis[u]=true;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v==f){
            continue;//�����ظ���
        }
        if(vis[v]){
            //��ʾ�����˷�������
            if(!fanzu){
                //��������ͨ����ǰû�г��ֹ�����  ��ô��������
                //����Ͳ�Ҫ��
                fanzu=true;
                dfs2(v,u);//���ظı�ߵķ���
            }
        }
        else{
            ans[v]=u;
            dfs(v,u);
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            //��ʾ�����ͨ��δ�����ʹ�
            fanzu=false;
            dfs(i,0);
            if(!fanzu){
                //������֮����û�з�����Ϊ
                cout<<"NIE"<<endl;
                return 0;
            }
        }
    }
    cout<<"TAK"<<endl;
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
