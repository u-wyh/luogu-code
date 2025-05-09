#include <stdio.h>
#include <stdlib.h>

int n, ti[5001];
int day[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 31, 30}; // 12���¼���һ�������0��Ϊ����
int a[5], b[5]; // ��������洢���ں�ʱ��
long long t; // ����
int ans; // ��

int is_leap_year(int year) {
    if (year % 100 == 0) {
        return (year % 400 == 0);
    }
    return (year % 4 == 0);
}

int cmp(const void *a,const void *b)
{
    return (*(int *)a-*(int *)b);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) { // ע��C���������0��ʼ
        scanf("%d", &ti[i]);
    }
    qsort(ti, n, sizeof(int), (int (*)(const void *, const void *))cmp); // ��Ҫ����cmp������������

    scanf("%d-%d-%d-%d:%d", &a[0], &a[1], &a[2], &a[3], &a[4]);
    scanf("%d-%d-%d-%d:%d", &b[0], &b[1], &b[2], &b[3], &b[4]);

    for (int i = a[0]; i < b[0]; i++) {
        if (is_leap_year(i)) {
            t -= 366;
        } else {
            t -= 365;
        }
    }

    for (int i = 0; i < a[1] - 1; i++) { // �·ݴ�1��ʼ��������������0��ʼ
        t += day[i];
    }

    for (int i = 0; i < b[1] - 1; i++) {
        t -= day[i];
    }

    if (is_leap_year(a[0]) && a[1] > 2) {
        t++; // ������������·ݴ���2����Ҫ����2�¶������һ��
    }

    if (is_leap_year(b[0]) && b[1] > 2) {
        t--; // ���Ƶأ�����������ҽ����·ݴ���2����Ҫ��ȥ2�¶������һ��
    }

    t += a[2]; // ���Ͽ�ʼ����
    t -= b[2]; // ��ȥ��������

    t *= 1440; // ת��Ϊ����
    t += 60 * a[3] + a[4]; // ���Ͽ�ʼ�ķ��Ӻ���
    t -= 60 * b[3] + b[4]; // ��ȥ�����ķ��Ӻ���

    t = -t; // ��תʱ���

    for (int i = 0; i < n; i++) {
        if (t >= ti[i]) {
            t -= ti[i];
            ans++;
        } else {
            break;
        }
    }

    printf("%d\n", ans); // �����
    return 0;
}
