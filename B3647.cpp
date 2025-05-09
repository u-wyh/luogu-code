#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 5000;

int n,m,ans;
int dis[MAXN][MAXN];

void build() {
    for (int i = 1; i <= n ; i++) {
        for (int j = 1; j <= n; j++) {
            dis[i][j] = INT_MAX;
            if(i==j)
                dis[i][j]=0;
        }
    }
}

void floyd() {
    // O(N^3)�Ĺ���
    // ö��ÿ������
    // ע�⣬����Ҫ����ö�٣�����Ҫ����ö�٣�����Ҫ����ö�٣�
    for (int bridge = 1; bridge <= n; bridge++) { // ����
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // i -> .....bridge .... -> j
                // distance[i][j]�ܲ�������
                // distance[i][j] = min ( distance[i][j] , distance[i][bridge] + distance[bridge][j])
                if (dis[i][bridge] != INT_MAX
                        && dis[bridge][j] != INT_MAX
                        && dis[i][j] > dis[i][bridge] + dis[bridge][j]) {
                    dis[i][j] = dis[i][bridge] + dis[bridge][j];
                }
            }
        }
    }
}

int main()
{
    cin>>n>>m;
    build();
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        dis[u][v]=min(dis[u][v],w);
        dis[v][u]=min(dis[v][u],w);
    }
    floyd();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<dis[i][j]<<' ';
        }
        cout<<endl;
    }
    return 0;
}

