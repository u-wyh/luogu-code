// Floyd�㷨ģ�棨��ȣ�
// �������� : https://www.luogu.com.cn/problem/P2910
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ�������д��룬���������ĳ�Main������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 101;
const int MAXM = 10001;

int n,m,ans;
int dis[MAXN][MAXN];
int path[MAXM];

void build() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dis[i][j] = INT_MAX;
        }
    }
}

void floyd() {
    // O(N^3)�Ĺ���
    // ö��ÿ������
    // ע�⣬����Ҫ����ö�٣�����Ҫ����ö�٣�����Ҫ����ö�٣�
    for (int bridge = 0; bridge < n; bridge++) { // ����
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
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
    //build();
    //��������£�����Ҫ�����Լ������ڽӾ����
    for(int i=1;i<=m;i++){
        cin>>path[i];
        path[i]--;
        //ע���±�Ķ�Ӧ
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>dis[i][j];
            //�����ֱ�Ӹ������ڽӾ���  ����Ҫ���ǽ���
        }
    }
    floyd();
    for(int i=1;i<m;i++){
        ans+=dis[path[i]][path[i+1]];
    }
    cout<<ans;
    return 0;
}
