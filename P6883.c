#include <stdio.h>
#include <string.h>
#include <limits.h>

#define N 21

int n, m, a[N][N], dp[1 << N];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    for (int i = 1; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) { // �жϵ�jλ�ǲ���1
                for (int k = 0; k < n; k++) {
                    if (!(i & (1 << k))) { // �жϵ�kλ�ǲ���0
                        dp[i] = (dp[i] < dp[i ^ (1 << j)] + a[j][k]) ? dp[i] : dp[i ^ (1 << j)] + a[j][k];
                    }
                }
            }
        }
    }

    int ans = INT_MAX; // ��INT_MAX����ʾ�������
    for (int i = 0; i < (1 << n); i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (!(i & (1 << j))) cnt++; // ͳ���м�λ��0
        }
        if (cnt <= m) ans = (ans < dp[i]) ? ans : dp[i];
    }

    printf("%d\n", ans);
    return 0;
}
