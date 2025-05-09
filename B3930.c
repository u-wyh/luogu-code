#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Ϊ��ʹ��INT_MAX

#define MAX_N 1000010

long long a[MAX_N];

// ����qsort�ıȽϺ���
int compare(const void *a, const void *b) {
    long long arg1 = *((long long*)a);
    long long arg2 = *((long long*)b);
    if (arg1 > arg2) return -1;
    if (arg1 < arg2) return 1;
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);

    // ��ȡ����
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    // ʹ��qsort����
    qsort(a + 1, n, sizeof(long long), compare);

    // ����n�Ĵ�С
    n = (n > 32) ? 32 : n;

    long long mx = 0;

    // �������ֵ
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            mx = (mx > (a[i] & a[j])) ? mx : (a[i] & a[j]);
        }
    }

    printf("%lld\n", mx);

    return 0;
}
