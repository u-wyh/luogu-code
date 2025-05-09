// �����ʷ��Ż���̬�滮ģ���⣬C++��
// һ����n���ڵ㣬����n-1���ߣ����нڵ�����һ�������涨1�Žڵ���ͷ
// �涨�κε㵽�Լ��ľ���Ϊ0
// ����d(u, x)����uΪͷ�������У���u�ľ���Ϊx�Ľڵ���
// ����ÿ����u����֪���ĸ�����С��x����ȡ������d(u, x)ֵ
// ��ӡÿ����Ĵ�x
// 1 <= n <= 10^6
// �������� : https://www.luogu.com.cn/problem/CF1009F
// �������� : https://codeforces.com/problemset/problem/1009/F
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
//�Ż���̬�滮�ķ�ʽ�ǽڵ�̳��Լ������ӵ���Ϣ
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000001;

int n;

int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int cntg = 0;

int len[MAXN];
int son[MAXN];
int dfn[MAXN];
int cntd = 0;

// ��̬�滮
int dp[MAXN];
// ������
int ansx[MAXN];

void setdp(int u, int i, int v) {
    dp[dfn[u] + i] = v;
}

int getdp(int u, int i) {
    return dp[dfn[u] + i];
}

void addEdge(int u, int v) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

void dfs1(int u, int fa) {
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa) {
            dfs1(v, u);
        }
    }
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa) {
            if (son[u] == 0 || len[son[u]] < len[v]) {
                son[u] = v;
            }
        }
    }
    len[u] = len[son[u]] + 1;
}

//����ȥ�Լ����ض���  ��Ϊ�Լ����ض���ռ�ݵ�λ�����Լ��ķ�Χ
//Ȼ��ȥ�Լ��������  �����ռ�ݵĺ��Լ���Ҫռ�ݵ�λ����ȫ��ͬ
//Ȼ��ʼ���Լ���λ��  ÿ��λ�ôӾ����Լ�0��ʼ  �����ض��ӻ�û�б����õ�Ҳ���ᱻ����
//����ӵ�û��Ӱ��  ������ȷ
void dfs2(int u, int fa) {
    dfn[u] = ++cntd;
    setdp(u, 0, 1);
    ansx[u] = 0;
    if (son[u] == 0) {
        return;
    }
    dfs2(son[u], u);
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa && v != son[u]) {
            dfs2(v, u);
        }
    }
    // ע��һ��Ҫ�ںϲ���������dp��Ϣ�Ĺ����У�ȥ����ansx
    // ǧ��Ҫ������ٱ���һ��u��dp��Ϣ��Ȼ�����ansx
    // ��Ϊ�κ�forѭ�����������ǳ����Ĺ�ģ��
    // ���forѭ���ǳ����Ĺ�ģ����ôu������ȥ��u���ض����ֱ�����ȥ��������ÿ���ڵ㶼������ȥ
    // ʱ�临�Ӷȱ�Ȼ������O(n)������O(n^2)�������ʷֵ����ƾͲ������ˣ�
    // ���Գ�����Ϣ�ᱻuֱ�Ӽ̳У����Բ�Ҫ���κ��볤���ĳ��ȵȹ�ģ��ѭ�����֣�
    ansx[u] = ansx[son[u]] + 1;
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa && v != son[u]) {
            for (int i = 1; i <= len[v]; i++) {
                setdp(u, i, getdp(u, i) + getdp(v, i - 1));
                if (getdp(u, i) > getdp(u, ansx[u]) || (getdp(u, i) == getdp(u, ansx[u]) && i < ansx[u])) {
                    ansx[u] = i;
                    //�ڹ����и��´�
                }
            }
        }
    }
    // ���u��ĳ�����룬��õ����ڵ���Ϊ1
    // ��ôu�𰸾���0���룬��Ϊu��u�Լ��ľ�����0��Ҳ��1���ڵ���
    // ������ĿҪ�󣬷��ؾ���С�ľ���
    if (getdp(u, ansx[u]) == 1) {
        ansx[u] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; i++) {
        cout << ansx[i] << "\n";
    }
    return 0;
}