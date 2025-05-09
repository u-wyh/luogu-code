#include <stdio.h>

#define MOD 10007

long long n, m, s = 1, t;
long long a[10005][105];

int main() {
    scanf("%lld %lld", &n, &m);
    a[0][0] = 1;

    // ��ʼ����������飨Pascal's Triangle Modulo��
    for (int i = 1; i <= 10000; i++) {
        for (int j = 0; j <= 100; j++) {
            if (j == 0) {
                a[i][j] = a[i-1][j]; // ��һ������1
            } else {
                a[i][j] = (a[i-1][j-1] + a[i-1][j]) % MOD;
            }
        }
    }

    // ����������м���
    for (int i = 1; i <= m; i++) {
        scanf("%lld", &t);
        s = (s * a[n][t]) % MOD;
        n -= t; // ���Ѿ��������ˣ�Ҫ����
    }

    printf("%lld\n", s);
    return 0;
}
