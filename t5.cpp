// �жϸ�����ͼ�ǲ���һ����
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10;

int n,m;
vector<pair<int,int>>edge[MAXN];
bool vis[MAXN];
bool flag=true;//��ʾ�ж��ǲ���һ����

void dfs(int u,int fa){
    if(vis[u]){
        flag=false;
        return ;
    }
    vis[u]=true;
    if(!flag){
        //��֦  ��ʾ�Ѿ��������� û�б�Ҫ����dfs
        return ;
    }
    for(int i=0;i<(int)edge[u].size();i++){
        int v=edge[u][i].first;
        if(v==fa){
            continue;
        }
        dfs(v,u);
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    if(m!=n-1){
        //�ߵ�Ҫ�󲻷���
        cout<<"����һ����"<<endl;
        return 0;
    }
    dfs(1,0);
    if(!flag){
        //�����ͨ�����д��ڻ�
        cout<<"����һ����"<<endl;
        return 0;
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            //��ֹһ����ͨ����
            cout<<"����һ����"<<endl;
            return 0;
        }
    }
    cout<<"��һ����"<<endl;
    return 0;
}
/*
6 11
1 2 12
1 3 6
1 5 9
1 6 10
2 4 2
2 5 6
3 6 6
3 4 2
4 5 4
4 7 4
5 6 4

6 5
1 2 1
2 4 1
2 3 1
5 6 1 
5 6 1

6 5
1 2 1
1 5 1
5 6 1
2 3 1
2 4 1
*/