// ɾ�ߺͲ�ѯ��C++��
// ͼ����n���㣬m������ߣ���ʼʱ��Ȩ����ͬ��ͼ����������ɸ���ͨ�Ĳ���
// һ����q��������ÿ���������������������е�һ��
// ���� 1 x : ��x���ڵ���ͨ�����У������yӵ�����ĵ�Ȩ
//            ��ӡy�ĵ�Ȩ��Ȼ���y�ĵ�Ȩ�޸�Ϊ0
// ���� 2 x : ɾ����x����
// 1 <= n <= 2 * 10^5    1 <= m <= 3 * 10^5    1 <= q <= 5 * 10^5
// �������� : https://www.luogu.com.cn/problem/CF1416D
// �������� : https://codeforces.com/problemset/problem/1416/D
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
//�����ֻ��ΪҶ�ڵ㸳��dfn���  ������
//�����Ļ� �߶�������ͨ�������ѯ �͵����޸�
//�����������ĵط�����θ��߸���Ȩ
//��ʼ���ն����ڵı�  ��1��ʼ����Ȩ
//��ɾ���ı߽������������  ��ɾ���ı߱�Ȩ����
//�����Ļ�ÿ��ɾһ���� �ͻ�ʹ��limit-1  �����ѯ
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200001;
const int MAXK = 400001;
const int MAXM = 300001;
const int MAXQ = 500001;
const int MAXH = 20;

struct Edge {
    int u, v, w;
};

bool cmp(Edge x, Edge y) {
    return x.w < y.w;
}

int n, m, q;

// �ڵ�ֵ�����飬��Ҫ��¼���߶���ҲҪʹ��
int node[MAXN];
// ���бߵ����飬������ɾ������������ÿ���ߵ�Ȩֵ
Edge edge[MAXM];
// ��¼���в���
int ques[MAXQ][2];

// ���鼯
int father[MAXK];

// Kruskal�ع���
int head[MAXK];
int nxt[MAXK];
int to[MAXK];
int cntg;
int nodeKey[MAXK];
int cntu;

// ������
int stjump[MAXK][MAXH];
// �����ϵ�Ҷ�ڵ����
int leafsiz[MAXK];
// ������Ҷ�ڵ��dfn�����Сֵ
int leafDfnMin[MAXK];
// leafseg[i] = j����ʾdfn���Ϊi��Ҷ�ڵ㣬ԭʼ���Ϊj
int leafseg[MAXK];
// dfn�ļ���
int cntd;

// �߶������±���dfn��ţ�ά����Χ�ڣ�ӵ������Ȩ��dfn���
int maxValueDfn[MAXN << 2];

//�����еı߸��ϱ�Ȩ
void prepare() {
    for (int i = 1; i <= q; i++) {
        if (ques[i][0] == 2) {
            edge[ques[i][1]].w = -1;
        }
    }
    int weight = 0;
    for (int i = 1; i <= m; i++) {
        if (edge[i].w != -1) {
            edge[i].w = ++weight;
        }
    }
    for (int i = q; i >= 1; i--) {
        if (ques[i][0] == 2) {
            edge[ques[i][1]].w = ++weight;
        }
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
    for (int i = 1; i <= m; i++) {
        int fx = find(edge[i].u);
        int fy = find(edge[i].v);
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
    stjump[u][0] = fa;
    for (int p = 1; p < MAXH; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    for (int e = head[u]; e > 0; e = nxt[e]) {
        dfs(to[e], u);
    }
    if (u <= n) {
        leafsiz[u] = 1;
        leafDfnMin[u] = ++cntd;
        leafseg[cntd] = u;
    } else {
        leafsiz[u] = 0;
        leafDfnMin[u] = n + 1;
    }
    for (int e = head[u]; e > 0; e = nxt[e]) {
        leafsiz[u] += leafsiz[to[e]];
        leafDfnMin[u] = min(leafDfnMin[u], leafDfnMin[to[e]]);
    }
}

int getAncestor(int u, int limit) {
    for (int p = MAXH - 1; p >= 0; p--) {
        if (stjump[u][p] > 0 && nodeKey[stjump[u][p]] <= limit) {
            u = stjump[u][p];
        }
    }
    return u;
}

void up(int i) {
    int l = i << 1;
    int r = i << 1 | 1;
    if (node[leafseg[maxValueDfn[l]]] > node[leafseg[maxValueDfn[r]]]) {
        maxValueDfn[i] = maxValueDfn[l];
    } else {
        maxValueDfn[i] = maxValueDfn[r];
    }
}

void build(int l, int r, int i) {
    if (l == r) {
        maxValueDfn[i] = l;
    } else {
        int mid = (l + r) / 2;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
}

// dfn���Ϊjobi����Ȩ���³�jobv
void update(int jobi, int jobv, int l, int r, int i) {
    if (l == r) {
        node[leafseg[jobi]] = jobv;
    } else {
        int mid = (l + r) / 2;
        if (jobi <= mid) {
            update(jobi, jobv, l, mid, i << 1);
        } else {
            update(jobi, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

// dfn��Χ[jobl..jobr]���ĸ��ڵ�ӵ������Ȩ�����ظýڵ��dfn���
int query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return maxValueDfn[i];
    } else {
        int mid = (l + r) / 2;
        int ldfn = 0, rdfn = 0;
        if (jobl <= mid) {
        	ldfn = query(jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid) {
        	rdfn = query(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
        if (node[leafseg[ldfn]] > node[leafseg[rdfn]]) {
            return ldfn;
        } else {
            return rdfn;
        }
    }
}

int queryAndUpdate(int x, int limit) {
    int anc = getAncestor(x, limit);
    int dfn = query(leafDfnMin[anc], leafDfnMin[anc] + leafsiz[anc] - 1, 1, n, 1);
    int ans = node[leafseg[dfn]];
    update(dfn, 0, 1, n, 1);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        cin >> node[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> edge[i].u >> edge[i].v;
        edge[i].w = 0;
    }
    for (int i = 1; i <= q; i++) {
        cin >> ques[i][0] >> ques[i][1];
    }
    prepare();
    kruskalRebuild();
    for (int i = 1; i <= cntu; i++) {
        if (i == father[i]) {
            dfs(i, 0);
        }
    }
    build(1, n, 1);
    int limit = m;
    for (int i = 1; i <= q; i++) {
        if (ques[i][0] == 1) {
            cout << queryAndUpdate(ques[i][1], limit) << "\n";
        } else {
            limit--;
        }
    }
    return 0;
}
