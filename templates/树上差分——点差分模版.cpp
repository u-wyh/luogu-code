// ���ϵ���ģ��(�ݹ��)
// ��n���ڵ��γ�һ������һ��ʼ���е�Ȩ����0
// �����ܶ������ÿ������(a,b)��ʾ��a��b·�������е�ĵ�Ȩ����1
// ���в�����ɺ󣬷������ϵ�����Ȩ
// �������� : https://www.luogu.com.cn/problem/P3128
// �ύ���µ�code���ύʱ��������ĳ�"Main"
// C++��ôд��ͨ����java����Ϊ�ݹ����̫�����ջ
// java��ͨ����д���ο����ڿ�Code01_MaxFlow2�ļ�
//�����н���a��b��·�������е�Ȩ��v  �൱��a+v b+v  lca-v  lcafa-v
//���ͳ�Ƶ�ʱ�� ����һ���ڵ�  �ȱ��������ӽڵ�  Ȼ������ڵ�����ӽڵ�ĵ�Ȩ
//���յõ��Լ��ĵ�Ȩ
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 50005;
const int LIMIT = 16;

int n,m;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int deep[MAXN],stjump[MAXN][LIMIT];
int power;
int num[MAXN];//��¼��Ȩ

//��������������ǽ���deep  st����Ϣ
void dfs1(int u, int f) {
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;
    for (int p = 1; p <= power; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    //���u��deep  stjump
    for (int e = head[u]; e != 0; e = Next[e]) {
        if (to[e] != f) {
            dfs1(to[e], u);
        }
        //���µݹ�
    }
}

int lca(int a, int b) {
    if (deep[a] < deep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    //ȷ����С��ϵ
    for (int p = power; p >= 0; p--) {
        if (deep[stjump[a][p]] >= deep[b]) {
            a = stjump[a][p];
        }
    }
    //���Ƚ����߱�Ϊͬһ�߶�
    if (a == b) {
        return a;
    }
    //�����ͬ˵���������ȹ�ϵ
    for (int p = power; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            a = stjump[a][p];
            b = stjump[b][p];
        }
        //�ж�������Ƿ���Ϲ���
    }
    return stjump[a][0];
    //���ǽ�ͷ������������Ϊ0  ʵ����û��0
}

//�����޸ĺ����Ϣ
void dfs2(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs2(v,u);
        }
    }
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            num[u]+=num[v];
        }
    }
}

int main()
{
    cin>>n>>m;
    power=log2(n);
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
    dfs1(1,0);
    for(int i=1;i<=m;i++){
        int u,v,lcafather,Lca;
        cin>>u>>v;
        Lca=lca(u,v);
        lcafather=stjump[Lca][0];
        num[u]++;
        num[v]++;
        num[Lca]--;
        num[lcafather]--;
    }
    dfs2(1,0);
    int maxans=0;
    for(int i=1;i<=n;i++){
        maxans=max(maxans,num[i]);
    }
    cout<<maxans;
    return 0;
}

