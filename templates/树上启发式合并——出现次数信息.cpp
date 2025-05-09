// ��ɫƽ���������C++��
// һ����n���ڵ㣬���1~n������ÿ���ڵ����ɫֵ�͸��׽ڵ���
// ���뱣֤���нڵ�һ�����һ����������1�Žڵ�����ͷ
// ���һ�������У����ڵ�ÿ����ɫ�Ľڵ��������ͬ�������������ɫƽ����
// ��ӡ���������ж��ٸ���������ɫƽ����
// 1 <= n����ɫֵ <= 2 * 10^5
// �������� : https://www.luogu.com.cn/problem/P9233
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200001;

int n;
int color[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt = 0;

int siz[MAXN];
int son[MAXN];

// colorCnt[i] = j����ʾi������ɫ������j��
int colorCnt[MAXN];
// colorNum[i] = j����ʾ���ִ���Ϊi����ɫһ����j��
int colorNum[MAXN];
// ��ɫƽ�������ĸ���
int ans = 0;

void addEdge(int u, int v) {
    nxt[++cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt;
}

void dfs1(int u) {
    siz[u] = 1;
    for (int e = head[u]; e > 0; e = nxt[e]) {
        dfs1(to[e]);
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
    colorCnt[color[u]]++;
    colorNum[colorCnt[color[u]] - 1]--;
    colorNum[colorCnt[color[u]]]++;
    for (int e = head[u]; e > 0; e = nxt[e]) {
        effect(to[e]);
    }
}

void cancle(int u) {
    colorCnt[color[u]]--;
    colorNum[colorCnt[color[u]] + 1]--;
    colorNum[colorCnt[color[u]]]++;
    for (int e = head[u]; e > 0; e = nxt[e]) {
        cancle(to[e]);
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

    //ȥ �ض���
    if (son[u] != 0) {
        dfs2(son[u], 1);
    }

    //����ڵ�Ĺ�����Ϣ
    colorCnt[color[u]]++;
    colorNum[colorCnt[color[u]] - 1]--;
    colorNum[colorCnt[color[u]]]++;

    //�����������Ϣ
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != son[u]) {
            effect(v);
        }
    }

    //�ж��Ըýڵ�Ϊͷ�������ǲ��Ƿ�����ĿҪ��
    //�жϷ�ʽ�� ����ڵ����ɫ�ĳ��ִ��� �� �������ɫ���ֵĴ�����ͬ����ɫ����  �ĳ˻�  ����������Ľڵ�����Ƚ�
    //��Ϊ���������ĿҪ��  ��ô������ɫ�ĳ��ִ�������һ����
    if (colorCnt[color[u]] * colorNum[colorCnt[color[u]]] == siz[u]) {
        ans++;
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
        cin >> color[i] >> father;
        if (i != 1) {
            addEdge(father, i);
        }
    }
    dfs1(1);
    dfs2(1, 0);
    cout << ans << "\n";
    return 0;
}
