// ����Ż���·����C++��
// һ����n���ڵ㣬���1~n������n-1���ߣ����нڵ�����һ������1�Žڵ�Ϊ��ͷ
// ÿ�����϶���һ���ַ����ַ���Χ[a~v]���ַ�һ��22�֣����Ż���·���Ķ�������
// �ڵ�a���ڵ�b��·����������бߵ��ַ��ռ����������������гɻ��Ĵ�����·�������Ż���·��
// ��ӡ1~nÿ���ڵ�Ϊͷ�������У�����Ż���·���ĳ���
// 1 <= n <= 5 * 10^5
// �������� : https://www.luogu.com.cn/problem/CF741D
// �������� : https://codeforces.com/problemset/problem/741/D
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500001;
const int MAXV = 22;// �ַ��������22��

int n;

// ��ʽǰ����
int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int weight[MAXN];
int cnt = 0;

// �����ʷ�
int siz[MAXN];
int dep[MAXN];
int eor[MAXN];//��ʾ��ͷ��������ýڵ��Ȩֵ
int son[MAXN];

// ��������ʽ�ϲ�
int maxdep[1 << MAXV];
int ans[MAXN];

void addEdge(int u, int v, int w) {
    nxt[++cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt;
}

//�����ʷ� ͳ��sz dep eor��Ϣ
void dfs1(int u, int d, int x) {
    siz[u] = 1;
    dep[u] = d;
    eor[u] = x;
    for (int e = head[u]; e > 0; e = nxt[e]) {
        dfs1(to[e], d + 1, x ^ (1 << weight[e]));
        //��ʾ��һ���ڵ��ȨֵΪ  x ^ (1 << weight[e]
    }
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        siz[u] += siz[v];
        if (son[u] == 0 || siz[son[u]] < siz[v]) {
            son[u] = v;
        }
    }
}

void effect(int u) {
    maxdep[eor[u]] = max(maxdep[eor[u]], dep[u]);
    for (int e = head[u]; e > 0; e = nxt[e]) {
        effect(to[e]);
    }
}

void cancle(int u) {
    maxdep[eor[u]] = 0;
    for (int e = head[u]; e > 0; e = nxt[e]) {
        cancle(to[e]);
    }
}

//����������ӽڵ�  ͳ�Ƶ�����ϢҪ��u�ڵ�
void answerFromLight(int light, int u) {
    if (maxdep[eor[light]] != 0) {
        ans[u] = max(ans[u], maxdep[eor[light]] + dep[light] - dep[u] * 2);
    }
    for (int i = 0; i < MAXV; i++) {
        if (maxdep[eor[light] ^ (1 << i)] != 0) {
            ans[u] = max(ans[u], maxdep[eor[light] ^ (1 << i)] + dep[light] - dep[u] * 2);
        }
    }
    for (int e = head[light]; e > 0; e = nxt[e]) {
        answerFromLight(to[e], u);
    }
}

void dfs2(int u, int keep) {
    //��ȥ�����
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != son[u]) {
            dfs2(v, 0);
        }
    }
    //��ȥ�ض���
    if (son[u] != 0) {
        dfs2(son[u], 1);
    }
    //�𰸵ĵ�һ���� ���ж��ӽڵ��е����ֵ
    for (int e = head[u]; e > 0; e = nxt[e]) {
        ans[u] = max(ans[u], ans[to[e]]);
    }
    //����Դ�ĵڶ�����  �ýڵ���Լ��ض��ӽڵ�����Ĵ�
    if (maxdep[eor[u]] != 0) {
        //���������� ��ȫ���Լ�һ����
        ans[u] = max(ans[u], maxdep[eor[u]] - dep[u]);
    }
    //�ⲿ�ּ�����Ǻ��Լ���һ����һ����
    for (int i = 0; i < MAXV; i++) {
        if (maxdep[eor[u] ^ (1 << i)] != 0) {
            ans[u] = max(ans[u], maxdep[eor[u] ^ (1 << i)] - dep[u]);
        }
    }
    // ��ǰ������ֵ��������������Ϣ
    maxdep[eor[u]] = max(maxdep[eor[u]], dep[u]);
    // ѡ��������Ĳ����������һ�㣬��ѡ��ǰ�������������������һ�㣬�õ��Ĵ�
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != son[u]) {
            answerFromLight(v, u);
            effect(v);
        }
    }
    if (keep == 0) {
        cancle(u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    int fth;
    int edg;
    char c;
    for (int i = 2; i <= n; i++) {
        cin >> fth;
        cin >> c;
        edg = c - 'a';
        addEdge(fth, i, edg);
    }
    dfs1(1, 1, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";
    return 0;
}
