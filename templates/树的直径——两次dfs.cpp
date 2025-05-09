//����dfs
// ����ֱ��ģ��(����dfs)
// ����һ��������Ȩ����Ϊ������ֱ������
// �������� : https://www.luogu.com.cn/problem/U81904
// �ύ���µ�code���ύʱ��������ĳ�"Main"
// �����޷�ͨ������������Ϊ�����и���
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 500005;

int n;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;
// ֱ���Ŀ�ʼ��
int start;
// ֱ���Ľ�����
int en;
// ֱ������
int diameter;
// dist[i] : �ӹ涨��ͷ�ڵ�������ߵ�i�ľ���
int dist[MAXN];
// last[i] : �ӹ涨��ͷ�ڵ������i�ڵ����һ���ڵ�
int last[MAXN];

void dfs(int u,int f,int w){
    last[u]=f;
    dist[u]=dist[f]+w;
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            dfs(to[i],u,weight[i]);
        }
    }
}

void road() {
    dfs(1, 0, 0);
    //�������������  һ�㶼��1
    start = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[start]) {
            start = i;
        }
    }
    //ѡ�������������ĵ�  ��Ϊͷ���
    //��Ϊ��ȨΪ��  ���Զ�������ڵ����  ��Զ�ĵ�һ����ֱ���˵��е�һ��
    dfs(start, 0, 0);
    en = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[en]) {
            en = i;
        }
    }
    diameter = dist[en];
}
//���ε���dfs

int main()
{
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;

        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        weight[cnt]=w;
        head[v]=cnt++;
    }
    road();
    cout<<diameter;
    return 0;
}
