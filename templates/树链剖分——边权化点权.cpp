// ��Ȩת��Ϊ��Ȩ��ģ���⣬C++��
// һ����n���ڵ㣬����n-1���ߣ��ڵ�����һ��������ʼʱ���бߵ�ȨֵΪ0
// һ����m��������ÿ������������2�������е�һ��
// ���� P x y : x��y��·���ϣ�ÿ���ߵ�Ȩֵ����1
// ���� Q x y : x��y��֤��ֱ�����ӵģ���ѯ����֮��ı�Ȩ
// 1 <= n��m <= 10^5
// �������� : https://www.luogu.com.cn/problem/P3038
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int n, m;

// ��ʽǰ����
int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int cntg = 0;

// �����ʷ�
int fa[MAXN];
int dep[MAXN];
int siz[MAXN];
int son[MAXN];
int top[MAXN];
int dfn[MAXN];
int cntd = 0;

// �߶���
int sum[MAXN << 2];
int addTag[MAXN << 2];

void addEdge(int u, int v) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

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

void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++cntd;
    if (son[u] == 0) {
        return;
    }
    dfs2(son[u], t);
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa[u] && v != son[u]) {
            dfs2(v, v);
        }
    }
}

void up(int i) {
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
}

void lazy(int i, int v, int len) {
    sum[i] += v * len;
    addTag[i] += v;
}

void down(int i, int ln, int rn) {
    if (addTag[i] != 0) {
        lazy(i << 1, addTag[i], ln);
        lazy(i << 1 | 1, addTag[i], rn);
        addTag[i] = 0;
    }
}

// ��Χ����
void add(int jobl, int jobr, int jobv, int l, int r, int i) {
    //������һ���ܺõķ��� ���Ǵ��ڿ�����jobl>jobr  ������������ԺܺõĽ��
    //���jobl>jobr  ��ôһ����jobl=jobr+1  ����lһ��С�ڵ���r  ����jobl <= l && r <= jobrһ��������
    //��ô����else�� ���jobl<=mid ��ôjobrһ��С��mid  ���jobr>mid  ��ôjoblһ������mid  
    //��������Խ���add�����еݹ� ��ôһ��ֻ�ܽ���һ���ݹ�
    //���ϵݹ� ����һ��������  jobl>mid&&jobr<=mid  �����Ҳ��ֶ��޷�����
    //���յĽ������  �������� һ�������㲻��  ���޼�����
    if (jobl <= l && r <= jobr) {
        lazy(i, jobv, r - l + 1);
    } else {
        int mid = (l + r) >> 1;
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

// �����ѯ
int query(int jobi, int l, int r, int i) {
    if (l == r) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    if (jobi <= mid) {
        return query(jobi, l, mid, i << 1);
    } else {
        return query(jobi, mid + 1, r, i << 1 | 1);
    }
}

// x��y��·���ϣ�ÿ���ߵı�Ȩ����·���ĵ�Ȩ
// ÿ���ߵı�Ȩ����v���������ɵ�ĵ�Ȩ����v
// ����Ҫע�⣡x��y����͹������ȣ��������ӵ�Ȩ��
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
    // x��y����͹������ȣ���Ȩ�����ӣ�
    add(min(dfn[x], dfn[y]) + 1, max(dfn[x], dfn[y]), v, 1, n, 1);
}

// ����x��y֮�������ߵı�Ȩ
int edgeQuery(int x, int y) {
    int down = max(dfn[x], dfn[y]);
    return query(down, 1, n, 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    char op;
    for (int i = 1, x, y; i <= m; i++) {
        cin >> op >> x >> y;
        if (op == 'P') {
            pathAdd(x, y, 1);
        } else {
            cout << edgeQuery(x, y) << "\n";
        }
    }
    return 0;
}
