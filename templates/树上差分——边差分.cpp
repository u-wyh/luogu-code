// �߲��ʵս
// ʹͼ����ͨ�ķ�����
// ��n���ڵ㣬����n-1���ϱ�ʹ�����ӳ�һ�������ٸ���m���±߶����������
// ������ж������������ͼ����ͨ���жϵ������߱�����һ���ϱߺ�һ���±�
// ���ط�����
// �������� : http://poj.org/problem?id=3417
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ����������
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
const int MAXN = 100001;
const int LIMIT = 17;

int power;
int n, m;
int num[MAXN];

int head[MAXN];
int Next[MAXN << 1];
int to[MAXN << 1];
int cnt=1;

int deep[MAXN];
int stjump[MAXN][LIMIT];

int ans;

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

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
//��������������ǽ���deep  st����Ϣ

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

void dfs2(int u, int f) {
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            dfs2(v, u);
        }
    }
    for (int e = head[u], v, w; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            w = num[v];
            if (w == 0) {
                ans += m;
            } else if (w == 1) {
                ans += 1;
            } else {
                ans += 0;
            }
            num[u] += num[v];
        }
    }
}

int main()
{
    scanf("%d %d",&n,&m);
    power=log2(n);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0);
    for(int i=1;i<=m;i++){
        int u,v,Lca;
        scanf("%d %d",&u,&v);
        Lca=lca(u,v);
        num[u]++,num[v]++;
        num[Lca]-=2;
    }
    dfs2(1,0);
    cout<<ans<<endl;
    return 0;
}