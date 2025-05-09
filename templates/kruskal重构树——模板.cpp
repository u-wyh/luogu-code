// Kruskal�ع���ģ���⣬C++��
// ͼ����n���㣬m������ߣ�ÿ���߸�����Ȩ��ͼ����������ɸ���ͨ�Ĳ���
// һ����q����ѯ��ÿ����ѯ�������µĸ�ʽ
// ��ѯ x y : ��x�͵�yϣ����ͨ���������е�����Ȩϣ������С����ӡ���ֵ
//            ����������޷���ͨ����ӡ"impossible"
// 1 <= n <= 10^5
// 1 <= m <= 3 * 10^5
// 1 <= q <= 10^5
// �������� : https://www.luogu.com.cn/problem/P2245
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;
const int MAXK = 200001;//��1e5��ԭʼ�ڵ�  ��Ҷ�ڵ� ��ô���нڵ�����Ϊ��������
const int MAXM = 300001;
const int MAXH = 20;

int n, m, q;

// ÿ������������Ϣ���ڵ�u���ڵ�v����Ȩw
struct Edge {
   int u, v, w;
};

bool cmp(Edge x, Edge y) {
   return x.w < y.w;
}

Edge edge[MAXM];

// ���鼯
int father[MAXK];
// Kruskal�ع����Ľ�ͼ
int head[MAXK];
int nxt[MAXK];
int to[MAXK];
int cntg;
// Kruskal�ع����ϣ��ڵ��Ȩֵ
int nodeKey[MAXK];
// Kruskal�ع����ϣ��������
int cntu;

// Kruskal�ع����ϣ�dfs���̽�������Ϣ
int dep[MAXK];
int stjump[MAXK][MAXH];

int find(int i) {
   if (i != father[i]) {
       father[i] = find(father[i]);
   }
   return father[i];
}

void addEdge(int u, int v) {
   nxt[++cntg] = head[u];
   to[cntg] = v;
   head[u] = cntg;
}

void kruskalRebuild() {
   for (int i = 1; i <= n; i++) {
       father[i] = i;
   }
   sort(edge + 1, edge + m + 1, cmp);//���߰��ձ�Ȩ����
   cntu = n;
   for (int i = 1; i <= m; i++) {
       int fx = find(edge[i].u);
       int fy = find(edge[i].v);
       if (fx != fy) {
            //����������ڵ㲻��һ������ ��ô�ϲ�  ������Ȩ��ֵΪ��Ȩ
           father[fx] = father[fy] = ++cntu;
           father[cntu] = cntu;
           nodeKey[cntu] = edge[i].w;
           addEdge(cntu, fx);
           addEdge(cntu, fy);
       }
   }
}

//������������Ϣ
void dfs(int u, int fa) {
   dep[u] = dep[fa] + 1;
   stjump[u][0] = fa;
   for (int p = 1; p < MAXH; p++) {
       stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
   }
   for (int e = head[u]; e > 0; e = nxt[e]) {
       dfs(to[e], u);
   }
}

int lca(int a, int b) {
   if (dep[a] < dep[b]) {
       int tmp = a;
       a = b;
       b = tmp;
   }
   for (int p = MAXH - 1; p >= 0; p--) {
       if (dep[stjump[a][p]] >= dep[b]) {
           a = stjump[a][p];
       }
   }
   if (a == b) {
       return a;
   }
   for (int p = MAXH - 1; p >= 0; p--) {
       if (stjump[a][p] != stjump[b][p]) {
           a = stjump[a][p];
           b = stjump[b][p];
       }
   }
   return stjump[a][0];
}

int main() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   cin >> n >> m;
   for (int i = 1; i <= m; i++) {
       cin >> edge[i].u >> edge[i].v >> edge[i].w;
   }
   kruskalRebuild();
   for (int i = 1; i <= cntu; i++) {
       if (i == father[i]) {
            //����ÿ��������������
           dfs(i, 0);
       }
   }
   cin >> q;
   for (int i = 1, x, y; i <= q; i++) {
       cin >> x >> y;
       if (find(x) != find(y)) {
           cout << "impossible" << "\n";
       } else {
           cout << nodeKey[lca(x, y)] << "\n";
       }
   }
   return 0;
}
