// ��������ʽ�ϲ�ģ���⣬C++��
// һ����n���ڵ㣬���1~n������n-1���ߣ����нڵ�����һ������1�Žڵ�Ϊ��ͷ
// ÿ���ڵ����һ����ɫֵ��һ����m����ѯ��ÿ����ѯ��������x
// ÿ����ѯ��ӡxΪͷ�������ϣ�һ���ж����ֲ�ͬ����ɫ
// 1 <= n��m����ɫֵ <= 10^5
// �������� : https://www.luogu.com.cn/problem/U41492
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int n, m;
// ÿ���ڵ����ɫ
int arr[MAXN];

// ��ʽǰ����
int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int cnt = 0;

// �����ʷ�
int fa[MAXN];
int siz[MAXN];
int son[MAXN];

// ��������ʽ�ϲ�
// colorCnt[i] = j����ʾi������ɫ������j��
int colorCnt[MAXN];
int ans[MAXN];
int diffColors = 0;

void addEdge(int u, int v) {
    nxt[++cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt;
}

// �����ʷ�
void dfs1(int u, int f) {
    fa[u] = f;
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

// ����uÿ���ڵ㹱����Ϣ
void effect(int u) {
    if (++colorCnt[arr[u]] == 1) {
        diffColors++;
    }
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa[u]) {
            effect(v);
        }
    }
}

// ����uÿ���ڵ�ȡ������
void cancle(int u) {
    colorCnt[arr[u]] = 0; // �����κ���ɫ��ֱ�ӰѸ���ɫ�ļ�������Ϊ0
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa[u]) {
            cancle(v);
        }
    }
}

// ��������ʽ�ϲ��Ĺ���
void dfs2(int u, int keep) {
    // ��������ӵ�������ͳ�������Ĵ𰸣�Ȼ��ȡ������
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa[u] && v != son[u]) {
            dfs2(v, 0);
        }
    }
    // �����ض��ӵ�������ͳ�������Ĵ𰸣�Ȼ��������
    if (son[u] != 0) {
        dfs2(son[u], 1);
    }
    // ��ǰ�ڵ㹱����Ϣ
    if (++colorCnt[arr[u]] == 1) {
        diffColors++;
    }
    // ��������ӵ����������¹���һ��
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != fa[u] && v != son[u]) {
            effect(v);
        }
    }
    // ��¼����u�Ĵ�
    ans[u] = diffColors;
    // ���u���ϼ��ڵ������ӣ�����u�Ĺ���ȡ����������
    if (keep == 0) {
        diffColors = 0;
        cancle(u);
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
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    dfs1(1, 0);//�����ʷ� �ó��ض�����Ϣ����
    dfs2(1, 0);//��ͷ��㿪ʼ����ͳ����Ϣ ����Ҳ����д�� dfs2(1,1)
    cin >> m;
    for (int i = 1, cur; i <= m; i++) {
        cin >> cur;
        cout << ans[cur] << "\n";
    }
    return 0;
}
