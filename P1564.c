#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 2510
#define INF 0x3f3f3f3f

int n, m;
int sum[3][MAXN];
int dp[MAXN];
int a[MAXN];

int main() {
    scanf("%d%d", &n, &m);
    memset(dp, INF, sizeof(dp)); // ʹ��memset��ʼ��dp����Ϊ�����
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum[a[i]][i] = sum[a[i]][i - 1] + 1; // �ۼӵ�ǰ���ֳ��ֵĴ���
        sum[!(a[i] - 1) + 1][i] = sum[!(a[i] - 1) + 1][i - 1]; // ����a[i]-1Ϊ0��1����������ۼ�
        if (a[i] == 1) sum[2][i] = sum[2][i - 1] + 1; // ���a[i]��1����Ҳ����sum[2]
    }

    // ע�⣺C����������������0��ʼ�������������Ǳ��ִ�1��ʼ���߼�
    for (int i = 1; i <= n; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if ((abs(sum[2][i] - sum[1][i] - (sum[2][j] - sum[1][j])) <= m) ||
                (sum[2][i] - sum[2][j] == 0) ||
                (sum[1][i] - sum[1][j] == 0)) {
                dp[i] = (dp[i] < dp[j] + 1) ? dp[i] : dp[j] + 1;
            }
        }
    }

    printf("%d\n", dp[n]);
    return 0;
}
