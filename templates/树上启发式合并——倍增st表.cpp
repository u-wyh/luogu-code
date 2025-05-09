// ����������C++��
// һ����n���ڵ㣬���1~n������ÿ���ڵ�ĸ��׽ڵ��ţ����׽ڵ�Ϊ0��˵����ǰ�ڵ���ĳ������ͷ
// ע�⣬n���ڵ���ɵ���ɭ�ֽṹ�����������ɿ���
// һ����m����ѯ��ÿ����ѯ x k����������
// ���x������k�ľ��룬û�����Ƚڵ㣬��ӡ0
// ���x������k�ľ��룬���ҵ����Ƚڵ�a����ô��a������k�ľ��룬����x֮�⣬���ܻ��������ڵ�
// ��Щ�ڵ����x��k�����ף���ӡ������׵�����
// 1 <= n��m <= 10^5
// �������� : https://www.luogu.com.cn/problem/CF208E
// �������� : https://codeforces.com/problemset/problem/208/E
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXH = 20;

int n, m;
bool root[MAXN];

// ��ʽǰ���ǽ�ͼ
int headg[MAXN];
int nextg[MAXN];
int tog[MAXN];
int cntg;

// �����б�
int headq[MAXN];
int nextq[MAXN];
int ansiq[MAXN];
int kq[MAXN];
int cntq;

// �����ʷ�
int siz[MAXN];
int dep[MAXN];
int son[MAXN];
int stjump[MAXN][MAXH];//��ʾ����ڵ��2��j�η�����

// ��������ʽ�ϲ�
int depCnt[MAXN];
int ans[MAXN];

void addEdge(int u, int v) {
    nextg[++cntg] = headg[u];
    tog[cntg] = v;
    headg[u] = cntg;
}

void addQuestion(int u, int i, int k) {
    nextq[++cntq] = headq[u];
    ansiq[cntq] = i;//��ʾ������
    kq[cntq] = k;
    headq[u] = cntq;
}

void dfs1(int u, int fa) {
    siz[u] = 1;
    dep[u] = dep[fa] + 1;
    stjump[u][0] = fa;
    for (int p = 1; p < MAXH; p++) {
        stjump[u][p] = stjump[ stjump[u][p - 1] ][p - 1];
    }
    for (int e = headg[u]; e > 0; e = nextg[e]) {
        dfs1(tog[e], u);
    }
    for (int e = headg[u], v; e > 0; e = nextg[e]) {
        v = tog[e];
        siz[u] += siz[v];
        if (son[u] == 0 || siz[son[u]] < siz[v]) {
            son[u] = v;
        }
    }
}

//��ѯu��k������
int kAncestor(int u, int k) {
    for (int p = MAXH - 1; p >= 0; p--) {
        if (k >= (1 << p)) {
            k -= (1 << p);
            u = stjump[u][p];
        }
    }
    return u;
}

void effect(int u) {
    depCnt[dep[u]]++;
    for (int e = headg[u]; e > 0; e = nextg[e]) {
        effect(tog[e]);
    }
}

void cancle(int u) {
    depCnt[dep[u]]--;
    for (int e = headg[u]; e > 0; e = nextg[e]) {
        cancle(tog[e]);
    }
}

void dfs2(int u, int keep) {
    for (int e = headg[u], v; e > 0; e = nextg[e]) {
        v = tog[e];
        if (v != son[u]) {
            dfs2(v, 0);
        }
    }
    if (son[u] != 0) {
        dfs2(son[u], 1);
    }
    depCnt[dep[u]]++;
    for (int e = headg[u], v; e > 0; e = nextg[e]) {
        v = tog[e];
        if (v != son[u]) {
            effect(v);
        }
    }
    for (int i = headq[u]; i > 0; i = nextq[i]) {
    	ans[ansiq[i]] = depCnt[dep[u] + kq[i]];
    }
    if (keep == 0) {
        cancle(u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1, father; i <= n; i++) {
        cin >> father;
        if (father == 0) {
        	root[i] = true;
        } else {
            addEdge(father, i);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (root[i]) {
            dfs1(i, 0);
        }
    }
    cin >> m;
    for (int i = 1, u, k, kfather; i <= m; i++) {
        cin >> u >> k;
        kfather = kAncestor(u, k);
        if (kfather != 0) {
            addQuestion(kfather, i, k);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (root[i]) {
            dfs2(i, 0);//����ط�����Ҫд0  ��Ȼ���Ǹ�  ��Ϊ���ǲ�������Ӱ����������
        }
    }
    for (int i = 1; i <= m; i++) {
        if (ans[i] == 0) {
            cout << "0 ";
        } else {
            cout << ans[i] - 1 << " ";
        }
    }
    cout << "\n";
    return 0;
}
