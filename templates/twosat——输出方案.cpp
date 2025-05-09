//http://poj.org/problem?id=3683
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstdio>
using namespace std;

const int MAXN = 2005; // ��� 1000 �����񣬲�� 2000 ����
const int MAXM = 4000005; // �ߵ��������

int dfn[MAXN], low[MAXN];
int st[MAXN], top;
int color, Time;
int col[MAXN];
bool instack[MAXN];
int n;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt = 1;

void addedge(int u, int v) {
    Next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

void tarjan(int x) {
    dfn[x] = ++Time;
    low[x] = Time;
    st[++top] = x;
    instack[x] = true;
    for (int i = head[x]; i; i = Next[i]) {
        int v = to[i];
        if (!dfn[v]) {
            tarjan(v);
            low[x] = min(low[x], low[v]);
        } else if (instack[v]) {
            low[x] = min(low[x], dfn[v]);
        }
    }
    if (dfn[x] == low[x]) {
        col[x] = ++color;
        while (st[top] != x) {
            col[st[top]] = color;
            instack[st[top]] = false;
            top--;
        }
        instack[x] = false;
        top--;
    }
}

int main() {
    cin >> n;
    vector<int> s1(n), e1(n), s2(n), e2(n);
    for (int i = 0; i < n; i++) {
        string start, end;
        int d;
        cin >> start >> end >> d;
        // ��ʱ��ת��Ϊ����
        s1[i] = ((start[0] - '0') * 10 + (start[1] - '0')) * 60 + (start[3] - '0') * 10 + (start[4] - '0');
        e1[i] = s1[i] + d;
        s2[i] = ((end[0] - '0') * 10 + (end[1] - '0')) * 60 + (end[3] - '0') * 10 + (end[4] - '0') - d;
        e2[i] = s2[i] + d;
    }
    // ���Լ������
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (max(s1[i], s1[j]) < min(e1[i], e1[j])) {
                //��ʾi��j�ĵ�һ������ͬʱ�μ�
                addedge(2 * i, 2 * j + 1);
                addedge(2 * j, 2 * i + 1);
            }
            if (max(s1[i], s2[j]) < min(e1[i], e2[j])) {
                addedge(2 * i, 2 * j);
                addedge(2 * j + 1, 2 * i + 1);
            }
            if (max(s2[i], s1[j]) < min(e2[i], e1[j])) {
                addedge(2 * i + 1, 2 * j + 1);
                addedge(2 * j, 2 * i);
            }
            if (max(s2[i], s2[j]) < min(e2[i], e2[j])) {
                addedge(2 * i + 1, 2 * j);
                addedge(2 * j + 1, 2 * i);
            }
        }
    }
    // Tarjan �㷨���ǿ��ͨ����
    for (int i = 0; i < 2 * n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }
    // ����Ƿ��г�ͻ
    for (int i = 0; i < n; i++) {
        if (col[2 * i] == col[2 * i + 1]) {
            cout << "NO" << endl;
            return 0;
        }
    }
    // �������
    cout << "YES" << endl;
    for (int i = 0; i < n; i++) {
        if (col[2 * i] < col[2 * i + 1]) {
            // ѡ���һ��ʱ���
            printf("%02d:%02d %02d:%02d\n", s1[i] / 60, s1[i] % 60, e1[i] / 60, e1[i] % 60);
        } else {
            // ѡ��ڶ���ʱ���
            printf("%02d:%02d %02d:%02d\n", s2[i] / 60, s2[i] % 60, e2[i] / 60, e2[i] % 60);
        }
    }
    return 0;
}
