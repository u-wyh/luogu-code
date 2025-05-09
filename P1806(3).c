#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define inf 2e9
#define LL long long
#define mod 1000

LL dp[520][520];
LL ans;

int main() {
    int n;
    scanf("%d", &n);

    // ��ʼ��dp����
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        dp[i][i] = 1;
    }

    // ��̬�滮���
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            for (int k = 1; k < j && j + k <= i; k++) {
                dp[i][j] += dp[i - j][k];
                // ע�⣺C������û���Զ�����ת����ȷ��dp[i][j]���ۼ�ǰ��LL����
                // ������dp�����Ѿ���LL���ͣ�����ʵ���ϲ���Ҫ�������
            }
        }
    }

    // ������
    for (int i = 1; i < n; i++) {
        ans += dp[n][i];
        // ע�⣺�ۼӹ����п��ܳ���int��Χ�����ʹ��LL����
    }

    // ������
    printf("%lld\n", ans);

    return 0;
}
