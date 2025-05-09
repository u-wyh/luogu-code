// ƽ����Ϊ
// һ����n���ڵ㣬���1~n����n-1�����γ�һ����
// �������ĵ㣬�������ĵ���������Ľڵ���
// �������ĵ�һ����ⷽʽ
// ��ĳ���ڵ�Ϊ��ʱ����������Ľڵ������٣���ô����ڵ�������
// �������� : http://poj.org/problem?id=1655
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10005;
const int MAXM = 100005;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;
int sz[MAXN];
//��¼��ĳ���ڵ�Ϊ�ߵ�ʱ���������нڵ��С
int center=0,best=INT_MAX;
//���Ƚ�����λ�� ��  ���������ʼ��
int n;
//һ����n���ڵ�  n-1����

void dfs(int u,int f){
    sz[u] = 1;
    // �Ե�ǰ�ڵ�u�����ڵ㣬���������ж��ٽڵ�
    int maxsub = 0;
    //��¼���������С
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            dfs(v, u);
            sz[u] += sz[v];
            maxsub = max(maxsub, sz[v]);
        }
    }
    //�������� maxsub��������ĺ��ӽڵ�Ϊ����������С���ֵ
    maxsub = max(maxsub, n - sz[u]);
    //n-sz[u]��ʾ�����Ե�ǰuΪ��  ���ĸ��׽ڵ������������ֵ��������Ϊ��  үүΪ���׵��ӽڵ㣩
    // ��ĿҪ���ҵ������С������
    if (maxsub < best || (maxsub == best && u < center)) {
        best = maxsub;
        center = u;
    }
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
    cout<<center;
    return 0;
}
//��һ���жϷ�������������ڵ�����
