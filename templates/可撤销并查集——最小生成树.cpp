// ͬ����С�������C++��
// һ����n���㣬m������ߣ�ÿ�����б�Ȩ��ͼ��֤����ͨ��
// һ����q�β�ѯ��ÿ����ѯ����������k����ʾ�ò�ѯ�漰k����
// Ȼ�����θ���k���ߵı�ţ���ӡ��k�����ܷ�ͬʱ������һ����С��������
// 1 <= n��m��q�����в�ѯ�漰�ߵ����� <= 5 * 10^5
// �������� : https://www.luogu.com.cn/problem/CF891C
// �������� : https://codeforces.com/problemset/problem/891/C
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
//������ʵ�õ���kruskal�������е�һ�����ʣ�
//�������б�Ȩ��ͬ�ı�  ���۰���ʲô˳��  ���յõ�����ͨ�Զ���һ����
//����ָ�Ĳ���˵����ѡ�ı���һ���ģ�Ҳ����ѡ��ı��ǹ̶��ģ�  ����˵�������γɵ���ͨ���еĵ���һ����
//�����1 2�������ڵ���ĳ�ֱ�˳��������  ����ͨ��  ��ô������˳���������ͬ�ı�Ȩ��  Ҳһ������ͨ��

//�������߼��� ���еı߰��ձ�Ȩ������
//���������漰���ı�ȫ���ռ����� Ҳ���ձ�Ȩ����  Ȼ����ͬһ������ı߻���Ϊһ����
//ÿ�ν�С�������ı�ȫ������kruskal������С������  Ȼ���ж����������ı��ܷ������С������  ������ô����������ڵ�����𰸾���false
//Ȼ�������������Ϣȫ������  ��Ϊ����һ������ܱ�Ȩ�������һ�� ֻ��������������Ų�ͬ  Ϊ�������Ժ����Ӱ��
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500001;

int n, m, q, k;

struct Edge {
    int u, v, w;
};

bool EdgeCmp(Edge x, Edge y) {
    return x.w < y.w;
}

struct Query {
    int u, v, w, i;
};

bool QueryCmp(Query x, Query y) {
    if(x.w != y.w) {
        return x.w < y.w;
    } else {
        return x.i < y.i;
    }
}
Edge edge[MAXN];
Query queries[MAXN];

int father[MAXN];
int siz[MAXN];
//ջ
int rollback[MAXN << 1][2];
int opsize;

bool ans[MAXN];

int find(int i) {
    while (i != father[i]) {
        i = father[i];//û�б�ƽ��
    }
    return i;
}

void Union(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (siz[fx] < siz[fy]) {
        int tmp = fx;
        fx = fy;
        fy = tmp;
    }
    father[fy] = fx;
    siz[fx] += siz[fy];
    //��������ջ
    rollback[++opsize][0] = fx;
    rollback[opsize][1] = fy;
}

void undo() {
    int fx = rollback[opsize][0];
    int fy = rollback[opsize--][1];
    father[fy] = fy;
    siz[fx] -= siz[fy];
}

void prepare() {
    for (int i = 1; i <= n; i++) {
        father[i] = i;
        siz[i] = 1;
    }
    sort(edge + 1, edge + m + 1, EdgeCmp);//���еı߰��ձ�Ȩ����
    sort(queries + 1, queries + k + 1, QueryCmp);//���е����ⰴ�ձ�Ȩ�����������
    for (int i = 1; i <= q; i++) {
        ans[i] = true;
    }
}

void compute() {
    int ei = 1, queryId, unionCnt;
    for (int l = 1, r = 1; l <= k; l = ++r) {
        while (r + 1 <= k && queries[l].w == queries[r + 1].w && queries[l].i == queries[r + 1].i) {
            //���������
            r++;
        }
        for (; ei <= m && edge[ei].w < queries[l].w; ei++) {
            if (find(edge[ei].u) != find(edge[ei].v)) {
                Union(edge[ei].u, edge[ei].v);
            }
        }
        queryId = queries[l].i;
        if (!ans[queryId]) {
            //��ǰ���ǲ��Ե���  ��ôֱ�ӽ��� û���жϵı�Ҫ
            continue;
        }
        unionCnt = 0;
        for (int i = l; i <= r; i++) {
            if (find(queries[i].u) == find(queries[i].v)) {
                ans[queryId] = false;
                break;
            } else {
                Union(queries[i].u, queries[i].v);
                unionCnt++;
            }
        }
        for (int i = 1; i <= unionCnt; i++) {
            //��λ���
            undo();
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
    }
    cin >> q;
    k = 0;
    for (int i = 1, s; i <= q; i++) {
        cin >> s;
        for (int j = 1, ei; j <= s; j++) {
            cin >> ei;
            queries[++k].u = edge[ei].u;
            queries[k].v = edge[ei].v;
            queries[k].w = edge[ei].w;
            queries[k].i = i;
        }
    }
    prepare();
    compute();
    for (int i = 1; i <= q; i++) {
        if (ans[i]) {
            cout << "YES" << "\n";
        } else {
            cout << "NO" << "\n";
        }
    }
    return 0;
}