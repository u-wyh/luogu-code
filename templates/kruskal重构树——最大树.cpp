// youyou�ľ�ѵ��C++��
// ͼ����n���㣬m������ߣ�ÿ���߸�����ͬ�ı�Ȩ��ͼ����������ɸ���ͨ�Ĳ���
// һ����q��������ÿ�������������µ����������е�һ��
// ���� 1 x   : ���Ʊ���limit����limit��ֵ�ĳ�x
// ���� 2 x   : ��x�����߹��κα�ȨС��limit�ıߣ���ӡ��ʱx���ڵ���ͨ�����С
// ���� 3 x y : ��x���ߵı�Ȩ�޸�Ϊy����Ŀ��֤�޸�֮�󣬵�x���ߵı�Ȩ��������
// 1 <= n��m��q <= 4 * 10^5
// �������� : https://www.luogu.com.cn/problem/P9638
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;
const int MAXK = 800001;
const int MAXM = 400001;
const int MAXH = 20;

int n, m, q;

struct Edge {
    int u, v, w, i;
};

bool cmp(Edge x, Edge y) {
    return x.w > y.w;
}
// ÿ���ߵ���Ϣ���ڵ�u���ڵ�v����Ȩw���ߵı��i
Edge edge[MAXM];
// �ߵı�Ŷ�Ӧ�ع����ϵĵ�ı��  Ϊ�˷������3
int edgeToTree[MAXM];

// ���鼯
int father[MAXK];

// Kruskal�ع���
int head[MAXK];
int nxt[MAXK];
int to[MAXK];
int cntg;
int nodeKey[MAXK];
int cntu;

// ����dfs��Kruskal�ع����Ľڵ㣬���������м���Ҷ�ڵ�  Ϊ��ͳ�Ʋ���2�Ĵ�
int leafsiz[MAXK];
// ����dfs��Kruskal�ع����Ľڵ㣬������
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
    sort(edge + 1, edge + m + 1, cmp);//�����ĿҪ��ʵ�����ǽ��߰��մӴ�С����
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
            edgeToTree[edge[i].i] = cntu;//�Ƚ��������Ҫ��¼����ڵ���������ת������
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
        //˵����������ͼ�ϵĵ�  ��Ҷ�ڵ�
        leafsiz[u] = 1;
    } else {
        leafsiz[u] = 0;
    }
    for (int e = head[u]; e > 0; e = nxt[e]) {
        leafsiz[u] += leafsiz[to[e]];//ͳ����uΪ�׵�������һ���ж���Ҷ�ڵ�
    }
}

//��ѯu�ڵ�������ͨ����  ����Ϊlimit�Ŀ��Ե���Ľڵ�����
int query(int u, int limit) {
    for (int p = MAXH - 1; p >= 0; p--) {
        if (stjump[u][p] > 0 && nodeKey[stjump[u][p]] >= limit) {
            //����  �϶���Խ����Խ�� ����ǰ���Ǳ�����������ȴ���
            //��ʹ������ȴ���  ����ڵ��ȨֵҲ�������limit����
            u = stjump[u][p];
        }
    }
    return leafsiz[u];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
        edge[i].i = i;
    }
    kruskalRebuild();
    for (int i = 1; i <= cntu; i++) {
        if (i == father[i]) {
            dfs(i, 0);
        }
    }
    int op, x, y, limit = 0;
    for (int i = 1; i <= q; i++) {
        cin >> op;
        if (op == 1) {
            cin >> limit;
        } else if (op == 2) {
            cin >> x;
            cout << query(x, limit) << "\n";
        } else {
            cin >> x >> y;
            if (edgeToTree[x] != 0) {
                nodeKey[edgeToTree[x]] = y;
            }
        }
    }
    return 0;
}
