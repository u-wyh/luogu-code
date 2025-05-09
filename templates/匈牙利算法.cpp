#include<bits/stdc++.h>
using namespace std;

int n,m;            //M, N�ֱ��ʾ���Ҳ༯�ϵ�Ԫ������
int graph[20][20]; //�ڽӾ����ͼ
int p[20];         //��¼��ǰ�Ҳ�Ԫ������Ӧ�����Ԫ��
bool vis[20];      //��¼�Ҳ�Ԫ���Ƿ��ѱ����ʹ�

bool match(int i){
    for (int j = 1; j <= m; j++){
        if (graph[i][j] && !vis[j]) {
            //�б���δ����
            vis[j] = true;                 //��¼״̬Ϊ���ʹ�
            if (p[j] == 0 || match(p[j])) {
                //�������ƥ�䣬����ԭ��ƥ������Ԫ�ؿ����ҵ��µ�ƥ��
                p[j] = i;    //��ǰ���Ԫ�س�Ϊ��ǰ�Ҳ�Ԫ�ص���ƥ��
                return true; //����ƥ��ɹ�
            }
        }
    }
    return false; //ѭ����������δ�ҵ�ƥ�䣬����ƥ��ʧ��
}

int Hungarian(){
    int cnt = 0;
    for (int i = 1; i <= n; i++){
        memset(vis, 0, sizeof(vis)); //����vis����
        if (match(i))
            cnt++;
        for(int i=1;i<=n;i++){
            cout<<p[i]<<' ';
        }
        cout<<endl;
    }
    return cnt;
}

int main()
{
    cin>>n>>m;
    int k;
    cin>>k;
    for(int i=1;i<=k;i++){
        int u,v;
        cin>>u>>v;
        graph[u][v]=true;
    }
    cout<<Hungarian()<<endl;
    for(int i=1;i<=n;i++){
        cout<<p[i]<<' ';
    }
    cout<<endl;
    return 0;
}

/*
����
4 4
6
1 2 1 4 2 2 3 1 3 3 4 4


ans:3
*/
