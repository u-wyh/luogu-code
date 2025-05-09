#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 10005;
const int MAXM = 20005;

int n, m, st, en;
int father[MAXN];
struct Edge {
    int st, en, val;
} edge[MAXM];

void build() {
    for (int i = 1; i <= n; i++) {
        father[i] = i;
    }
}

int find(int i) {
    if (i != father[i]) {
        father[i] = find(father[i]);
    }
    return father[i];
}

bool unionSets(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy) {
        father[fx] = fy;
        return true;
    } else {
        return false;
    }
}

bool cmp(Edge a, Edge b) {
    return a.val < b.val;
}

int main() {
    cin >> n >> m >> st >> en;
    build();
    for (int i = 1; i <= m; i++) {
        cin >> edge[i].st >> edge[i].en >> edge[i].val;
    }
    sort(edge + 1, edge + m + 1, cmp);
    int ans = 0;
    bool connected = false;
    for (int i = 1; i <= m; i++) {
        if (unionSets(edge[i].st, edge[i].en)) {
            ans = max(ans, edge[i].val);
            if (find(st) == find(en)) {
                connected = true;
                break; // һ��st��en��ͨ���Ϳ���ֹͣ��ӱ���
            }
        }
    }
    if (connected) {
        cout << ans << endl; // �������MST������Ȩֵ
    } else {
        cout << "st and en are not connected" << endl; // ���ߴ���st��en����ͨ�����
    }
    return 0;
}
