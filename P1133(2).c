#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100010

int dp[MAX_N][3][2], n;
int a[MAX_N][3];
int ans = 0;

// �Զ���max����
int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &a[i][0], &a[i][1], &a[i][2]); // ����ÿ��λ�ø��ָ߶ȵĹ��ͼ�ֵ
    }

    // ��ʼ��dp����
    for (int j = 0; j < 3; j++) { // ������ĸ߶ȣ������֣��������˼�ǵ�һ��λ�����µ�j����
        for (int i = 0; i < 3; i++)
            for (int k = 0; k < 2; k++)
                dp[1][i][k] = 0;
        dp[1][j][0] = dp[1][j][1] = a[1][j]; // ��ʼֵΪa[1][j]

        for (int i = 2; i <= n; i++) { // ѭ��ÿ��λ��������
            dp[i][0][0] = max(dp[i-1][1][1], dp[i-1][2][1]) + a[i][0];
            dp[i][1][0] = dp[i-1][2][1] + a[i][1];
            dp[i][1][1] = dp[i-1][0][0] + a[i][1];
            dp[i][2][1] = max(dp[i-1][1][0], dp[i-1][0][0]) + a[i][2];
        }

        // ����ans
        for (int i = 0; i < j; i++)
            ans = max(ans, dp[n][i][0]); // <=j�ĸ߶ȿ϶��Ǳ������ģ�����Ϊdp[n][i][0]
        for (int i = 2; i > j; i--)
            ans = max(ans, dp[n][i][1]); // >j�Ŀ϶��Ǳ����ߵģ�����Ϊdp[n][i][1]
    }

    printf("%d\n", ans); // ������
    return 0;
}
