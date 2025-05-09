#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_N 110
#define MAX_M 60

int f[MAX_N][MAX_M][MAX_M];
int a[MAX_M][MAX_M];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    f[1][1][1] = a[1][1];
    for (int p = 2; p <= n + m - 1; p++) {
        for (int i = 1; i <= n && i <= p; i++) {
            for (int j = 1; j <= n && j <= p; j++) {
                if (i == 1 && j == 1) continue;
                f[p][i][j] = 0; // ��ʼ��f[p][i][j]Ϊ0����Ȼ����������п��ܲ��Ǳ�Ҫ�ģ���Ϊ�������ĸ�ֵ�Ḳ����
                f[p][i][j] = max(max(f[p - 1][i][j], f[p - 1][i - 1][j]), max(f[p - 1][i][j - 1], f[p - 1][i - 1][j - 1]));
                if (i == j) {
                    f[p][i][j] += a[i][p - i + 1];
                } else {
                    f[p][i][j] += a[i][p - i + 1] + a[j][p - j + 1];
                }
            }
        }
    }
    printf("%d\n", f[n + m - 1][n][n]);
    return 0;
}

// ����C��׼����û��max������������Ҫ�Լ�������
int max(int a, int b) {
    return a > b ? a : b;
}
