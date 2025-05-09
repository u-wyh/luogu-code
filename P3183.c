#include <stdio.h>

struct node {
    int u, w, next;
};

struct node e[200010];
int st[100010], out[100010], ind[100010], f[100010], n, m, a, b, ans, tot, s, end;

void add(int x, int y) {
    e[++tot].u = x;
    e[tot].w = y;
    e[tot].next = st[x];
    st[x] = tot;
}

int dfs(int x) {
    if (f[x]) return f[x];  // ���仯
    int ans = 0;
    if (out[x] == 0) return 1;
    for (int i = st[x]; i; i = e[i].next) {
        ans += dfs(e[i].w);
    }
    f[x] = ans;  // ���仯
    return ans;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &a, &b);
        add(a, b);
        out[a]++;
        ind[b]++;
    }
    for (int i = 1; i <= n; i++) {
        if (ind[i] == 0 && out[i] != 0) {  // ע�ⵥ��������
            ans += dfs(i);
        }
    }
    printf("%d", ans);
    return 0;
}
