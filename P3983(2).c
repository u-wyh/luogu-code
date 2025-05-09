#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll f[20], n, m, a[20], v[20] = {0, 1, 3, 5, 7, 9, 10, 11, 14, 15, 17}; // v���鴢����ÿ�Ҵ��ķ���
ll dp[100010], ans = 0;

int main() {
    scanf("%lld", &n);
    for (int i = 1; i <= 10; i++) {
        scanf("%lld", &a[i]);
    }

    // ����ÿ�Ҵ������������
    for (int i = 1; i <= 10; i++) {
        for (int j = i; j <= 10; j++) {
            f[j] = (f[j - i] + a[i] > f[j]) ? f[j - i] + a[i] : f[j];
        }
    }

    // �����Ϊ�������
    for (int i = 1; i <= 10; i++) {
        f[i] -= v[i];
    }

    // �����
    for (int i = 1; i <= 10; i++) {
        for (int j = i; j <= n; j++) {
            dp[j] = (dp[j - i] + f[i] > dp[j]) ? dp[j - i] + f[i] : dp[j];
        }
    }

    // �ҳ�dp�����е����ֵ
    for (int i = 1; i <= n; i++) {
        if (dp[i] > ans) {
            ans = dp[i];
        }
    }

    printf("%lld\n", ans);
    return 0;
}
