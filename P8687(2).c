#include <stdio.h>
#include <string.h>
#include <limits.h>

#define N 20
#define MAX_STATES (1 << N)

int n, m, k;
int dp[MAX_STATES];
int v[N + 1];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    memset(dp, INT_MAX, sizeof(dp));

    for (int i = 1; i <= n; ++i) {
        int h = 0;
        for (int j = 1; j <= k; ++j) {
            int p;
            scanf("%d", &p);
            p--; // ����Ϊ0������
            h |= (1 << p); // ʹ��λ����������ϲ�״̬
        }
        dp[h] = 1; // ��Щ��ζ��������һ���ǽ��
        v[i] = h; // ��¼ÿ���ǵ�״̬
    }

    for (int i = 0; i < (1 << m); ++i) { // ö�����п��ܵ�״̬
        for (int j = 1; j <= n; ++j) {
            if (dp[i] != INT_MAX) { // ֻ���¿ɴ�״̬
                dp[i | v[j]] = min(dp[i | v[j]], dp[i] + 1); // ����״̬ת��
            }
        }
    }

    if (dp[(1 << m) - 1] == INT_MAX) {
        printf("-1\n"); // ���䲻����
    } else {
        printf("%d\n", dp[(1 << m) - 1]); // �������
    }

    return 0;
}
