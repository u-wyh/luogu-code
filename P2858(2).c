#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2010

int max(int a, int b) {
    return (a > b) ? a : b;
}

int n, f[MAX_N][MAX_N], v[MAX_N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
    }

    // ��ʼ����̬�滮���飬����ȫ����Ϊ0��������������У�������������ȡ���ֵ�����Գ�ʼֵ��Ӱ����

    for (int i = 1; i <= n; i++) {
        for (int j = n; j >= i; j--) {
            int a = n - (j - i + 1); // ����ʣ������
            f[i][j] = max(f[i - 1][j] + v[i - 1] * a, f[i][j + 1] + v[j + 1] * a); // ת�Ʒ���
        }
    }

    int maxn = 0;
    for (int i = 1; i <= n; i++) {
        maxn = max(maxn, f[i][i] + v[i] * n); // �������һ�������ļ۸�
    }

    printf("%d\n", maxn);

    return 0;
}
