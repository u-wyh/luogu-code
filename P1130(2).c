#include <stdio.h>
#include <limits.h> // ����INT_MAX

#define LL long long

LL n, m;
LL gay[2005][2005];
LL dp[2005][2000];
LL minn = LLONG_MAX; // ʹ��C�����е�LLONG_MAX��ʾ�������

LL min(LL a, LL b) {
    return a < b ? a : b;
}

int main() {
    scanf("%lld %lld", &n, &m);
    for (LL i = 1; i <= m; i++) {
        for (LL j = 1; j <= n; j++) {
            scanf("%lld", &gay[i][j]); // ע��������Ҫ%lld����ȡlong long����
        }
    }

    // ��ʼ��dp���飬ע��������ڵ�0���˵Ĵ�����Ҫ�ر�С��
    for (LL j = 1; j <= n; j++) {
        dp[0][j-1] = LLONG_MAX; // ��ʼ��Ϊ���ֵ����Ϊ��Ҫ������״̬ת�ƶ���
        for (LL i = 1; i <= m; i++) {
            dp[i][j] = LLONG_MAX; // ÿ��dp״̬����ʼ��Ϊ���ֵ
            // ��i��������j�������������ĵ�j-1������ĵ�i-1���˻��ߵ�i����ת�ƹ���
            if (j > 1) {
                dp[i][j] = min(dp[i-1][j-1], dp[i][j-1]) + gay[i][j];
            } else {
                dp[i][j] = gay[i][j]; // ����ǵ�һ������ֱ��ȡ��ǰ����
            }
        }
    }

    // �������п��ܵ����һ�����ҵ���Сֵ
    for (LL i = 1; i <= m; i++) {
        minn = min(minn, dp[i][n]);
    }

    printf("%lld\n", minn);
    return 0;
}

