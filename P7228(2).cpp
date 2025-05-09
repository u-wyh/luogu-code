#include<iostream>
#define endl '\n'
using namespace std;
#define MAXN 100001
int n;
struct edge{
    int v;
    int next;
}e[MAXN<<1];
int head[MAXN];
bool towards[MAXN];//ȷ�ϱ�Ҫ��Ҫ��������
bool f=0;//��ʼΪ0��1��û��ϵ
bool vis[MAXN];
void dfs(int p)
{
    if(vis[p])
        return;
    vis[p]=1;
    f^=1;
    for(int i=head[p];i;i=e[i].next)
    {
        if(vis[e[i].v])
            continue;
        //f^=1;
        if(i>MAXN)
            towards[i-MAXN]=f^1;
        else
            towards[i]=f;
        dfs(e[i].v);
        //f^=1;
    }
    f^=1;
}
int main()
{
    cin>>n;
    for(int i=1,j=MAXN+1,u,v;i<n;i++,j++)
    {
        cin>>u>>v;
        e[i].v=v,e[i].next=head[u],head[u]=i;//�ӱ�
        e[j].v=u,e[j].next=head[v],head[v]=j;//����ͼ�ӷ����
    }
    dfs(1);
    for(int i=1;i<n;i++)
        cout<<towards[i]<<endl;
    return 0;
}
