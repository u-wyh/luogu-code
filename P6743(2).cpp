#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int n,m;
bool vis[MAXN<<1];//��ʾ�������Ƿ񾭹�
bool in[MAXN];
int st[MAXN],r=0;

//�����Ĺؼ�������θ��߱��
//��Ϊ���Ӧ����α�Ƿ��ʹ��ı�
//vis[i]=vis[i^1]=true   ��Ҫ���Ŵ�2��ʼ  23 45 67 89
void addedge(int u,int v){
    Next[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}

void dfs(int u){
    for(int i=head[u];i>0;i=head[u]){
        head[u]=Next[i];
        if(vis[i]){
            //��ʾ�����߷��ʹ���  ����������
            continue;
        }
        vis[i]=vis[i^1]=true;
        //������ ����ȫ����Ϊ1
        dfs(to[i]);
    }
    if(in[u]){
        //��ʾ�Ѿ���Ϊ��һ����  ��ô��������
        //����uһ�������
        while(st[r]!=u&&r){
            in[st[r]]=false;//��ʾ�Ѿ�������
            cout<<st[r--]<<' ';
        }
        cout<<st[r--]<<endl;//��ʾ�û������е�ȫ������
    }
    else in[u]=true;
    st[++r]=u;
    //���ֻ��һ����ͨ�ĵ� ��ôֱ�Ӽ���ջ
    //��ʹ�Ǿ�����������ж�  ��ô�ͻ���Ϊ�»�������ٴο�ʼ
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1);
    return 0;
}
