//P3379
// tarjan�㷨�ⷨ
// �������� : https://www.luogu.com.cn/problem/P3379
// �ύ���µ�code���ύʱ��������ĳ�"Main"
// C++��ôд��ͨ����java����Ϊ�ݹ����̫�����ջ
// java��ͨ����д���ο����ڿ�Code03_Tarjan2�ļ�
//tarjan�㷨��lca�����߲���  ����˼��Ҳ�ܼ� lca����˵��������������ͬʱ������lca��������
//�����ܱ���������  ��Ȼ����Ҳ��ͬʱ������lca�����Ƚڵ��������  ��������̫����
//�����������  ��Ѱ������ͬʱ���ֵ�������ͷ��� ��lca
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
const int LIMIT = 20;

int n,m,root;
int head[MAXN];
int Next[MAXN];
int to[MAXN];
int tcnt=1;
//��ͼ����ʽǰ����

int headQuery[MAXN];
int queryNext[MAXN << 1];
int queryTo[MAXN << 1];
// ����ı�ţ�һ���д𰸿���֪����д����
int queryIndex[MAXN << 1];
int qcnt=1;
//�������ʽǰ����   ����һ������ı������  �������

// ĳ���ڵ��Ƿ���ʹ�
bool visited[MAXN];
// ���鼯
int father[MAXN];
// �ռ��Ĵ�
int ans[MAXN];

void build(){
    for(int i=1;i<=n;i++){
        father[i]=i;
    }
}

int Find(int i) {
    if (i != father[i]) {
        father[i] = Find(father[i]);
    }
    return father[i];
}

void tarjan(int u, int f) {
    visited[u] = true;
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            tarjan(v, u);//���µݹ�  ֱ��Ҷ�ڵ�
            father[v] = u;
        }
    }
    for (int e = headQuery[u], v; e != 0; e = queryNext[e]) {
        v = queryTo[e];
        if (visited[v]) {
            //���˵�������ڵ��Ѿ������ʹ�  �ſ��Խ��д���д
            ans[queryIndex[e]] = Find(v);
            //��д�Ĵ�������ڵ����ڲ��鼯��ͷ���
        }
    }
}

int main()
{
    cin>>n>>m>>root;
    build();
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;

        Next[tcnt]=head[u];
        to[tcnt]=v;
        head[u]=tcnt++;

        Next[tcnt]=head[v];
        to[tcnt]=u;
        head[v]=tcnt++;

    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;

        queryNext[qcnt] = headQuery[u];
		queryTo[qcnt] = v;
		queryIndex[qcnt] = i;
		headQuery[u] = qcnt++;

        queryNext[qcnt] = headQuery[v];
		queryTo[qcnt] = u;
		queryIndex[qcnt] = i;
		headQuery[v] = qcnt++;
    }
    tarjan(root,0);
    for(int i=1;i<=m;i++){
        if(ans[i]==0)
            ans[i]=root;
        cout<<ans[i]<<endl;
    }
    return 0;
}
