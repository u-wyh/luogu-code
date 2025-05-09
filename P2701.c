#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h> // Ϊ��ʹ��INT_MAX

#define MAXN 1005

int n, m;
int a[MAXN][MAXN], f[MAXN][MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d%d", &n, &m);
    memset(a, 1, sizeof(a));
    int x, y;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        a[x][y] = 0;
    } // ����

    // ��ʼ��f����Ϊ0����Ϊ��̬�滮�����У����û��������Ӧ�Ӹ�λ�ÿ�ʼ������������α߳�
    memset(f, 0, sizeof(f));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j]) { // �������
                // ע�⣬���i��jΪ1���������Ϸ�����û��ֵ����Ҫ��������
                int left = (j > 1) ? f[i][j - 1] : 0;
                int up = (i > 1) ? f[i - 1][j] : 0;
                int diag = (i > 1 && j > 1) ? f[i - 1][j - 1] : 0;
                f[i][j] = 1 + min(min(left, up), diag); // ��̬ת�Ʒ���
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            ans = max(ans, f[i][j]); // ans��¼���ֵ
        }
    }
    printf("%d\n", ans);
    return 0;
}
