// �̸�
// һ����n���ڵ㣬���1~n����n-1�����γ�һ����
// �����������ĵ�
// �������ĵڶ�����ⷽʽ
// ��ĳ���ڵ�Ϊ��ʱ��ÿ�������Ľڵ����������ܽڵ�����һ�룬��ô����ڵ�������
// �������� : http://poj.org/problem?id=3107
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int MAXM = 1000005;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;
int sz[MAXN];
//��¼��ĳ���ڵ�Ϊ�ߵ�ʱ���������нڵ��С
int maxsize[MAXN];
//��¼��ĳ���ڵ�Ϊ���ڵ��ʱ�����������С
int n;
//һ����n���ڵ�  n-1����

void dfs(int u,int f){
    sz[u] = 1;
    // �Ե�ǰ�ڵ�u�����ڵ㣬���������ж��ٽڵ�
    maxsize[u] = 0;
    //��¼���������С
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            dfs(v, u);
            sz[u] += sz[v];
            maxsize[u]=max(maxsize[u],sz[v]);
        }
    }
    maxsize[u] = max(maxsize[u], n - sz[u]);
}

int main()
{
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;
    }
    dfs(1,0);
    for(int i=1;i<=n;i++){
        if(maxsize[i]<=n/2){
            cout<<i<<' ';
        }
        //��಻�ᳬ������
    }
    return 0;
}
//�ڶ��ַ�ʽ�����������ڵ㲻����������һ��
