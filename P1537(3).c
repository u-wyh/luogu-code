#include <stdio.h>
#include <string.h>

#define MAX_VALUE 6  // ������ֵ
#define MAX_SUM (2 * 10000 * 6)  // ��������ܺͲ����� 2 * 10^4 * 6

int dp[MAX_SUM + 1];  // ��̬�滮���飬���ڼ�¼�Ƿ�������ĳ����
int a[MAX_VALUE + 1];  // �洢ÿ�ּ�ֵ���������

int main() {
    int Case = 0;
    while (1) {
        Case++;
        int sum = 0;
        for (int i = 1; i <= 6; i++) {
            scanf("%d", &a[i]);
            sum += i * a[i];
        }
        if (sum == 0) break;  // ��������

        printf("Collection #%d:\n", Case);
        if (sum % 2 != 0) {
            printf("Can't be divided.\n\n");
            continue;
        }

        memset(dp, 0, sizeof(dp));  // ��ʼ��dp����
        dp[0] = 1;  // ��ʼ״̬����Ϊ0ʱ���ǿ�����ɵ�

        for (int i = 1; i <= 6; i++) {
            for (int j = sum / 2; j >= i; j--) {
                for (int k = 1; k <= a[i] && j >= k * i; k++) {
                    dp[j] |= dp[j - k * i];
                }
            }
        }

        if (dp[sum / 2]) {
            printf("Can be divided.\n\n");
        } else {
            printf("Can't be divided.\n\n");
        }
    }

    return 0;
}
