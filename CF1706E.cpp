// �ӱ�ֱ����ͨ��C++��
// ͼ����n���㣬m������ߣ���ı��1~n���ߵı��1~m�����е㶼��ͨ
// һ����q����ѯ��ÿ����ѯ��ʽ����
// ��ѯ l r : ����Ҫ������ǰ���ٵıߣ�����ʹ��[l, r]�е����е���ͨ
// 1 <= n <= 10^5
// 1 <= m��q <= 2 * 10^5
// �������� : https://www.luogu.com.cn/problem/CF1706E
// �������� : https://codeforces.com/problemset/problem/1706/E
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
//�����Ҫ����ű�Ϊdfn���
//���Ҫ��ѯһ���������нڵ��lca  ʵ���Ͼ����������dfn�����С�ĺ������������lca
//���ǿ��Թ���һ��stmin stmax�������ѯ����dfn����С�����ֵ
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXK = 200001;
const int MAXM = 200001;
const int MAXH = 20;

struct Edge {
    int u, v, w;
};

bool cmp(Edge x, Edge y) {
    return x.w < y.w;
}

int t, n, m, q;
Edge edge[MAXM];

// ���鼯
int father[MAXK];

// Kruskal�ع���
int head[MAXK];
int nxt[MAXK];
int to[MAXK];
int cntg;
int nodeKey[MAXK];
int cntu;

// ���
int dep[MAXK];
// dfn��
int dfn[MAXK];
// seg[i] = j���������Ͻڵ��dfn���Ϊi����Ӧԭʼ�ڵ�ı��Ϊj
int seg[MAXK];
// ���ϵı�����
int stjump[MAXK][MAXH];
// dfn��ŵļ���
int cntd;

// һά����ı�������ѯ�������ֵ����Сֵ
int lg2[MAXN];
int stmax[MAXN][MAXH];
int stmin[MAXN][MAXH];

void clear() {
    cntg = 0;
    cntd = 0;
    for (int i = 1; i <= n * 2; i++) {
        head[i] = 0;
    }
}

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
    sort(edge + 1, edge + m + 1, cmp);
    cntu = n;
    for (int i = 1, fx, fy; i <= m; i++) {
        fx = find(edge[i].u);
        fy = find(edge[i].v);
        if (fx != fy) {
            father[fx] = father[fy] = ++cntu;
            father[cntu] = cntu;
            nodeKey[cntu] = edge[i].w;
            addEdge(cntu, fx);
            addEdge(cntu, fy);
        }
    }
}

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    dfn[u] = ++cntd;
    seg[cntd] = u;
    stjump[u][0] = fa;
    for (int p = 1; p < MAXH; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    for (int e = head[u]; e > 0; e = nxt[e]) {
        dfs(to[e], u);
    }
}

// ���������ϵ�st������117��������ϸ�Ľ���
void buildst() {
	lg2[0] = -1;
    for (int i = 1; i <= n; i++) {
    	lg2[i] = lg2[i >> 1] + 1;
        stmax[i][0] = dfn[i];
        stmin[i][0] = dfn[i];
    }
    for (int p = 1; p <= lg2[n]; p++) {
        for (int i = 1; i + (1 << p) - 1 <= n; i++) {
            stmax[i][p] = max(stmax[i][p - 1], stmax[i + (1 << (p - 1))][p - 1]);
            stmin[i][p] = min(stmin[i][p - 1], stmin[i + (1 << (p - 1))][p - 1]);
        }
    }
}

// ����st��[l..r]��Χ�ϵ���Сֵ������117��������ϸ�Ľ���
int dfnmin(int l, int r) {
    int p = lg2[r - l + 1];
    int ans = min(stmin[l][p], stmin[r - (1 << p) + 1][p]);
    return ans;
}

// ����st��[l..r]��Χ�ϵ����ֵ������117��������ϸ�Ľ���
int dfnmax(int l, int r) {
    int p = lg2[r - l + 1];
    int ans = max(stmax[l][p], stmax[r - (1 << p) + 1][p]);
    return ans;
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

int query(int l, int r) {
    int x = seg[dfnmin(l, r)];
    int y = seg[dfnmax(l, r)];//��Ϊ��Ӧ��ԭʼ���
    return nodeKey[lca(x, y)];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    for (int test = 1; test <= t; test++) {
        cin >> n >> m >> q;
        for (int i = 1; i <= m; i++) {
            cin >> edge[i].u >> edge[i].v;
            edge[i].w = i;
        }
        clear();
        kruskalRebuild();
        dfs(cntu, 0);
        buildst();
        for (int i = 1, l, r; i <= q; i++) {
            cin >> l >> r;
            if (l == r) {
                cout << 0 << " ";
            } else {
                cout << query(l, r) << " ";
            }
        }
        cout << "\n";
    }
    return 0;
}