#include <stdio.h>
#include <stdlib.h>

#define FOR(i, n, m) for (int i = n; i <= m; i++)

int f[210][210], a[420]; // ����a�Ĵ�С�ӱ��Դ洢���Ƶ�����
int n, ans = 0;

int main() {
    scanf("%d", &n);
    FOR(i, 1, n) scanf("%d", &a[i]);
    FOR(i, n + 1, 2 * n) a[i] = a[i - n]; // ��������a

    // ��ʼ��f���飨��ѡ��������������У�����������ͨ���Ƚ�������f�ģ����Բ���Ҫ��ʽ��ʼ����

    // ��̬�滮���
    FOR(i, 2, n) {
        FOR(j, 1, 2 * n - i) {
            FOR(k, j, j + i - 2) {
                f[j][j + i - 1] = (f[j][k] + f[k + 1][j + i - 1] + a[j] * a[j + i] * a[k + 1] > f[j][j + i - 1]) ?
                                  f[j][k] + f[k + 1][j + i - 1] + a[j] * a[j + i] * a[k + 1] :
                                  f[j][j + i - 1];
            }
        }
    }

    // �������ֵ
    FOR(i, 1, n) {
        if (f[i][n + i - 1] > ans) {
            ans = f[i][n + i - 1];
        }
    }

    printf("%d\n", ans);
    return 0;
}
