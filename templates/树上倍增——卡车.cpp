// ��������
// һ����n�����У����1 ~ n
// һ����m��˫���·��ÿ����·(u, v, w)��ʾ��һ������Ϊw����u��v��˫���·
// ��һ�㵽��һ���·;�У��������ز��ܳ���ÿһ����·������
// ÿ����ѯ(a, b)��ʾ��a��b��·���У������������������Ƕ���
// �����a��b�޷������ô��Ϊ����-1
// һ����q����ѯ�����ش�����
// 1 <= n <= 10^4
// 1 <= m <= 5 * 10^4
// 1 <= q <= 3 * 10^4
// 0 <= w <= 10^5
// 1 <= u, v, a, b <= n
// �������� : https://www.luogu.com.cn/problem/P1967
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10001;
const int MAXM = 50001;
const int LIMIT = 21;

int power;
struct node{
    int u,v,w;
}edge[MAXM];
//һ��ʼ��Ҫֱ�ӽ�ͼ  Ҫ�����������
// ���鼯
int father[MAXN];
// �������п�����ɭ�֣�������Ҫ�жϽڵ��Ƿ���ʹ���
bool visited[MAXN];
// �����������ͼ
int head[MAXN];
int Next[MAXM << 1];
int to[MAXM << 1];
int weight[MAXM << 1];
int cnt=1;
int deep[MAXN];
// stjump[u][p] : u�ڵ�������2�Ĵη���������ʲô�ڵ�
int stjump[MAXN][LIMIT];
// stmin[u][p] : u�ڵ�������2�Ĵη�����·���У���С��Ȩֵ
int stmin[MAXN][LIMIT];
int n,m,q;

void build() {
    power = log2(n);
    cnt = 1;
    for (int i = 1; i <= n; i++) {
        father[i] = i;
    }
}
//��ʼ�����鼯

bool cmp(node a,node b){
    return a.w>b.w;
}

int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}

void addEdge(int u, int v, int w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void kruskal() {
    sort(edge+1, edge+ m + 1, cmp);
    for (int i = 1, a, b, fa, fb; i <= m; i++) {
        a = edge[i].u;
        b = edge[i].v;
        fa = find(a);
        fb = find(b);
        if (fa != fb) {
            father[fa] = fb;
            addEdge(a, b, edge[i].w);
            addEdge(b, a, edge[i].w);
        }
    }
}
//ʹ��k�㷨�������������

void dfs(int u, int w, int f) {
    //w��uf�ı�Ȩ  ����һ��������   ��Ϊ���������������
    visited[u] = true;
    if (f == 0) {
        deep[u] = 1;
        stjump[u][0] = u;
        stmin[u][0] = INT_MAX;
    } else {
        deep[u] = deep[f] + 1;
        stjump[u][0] = f;
        stmin[u][0] = w;
    }
    for (int p = 1; p <= power; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
        stmin[u][p] = min(stmin[u][p - 1], stmin[stjump[u][p - 1]][p - 1]);
    }
    for (int e = head[u]; e != 0; e = Next[e]) {
        if (!visited[to[e]]) {
            dfs(to[e], weight[e], u);
        }
    }
}

int lca(int a, int b) {
    if (find(a) != find(b)) {
        return -1;
    }
    if (deep[a] < deep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    int ans = INT_MAX;
    for (int p = power; p >= 0; p--) {
        if (deep[stjump[a][p]] >= deep[b]) {
            ans = min(ans, stmin[a][p]);
            a = stjump[a][p];
        }
    }
    if (a == b) {
        return ans;
    }
    for (int p = power; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            ans = min(ans, min(stmin[a][p], stmin[b][p]));
            a = stjump[a][p];
            b = stjump[b][p];
        }
    }
    ans =min(ans,min(stmin[a][0], stmin[b][0]));
    return ans;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>edge[i].u>>edge[i].v>>edge[i].w;
    }
    build();
    kruskal();
    //��Ϊ������Ͽ����в�ֹһ������  ������ͨ��һ����ʽʵ�ֽ�ͼ
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, 0, 0);
            //��ÿ�����Ž���һ��st  deep
        }
    }
    cin>>q;
    for (int i = 1, a, b; i <= q; i++) {
        cin>>a>>b;
        cout<<lca(a, b)<<endl;;
    }
    return 0;
}
