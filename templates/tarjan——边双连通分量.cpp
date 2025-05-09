//P8436
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;   // ���ڵ���
const int MAXM = 2e6+5;   // ������������ͼҪ��2��

// ��ʽǰ���Ǵ�ͼ
int head[MAXN];     // head[u]��ʾ�ڵ�u�ĵ�һ���ߵı��
int Next[MAXM<<1];  // Next[i]��ʾ��i���ߵ���һ����
int to[MAXM<<1];    // to[i]��ʾ��i����ָ��Ľڵ�
int cnt = 1;        // �ߵļ���������1��ʼ�����㴦����ߣ�

// Tarjan�㷨��ر���
int dfn[MAXN];      // dfn[u]��ʾ�ڵ�u��DFS��ʱ�����
int low[MAXN];      // low[u]��ʾu����������׷�ݵ����������ȵ�dfn
int st[MAXN], top;  // ջ�����ڴ洢��ǰDFS·���ϵĽڵ�
int color, Time;    // color��¼��˫��������Time��ʱ���������
int col[MAXN];      // ������Ⱦɫ��������δʹ��
int n, m;           // �ڵ����ͱ���
vector<int> ans[MAXN]; // �洢ÿ����˫�Ľڵ�

// ���ٶ��뺯���������ڴ���������
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
        x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}

// ��������
void addedge(int u, int v) {
    Next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

// Tarjan�㷨���˫��ͨ����
void tarjan(int u, int f, int tot) {
    dfn[u] = low[u] = ++Time; // ��ʼ��dfn��low
    st[++top] = u;            // �ڵ�u��ջ

    // ����u�������ڽӱ�
    for(int i = head[u]; i; i = Next[i]) {
        int v = to[i];
        // ����Ǹ����Ҳ��Ƿ���ߣ���������ͼ���رߣ�
        if(v == f && (i - 1) == ((tot - 1) ^ 1)) {
            continue;
        }
        if(!dfn[v]) {         // ���vδ������
            tarjan(v, u, i);  // �ݹ����v
            low[u] = min(low[u], low[v]); // ����low[u]
        } else {              // ���v�ѱ����ʣ�����رߣ�
            low[u] = min(low[u], dfn[v]);
        }
    }

    // ���dfn[u] == low[u]��˵��u�Ǳ�˫�ĸ�
    if(dfn[u] == low[u]) {
        color++;              // �µı�˫���
        ans[color].push_back(u); // ������ڵ�
        // ����ջ�нڵ㣬ֱ��u������������һ����˫��
        while(st[top] != u) {
            ans[color].push_back(st[top--]);
        }
        top--;                // ����u
    }
}

int main() {
    n = read(), m = read();
    // ����߲���ͼ������ͼ��
    for(int i = 1; i <= m; i++) {
        int u = read(), v = read();
        addedge(u, v);
        addedge(v, u); // ����ͼ��˫���
    }

    // ������δ���ʵĽڵ�����Tarjan
    for(int i = 1; i <= n; i++) {
        if(!dfn[i]) {
            tarjan(i, 0, 0); // 0��ʾû�и��ڵ�͸���
        }
    }

    // �����˫������ÿ����˫�Ľڵ�
    cout << color << endl;
    for(int i = 1; i <= color; i++) {
        cout << ans[i].size() << ' ';
        for(int j = 0; j < ans[i].size(); j++) {
            cout << ans[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}