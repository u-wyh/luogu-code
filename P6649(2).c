#include <stdio.h>
#include <limits.h> // ���ڶ���INT_MAX

#define MIN(a, b) ((a) < (b) ? (a) : (b))

long long dp[2000][2000];
long long a[2000][2000];

// ���ٶ��뺯��
int read() {
    int x = 0;
    int f = 0; // ʹ��int����ʾ������־
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        f |= (ch == '-');
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    if (f) return -x;
    else return x;
}

int main() {
    int n, m;
    n = read();
    m = read();

    // ��ʼ��dp����Ϊһ��������ע�⣺����ʹ��LONG_LONG_MAX����������Ŀ������Ҫ���������
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m + 1; j++) {
            dp[i][j] = LLONG_MAX;
        }
    }

    // ��ȡ����a
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            a[i][j] = read();
            if (j > 1 && a[i][j - 1] < 0) {
                a[i][j] += a[i][j - 1];
            }
        }
        dp[i][m + 1] = LLONG_MAX; // �߽�����
    }

    // ��̬�滮���
    for (int i = n; i >= 1; i--) {
        for (int j = m; j >= 1; j--) {
            if (a[i][j] <= 0) {
                dp[i][j] = MIN(dp[i][j + 1], dp[i + 1][j] + a[i][j]);
            } else {
                dp[i][j] = MIN(dp[i][j + 1], dp[i + 1][j]) + a[i][j];
            }
        }
    }

    // �ҳ���һ�е���Сֵ��Ϊ��
    long long ans = LLONG_MAX;
    for (int j = 1; j <= m; j++) {
        ans = MIN(ans, dp[1][j]);
    }

    printf("%lld\n", ans);
    return 0;
}
