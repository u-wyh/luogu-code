#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int a[201], b[201];
    int n, m, s, long1, ans, i;

    scanf("%d %d %d", &n, &m, &s); // ��ȡn, m, s

    for (i = 1; i <= s; i++) {
        scanf("%d", &a[i]); // ��ȡ��ͷλ��
    }

    qsort(a + 1, s, sizeof(int), compare); // ����ͷλ�ý�������

    for (i = 2; i <= s; i++) {
        b[i] = a[i] - a[i - 1] - 1; // ����������ͷ֮��ľ���
    }

    qsort(b + 2, s - 1, sizeof(int), compare); // �Ծ����������

    ans = s; // Ĭ��ÿ����ͷ����Ҫһ��ľ��
    long1 = s; // Ĭ���ܳ���Ϊs������ÿ��ľ�峤��Ϊ1��

    for (i = 2; ans > n; i++) { // ��ľ����������nʱ
        ans--; // ľ��������һ
        long1 += b[i]; // ����ǰ���ļ���ӵ��ܳ�����
    }

    printf("%d\n", long1); // ����ܳ���

    return 0;
}
