#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LL unsigned long long

int n, i, j;
int a[101]; // ����
int f[101][101]; // f[i][j]��ʾȡi~j��������player1��ߵ÷�
int s[101]; // s[i]��ʾa[1]~a[i]�ĺ�

int max(int x, int y) {
    return x > y ? x : y;
}

int main() {
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]); // ����
        s[i] = s[i - 1] + a[i]; // ���
        f[i][i] = a[i]; // ��ʼ��
    }

    // ��ʾa[i]~a[j]�ĺ͵ķ�����s[j]-s[i-1]
    for (i = n - 1; i >= 1; i--) {
        for (j = i + 1; j <= n; j++) {
            f[i][j] = max((s[j] - s[i - 1]) - f[i + 1][j],
                          (s[j] - s[i - 1]) - f[i][j - 1]);
        }
    }
    printf("%d %d\n", f[1][n], s[n] - f[1][n]);
    return 0;
}
