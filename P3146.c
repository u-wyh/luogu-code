#include <stdio.h>
#include <stdlib.h>

#define N 250

int f[N][N];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, ans = 0;
    scanf("%d", &n);

    // ��ȡ���ݲ���ʼ��
    for (int i = 1; i <= n; i++) {
        scanf("%d", &f[i][i]);
        ans = max(ans, f[i][i]);
    }

    // ��̬�滮��������������
    for (int len = 2; len <= n; len++) {
        for (int l = 1; l <= n - len + 1; l++) {
            int r = l + len - 1;
            for (int k = l; k < r; k++) {
                if (f[l][k] == f[k + 1][r] && f[l][k] != 0) { // ע����f[l][k]�Ƿ�Ϊ0
                    f[l][r] = max(f[l][r], f[l][k] + 1);
                    ans = max(ans, f[l][r]);
                }
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}
