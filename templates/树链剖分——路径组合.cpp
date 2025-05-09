// ���Σ�C++��
// һ����n�����У�����n-1���ߣ���������һ������ÿ�����и�����ʼ�ı�ʯ�۸�
// һ����m��������������������
// ���� x y v : ����x������y�����·;�У������ѡ��һ�����뱦ʯ
//              �����н��Ĺ����У���ѡһ��������ʯ���Դ˻������
//              ��ӡ���ܻ�õ�����������Ϊ��������ӡ0
//              ���������;����;���г��еı�ʯ�۸�����v
// 1 <= n��m <= 5 * 10^4
// 0 <= �κ�ʱ��ı�ʯ�۸� <= 10^9
// �������� : https://www.luogu.com.cn/problem/P3976
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50001;
const int INF  = 1000000001;

int n, m;
int arr[MAXN];//��ʼʱ��ɫ����

//��ʽǰ����
int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int cntg = 0;

//�����ʷ�
int fa[MAXN];
int dep[MAXN];
int siz[MAXN];
int son[MAXN];
int top[MAXN];
int dfn[MAXN];
int seg[MAXN];
int cntd = 0;

//�߶���
int maxv[MAXN << 2];//�������ֵ
int minv[MAXN << 2];//������Сֵ
int lprofit[MAXN << 2];//�����з�������  ����Ǵ������������
int rprofit[MAXN << 2];//�����з�������  ����Ǵ��ҵ����������
// �߶�����Χ���ӵ���������Ϣ
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
    for (int e = head[u]; e > 0; e = nxt[e]) {
        int v = to[e];
        if (v != f) {
            dfs1(v, u);
        }
    }
    for (int e = head[u]; e > 0; e = nxt[e]) {
        int v = to[e];
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
    seg[cntd] = u;
    if (son[u] == 0) {
        return;
    }
    dfs2(son[u], t);
    for (int e = head[u]; e > 0; e = nxt[e]) {
        int v = to[e];
        if (v != fa[u] && v != son[u]) {
            dfs2(v, v);
        }
    }
}

void up(int i) {
    int l = i << 1;
    int r = i << 1 | 1;
    maxv[i] = max(maxv[l], maxv[r]);
    minv[i] = min(minv[l], minv[r]);
    lprofit[i] = max({lprofit[l], lprofit[r], maxv[r] - minv[l]});
    rprofit[i] = max({rprofit[l], rprofit[r], maxv[l] - minv[r]});
}

void lazy(int i, int v) {
    maxv[i] += v;
    minv[i] += v;
    addTag[i] += v;
}

void down(int i) {
    if (addTag[i] != 0) {
        lazy(i << 1, addTag[i]);
        lazy(i << 1 | 1, addTag[i]);
        addTag[i] = 0;
    }
}

void build(int l, int r, int i) {
    if (l == r) {
        maxv[i] = minv[i] = arr[seg[l]];
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
}

void add(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy(i, jobv);
    } else {
        down(i);
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            add(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

// ans[0] : �߶�������ಿ�ֵ�max
// ans[1] : �߶�������ಿ�ֵ�min
// ans[2] : �߶�������ಿ�ֵ�lprofit
// ans[3] : �߶�������ಿ�ֵ�rprofit
// rmax : �߶������Ҳಿ�ֵ�max
// rmin : �߶������Ҳಿ�ֵ�min
// rlpro : �߶������Ҳಿ�ֵ�lprofit
// rrpro : �߶������Ҳಿ�ֵ�rprofit
// ��ಿ�ֺ��Ҳಿ�ֵ���Ϣ������һ��õ�������Χ��max��min��lprofit��rprofit
void merge(int ans[], int rmax, int rmin, int rlpro, int rrpro) {
    int lmax  = ans[0];
    int lmin  = ans[1];
    int llpro = ans[2];
    int lrpro = ans[3];
    ans[0] = max(lmax, rmax);
    ans[1] = min(lmin, rmin);
    ans[2] = max({llpro, rlpro, rmax - lmin});
    ans[3] = max({lrpro, rrpro, lmax - rmin});
    //��up��������Ϣ��Ϸ�ʽһ��
}

void query(int ans[], int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        //����ǰ�ռ�����Ϣ��Ŀǰ����Ϣ�ϲ�  ��ǰ����Ϣ�϶�����ಿ�ֵ���Ϣ
        merge(ans, maxv[i], minv[i], lprofit[i], rprofit[i]);
    } else {
        down(i);
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            query(ans, jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid) {
            query(ans, jobl, jobr, mid + 1, r, i << 1 | 1);
        }
    }
}

// ans[0] : �߶�������ಿ�ֵ�max
// ans[1] : �߶�������ಿ�ֵ�min
// ans[2] : �߶�������ಿ�ֵ�lprofit
// ans[3] : �߶�������ಿ�ֵ�rprofit
// �����߶�����ѯ��չ�������и��Ҳ��ֵ���Ϣ���Ͻ�ans���������ϳ�������Ϣ
void query(int ans[], int jobl, int jobr) {
    ans[0] = -INF;
    ans[1] =  INF;
    ans[2] =  0;
    ans[3] =  0;
    //��ʼʱ��ans����  ���ֵ����Ϊ��Сֵ  ��Сֵ����Ϊ�ϴ�ֵ  ������������Ϊ0  �����������
    query(ans, jobl, jobr, 1, n, 1);
}

void clone(int *a, int *b) {
    a[0] = b[0];
    a[1] = b[1];
    a[2] = b[2];
    a[3] = b[3];
}

int compute(int x, int y, int v) {
    int tmpx = x;
    int tmpy = y;
    int xpath[4] = {-INF, INF, 0, 0};//�ռ�x��lca����Ϣ
    int ypath[4] = {-INF, INF, 0, 0};//�ռ�y��lca����Ϣ
    int cur[4];
    while (top[x] != top[y]) {
        if (dep[top[x]] <= dep[top[y]]) {
            query(cur, dfn[top[y]], dfn[y]);//����ѯ����Ϣ�͵�cur������
            merge(cur, ypath[0], ypath[1], ypath[2], ypath[3]);//��ypath����Ϣ���ܵ�cur��  ��Ϊcur�����
            clone(ypath, cur);//�ٽ�cur��Ϣ�ͻص�ypath
            y = fa[top[y]];
        } else {
            query(cur, dfn[top[x]], dfn[x]);
            merge(cur, xpath[0], xpath[1], xpath[2], xpath[3]);
            clone(xpath, cur);
            x = fa[top[x]];
        }
    }
    //���ݽڵ������ж����һ��������һ����
    if (dep[x] <= dep[y]) {
        query(cur, dfn[x], dfn[y]);
        merge(cur, ypath[0], ypath[1], ypath[2], ypath[3]);
        clone(ypath, cur);
    } else {
        query(cur, dfn[y], dfn[x]);
        merge(cur, xpath[0], xpath[1], xpath[2], xpath[3]);
        clone(xpath, cur);
    }
    //ʵ����x��lca�Ǵ��ҵ���Ĺ���  lca��y�Ǵ�����
    int ans = max({xpath[3], ypath[2], ypath[0] - xpath[1]});

    //�������ϵ�Ȩֵ������ĿҪ�����v
    x = tmpx;
    y = tmpy;
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
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, n, 1);
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int x, y, v;
        cin >> x >> y >> v;
        cout << compute(x, y, v) << "\n";
    }
    return 0;
}
