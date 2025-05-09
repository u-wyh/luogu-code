// �����ʷ�ģ���⣬C++��
// һ����n���ڵ㣬����n-1���ߣ��ڵ�����һ����
// ����ÿ���ڵ�ĳ�ʼȨֵ����������ͷ�ڵ���root
// һ����m��������ÿ�ֲ���������4�������е�һ��
// ���� 1 x y v : x��y��·���ϣ�ÿ���ڵ�ֵ����v
// ���� 2 x y   : x��y��·���ϣ���ӡ���нڵ�ֵ���ۼӺ�
// ���� 3 x v   : xΪͷ�������ϣ�ÿ���ڵ�ֵ����v
// ���� 4 x     : xΪͷ�������ϣ���ӡ���нڵ�ֵ���ۼӺ�
// 1 <= n��m <= 10^5
// 1 <= MOD <= 2^30
// �����ֵ��Ϊint����
// ��ѯ����ʱ����ӡ(��ѯ��� % MOD)����Ŀ�����MODֵ
// �������� : https://www.luogu.com.cn/problem/P3384
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int n, m, root, MOD;
int arr[MAXN];

int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int cntg = 0;

int fa[MAXN];
int dep[MAXN];
int siz[MAXN];//������С
int son[MAXN];//�ض��ӽڵ���
int top[MAXN];//��������ͷ�ڵ�
int dfn[MAXN];//dfn���
int seg[MAXN];//dfn��Ŷ�Ӧ��ԭʼ�ڵ���
int cntd = 0;

long long sum[MAXN << 2];
long long addTag[MAXN << 2];

void addEdge(int u, int v) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

// �����ڵ�u���ڵ�u���ϵĸ��ڵ���f
// dfs1�Ĺ���ȥ���� fa dep siz son
void dfs1(int u, int f) {
    fa[u] = f;
    dep[u] = dep[f] + 1;
    siz[u] = 1;
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != f) {
            dfs1(v, u);
        }
    }
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != f) {
            siz[u] += siz[v];
            if (son[u] == 0 || siz[son[u]] < siz[v]) {
                son[u] = v;
            }
        }
    }
}

// �����ڵ�u���ڵ�u����������ͷ�ڵ���t
// dfs2�Ĺ���ȥ���� top dfn seg
void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++cntd;
    seg[cntd] = u;
    if (son[u] == 0) {
        return;
    }
    dfs2(son[u], t);//ȥ �ض��Ӽ�������
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa[u] && v != son[u]) {
            //������Լ���һ������ �Լ���ͷ���
            dfs2(v, v);
        }
    }
}

void up(int i) {
    sum[i] = (sum[i << 1] + sum[i << 1 | 1]) % MOD;
}

void lazy(int i, long long v, int n) {
    sum[i] = (sum[i] + v * n) % MOD;
    addTag[i] = (addTag[i] + v) % MOD;
}

void down(int i, int ln, int rn) {
    if (addTag[i] != 0) {
        lazy(i << 1, addTag[i], ln);
        lazy(i << 1 | 1, addTag[i], rn);
        addTag[i] = 0;
    }
}

void build(int l, int r, int i) {
    if (l == r) {
        sum[i] = arr[seg[l]] % MOD;
    } else {
        int mid = (l + r) / 2;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
}

void add(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy(i, jobv, r - l + 1);
    } else {
        int mid = (l + r) / 2;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) {
            add(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

long long query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) / 2;
    down(i, mid - l + 1, r - mid);
    long long ans = 0;
    if (jobl <= mid) {
        ans = (ans + query(jobl, jobr, l, mid, i << 1)) % MOD;
    }
    if (jobr > mid) {
        ans = (ans + query(jobl, jobr, mid + 1, r, i << 1 | 1)) % MOD;
    }
    return ans;
}

// ��x��y��·���ϣ����нڵ��ֵ����v
void pathAdd(int x, int y, int v) {
    while (top[x] != top[y]) {
        if (dep[top[x]] <= dep[top[y]]) {
            add(dfn[top[y]], dfn[y], v, 1, n, 1);
            y = fa[top[y]];
        } else {
            add(dfn[top[x]], dfn[x], v, 1, n, 1);
            x = fa[top[x]];
        }
    }
    add(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), v, 1, n, 1);
}

// x�������ϣ����нڵ��ֵ����v
void subtreeAdd(int x, int v) {
    add(dfn[x], dfn[x] + siz[x] - 1, v, 1, n, 1);
}

// ��x��y��·���ϣ���ѯ���нڵ���ۼӺ�
long long pathSum(int x, int y) {
    long long ans = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] <= dep[top[y]]) {
            ans = (ans + query(dfn[top[y]], dfn[y], 1, n, 1)) % MOD;
            y = fa[top[y]];
        } else {
            ans = (ans + query(dfn[top[x]], dfn[x], 1, n, 1)) % MOD;
            x = fa[top[x]];
        }
    }
    ans = (ans + query(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), 1, n, 1)) % MOD;
    return ans;
}

// x�������ϣ���ѯ���нڵ���ۼӺ�
long long subtreeSum(int x) {
    return query(dfn[x], dfn[x] + siz[x] - 1, 1, n, 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> root >> MOD;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs1(root, 0);
    dfs2(root, root);
    build(1, n, 1);
    for (int i = 1, op, x, y, v; i <= m; i++) {
        cin >> op;
        if (op == 1) {
            cin >> x >> y >> v;
            pathAdd(x, y, v);
        } else if (op == 2) {
            cin >> x >> y;
            cout << pathSum(x, y) << "\n";
        } else if (op == 3) {
            cin >> x >> v;
            subtreeAdd(x, v);
        } else {
            cin >> x;
            cout << subtreeSum(x) << "\n";
        }
    }
    return 0;
}
