#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

const int N = 200005;

set<int> q1, q2;
int a[N], vis[N], n, f[N], g[N];

inline int read() {
    char c = getchar();
    int tot = 1;
    while (c < '0' || c > '9') {
        if (c == '-') tot = -1;
        c = getchar();
    }
    int sum = 0;
    while (c >= '0' && c <= '9') {
        sum = sum * 10 + (c - '0');
        c = getchar();
    }
    return sum * tot;
}

int main() {
    n = read();
    for (int i = 1; i <= n; i++) {
        a[i] = read();
        vis[a[i]] = 1;
    }

    for (int i = 1; i <= 2 * n; i++) {
        if (!vis[i]) {
            q1.insert(i);
            q2.insert(-i);
        }
    }

    for (int i = 1; i <= n; i++) {
        auto it = q1.lower_bound(a[i]);
        if (it != q1.end()) {
            q1.erase(it);
            f[i] = f[i - 1] + 1;
        } else {
            f[i] = f[i - 1];
        }
    }

    for (int i = n; i >= 1; i--) {
        auto it = q2.lower_bound(-a[i]);
        if (it != q2.end()) {
            q2.erase(it);
            g[i] = g[i + 1] + 1;
        } else {
            g[i] = g[i + 1];
        }
    }

    int ans = g[1];
    for (int i = 1; i <= n; i++) {
        ans = max(ans, f[i] + g[i + 1]);
    }

    printf("%d\n", ans);
    return 0;
}
