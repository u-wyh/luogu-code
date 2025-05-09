#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int n, k, m;
int Min = INT_MAX;
int f[501][501];

int min(int a,int b)
{
    return a<b?a:b;
}

typedef struct {
    int h, w;
} info;

info a[1001];

int cmp(const void *x, const void *y) {
    info *xx = (info *)x;
    info *yy = (info *)y;
    return xx->h - yy->h;
}

int main() {
    scanf("%d %d", &n, &k);
    m = n - k; // ѡȡm����
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &a[i].h, &a[i].w);
    }

    qsort(a + 1, n, sizeof(info), cmp); // �߶Ⱦ���˳��

    memset(f, 0x7f, sizeof(f)); // ��ʼ��Ϊ����ֵ

    for (int i = 1; i <= n; i++) {
        f[i][1] = 0; // ����ѡ���κ��鶼�����л���
    }

    for (int i = 2; i <= n; i++) { // ���ŷŵ�i����ʱ��
        for (int j = 1; j < i; j++) { // ������ǰ���j������
            for (int l = 2; l <= min(i, m); l++) { // ���µ�i��ʱ�����Ȳ�����i��m
                f[i][l] = min(f[i][l], f[j][l - 1] + abs(a[i].w - a[j].w)); // �ܻ���ԽСԽ��
            }
        }
    }

    for (int i = m; i <= n; i++) {
        Min = min(Min, f[i][m]); // �ҵ���m��β����С����
    }

    printf("%d\n", Min);
    return 0;
}
