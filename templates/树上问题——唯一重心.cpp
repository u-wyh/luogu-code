// ɾ����ʹ������Ψһ
// һ����n���ڵ㣬���1~n����n-1�����γ�һ����
// ����ϣ��������Ψһ�Ľڵ㣬�����ķ�ʽ����ɾ��һ���ߡ�Ȼ������һ����
// �������ֻ��һ�����ģ���Ҫɾ���������ĵ�����һ���ߣ��ٰ������߼���(�����޷�ͨ���Ѿ�ʵ��)
// ����������������ģ������ķ�ʽ����ɾ��һ���ߡ�Ȼ������һ���ߣ�ʹ������Ψһ��
// ��������ж��֣���ӡ����һ�ּ���
// ������ɾ���ڵ�3�ͽڵ�4֮��ıߣ������ӽڵ�4�ͽڵ�7֮��ıߣ���ô��ӡ:
// "3 4"
// "4 7"
// �������� : https://www.luogu.com.cn/problem/CF1406C
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ����������
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 100001;

int n;
int head[MAXN];
int Next[MAXN << 1];
int to[MAXN << 1];
int cnt;

// size[i] : ��1�Žڵ㿪ʼdfs�Ĺ����У���iΪͷ�������Ľڵ���
int sz[MAXN];

// maxsub[i] : ����ڵ�i���������ĸ�����������Ĵ�С
int maxsub[MAXN];

// �ռ����е�����
vector<int> centers;

// �κ�һ��Ҷ�ڵ�
int anyLeaf;

// ��Ҷ�ڵ�ĸ��׽ڵ�
int anyLeafFather;

void build() {
    cnt = 1;
    fill(head + 1, head + n + 1, 0);
}

void addEdge(int u, int v) {
    Next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

void dfs(int u, int f) {
    sz[u] = 1;
    maxsub[u] = 0;
    for (int e = head[u]; e != 0; e = Next[e]) {
        int v = to[e];
        if (v != f) {
            dfs(v, u);
            sz[u] += sz[v];
            maxsub[u] = max(maxsub[u], sz[v]);
        }
    }
    maxsub[u] = max(maxsub[u], n - sz[u]);
}

// ������һ��Ҷ�ڵ�͸�Ҷ�ڵ�ĸ��׽ڵ�
void find(int u, int f) {
    for (int e = head[u]; e != 0; e = Next[e]) {
        int v = to[e];
        if (v != f) {
            find(v, u);
            return;
        }
    }
    anyLeaf = u;
    anyLeafFather = f;
}

int compute() {
    dfs(1, 0);
    centers.clear();
    for (int i = 1; i <= n; i++) {
        if (maxsub[i] <= n / 2) {
            centers.push_back(i);
        }
    }
    if (centers.size() == 2) {
        find(centers[1], centers[0]);
        //�������������  ��ô���Ǳ�Ȼ����  ʹ֮Ϊ���ӹ�ϵ
        //�ҵ�һ��centers[1]��Ҷ�ӽڵ� ������ڵ�ҵ�centers[0]�ϼ���
    }
    return centers.size();
}

int main() {
    int testCase;
    scanf("%d", &testCase);
    for (int t = 1; t <= testCase; t++) {
        scanf("%d", &n);
        build();
        for (int i = 1, u, v; i < n; i++) {
            scanf("%d%d", &u, &v);
            addEdge(u, v);
            addEdge(v, u);
        }
        int centroidCount = compute();
        if (centroidCount == 1) {
            int centroid = centers[0];
            int neighbor = to[head[centroid]]; // ��������ȡ��һ���ڽӵ���Ϊ�����ע������ж����
            printf("%d %d\n", centroid, neighbor);
            printf("%d %d\n", centroid, neighbor); // ������ĿҪ�󣬿�����Ҫ�����ͬ�ı�
            // ע�⣺�������ֻ��Ҫ�������һ�������������ıߣ�ʵ�����������Ҫ������ĿҪ�����
        } else {
            printf("%d %d\n", anyLeafFather, anyLeaf);
            printf("%d %d\n", centers[0], anyLeaf);
        }
    }
    return 0;
}
