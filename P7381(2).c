#include <stdio.h>
#include <string.h>
#include <limits.h> // Ϊ��ʹ��INT_MIN

int n, m, k;
int p[505], b[505], dp[505][505];

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p[i]);
    }
    for (int i = 0; i <= m; i++) {
        scanf("%d", &b[i]);
    }

    // ��ʼ��dp���飬����������г�ʼֵΪINT_MIN����ʾδ����
    memset(dp, INT_MIN, sizeof(dp));
    // ��ʼ��dp[0][0]Ϊ0����ʾû��ѡ���κ���Ʒʱ�ļ�ֵΪ0
    dp[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            // ���赱ǰdp[i][j]Ϊ��Сֵ��ͨ���Ƚϸ���Ϊ���ֵ
            dp[i][j] = INT_MIN;
            for (int kk = 0; kk <= j; kk++) {
                // ע�������±��������Ϊp[i]�Ǵ�1��ʼ�ģ���b���±��Ǵ�0��ʼ��
                int index = p[i] + j - kk;
                if (index >= 0 && index <= m) {
                    // ֻ����index��Чʱ�Ž��м���
                    dp[i][j] = (dp[i][j] > dp[i-1][kk] + b[index]) ? dp[i][j] : (dp[i-1][kk] + b[index]);
                }
            }
        }
    }

    // �����������dp[n][k]��Ȼ��INT_MIN�����ʾû�п��еĽ������
    if (dp[n][k] == INT_MIN) {
        printf("No valid solution.\n");
    } else {
        printf("%d\n", dp[n][k]);
    }

    return 0;
}
