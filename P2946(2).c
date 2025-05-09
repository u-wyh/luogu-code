#include <stdio.h>
#include <stdlib.h>

#define p 100000000 // ���峣��
#define N 2010
#define F 1010

int n, f;
int r[N];
long long h[N][F];

int main() {
    int i, j;
    scanf("%d %d", &n, &f);
    for (i = 1; i <= n; i++) {
        scanf("%d", &r[i]);
        r[i] %= f; // ��ǰȡģ
    }

    // ��ʼ��
    for (i = 1; i <= n; i++) {
        h[i][r[i]] = 1;
    }

    // ��̬�滮����
    for (i = 1; i <= n; i++) {
        for (j = 0; j < f; j++) {
            h[i][j] = (h[i][j] + h[i-1][j]) % p;
            h[i][j] = (h[i][j] + h[i-1][(j - r[i] + f) % f]) % p; // ÿ��һ�ξ�%p
        }
    }
    printf("%lld\n", h[n][0]);
    return 0;
}
