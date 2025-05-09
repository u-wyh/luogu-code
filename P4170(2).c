#include <stdio.h>
#include <string.h>
#include <limits.h> // ���ڳ�ʼ��dp����Ϊ���ֵ

int main() {
    int n, i, j, k, l, t;
    char s[60];
    int dp[60][60]; // ע������dp����������Ѿ���int�������ٴ�����

    scanf("%s", s);
    n = strlen(s);
    //printf("%d\n",n);

    // ��ʼ��dp����
    for (i = 0; i < n; ++i) {
        for (j = 0; j <= i; ++j) { // ע������j��������i����Ϊdp[i][j]ֻ����j<=iʱ��������
            dp[i][j] = (j == i) ? 1 : INT_MAX; // ���i==j���򳤶�Ϊ1���Ӵ����Էָ��1������
        }
    }

    // ��̬�滮����
    for (l = 1; l < n; ++l) {
        for (i = 0; i + l < n; ++i) {
            int r = i + l; // �ұ߽�
            if (s[i] == s[r]) {
                dp[i][r] = dp[i][r - 1]; // �����β�ַ���ȣ���ǰ�Ӵ��ķָ�����ǰһ���Ӵ���ͬ
            } else {
                dp[i][r] = dp[i][i] + dp[i + 1][r]; // ��ʼ��Ϊ���ָ�����
                for (k = i + 1; k < r; ++k) {
                    dp[i][r] = (dp[i][r] < dp[i][k] + dp[k + 1][r]) ? dp[i][r] : dp[i][k] + dp[k + 1][r];
                }
            }
        }
    }

    printf("%d\n", dp[0][n - 1]); // ������
    return 0;
}
