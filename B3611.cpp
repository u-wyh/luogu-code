#include<bits/stdc++.h>
using namespace std;

int n;
int dis[105][105];

void floyd() {
    // O(N^3)�Ĺ���
    // ö��ÿ������
    // ע�⣬����Ҫ����ö�٣�����Ҫ����ö�٣�����Ҫ����ö�٣�
    for (int bridge = 1; bridge <= n; bridge++) { // ����
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dis[i][j] == 0&&dis[i][bridge] != 0&& dis[bridge][j] != 0) {
                    dis[i][j] = 1;
                }
            }
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>dis[i][j];
        }
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
