#include <stdio.h>

int n, a[101], mid, all, ans;

int main() {
    scanf("%d", &n);
    all = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        all += a[i];
    }
    all /= n;

    ans = 0;
    for (int i = 1; i < n; i++) { // ע��ѭ����n-1���Ա������a[n+1]
        if (a[i] != all) {
            a[i + 1] += a[i] - all;
            ans++;
        }
    }

    printf("%d", ans);
    return 0;
}
