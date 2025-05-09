#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long int p, c; // p������ɿ����۸�c��ʾϲ�����ɿ�������ţ��
} cow;

cow c[100002];

// �ȽϺ���������qsort
int com(const void *a, const void *b) {
    cow *ca = (cow *)a;
    cow *cb = (cow *)b;
    if (ca->p < cb->p) return -1;
    if (ca->p > cb->p) return 1;
    return 0;
}

int main() {
    int n;
    unsigned long long int b, ans = 0; // Ԥ��ʹ�
    scanf("%d %llu", &n, &b); // ��ȡn��b

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &c[i].p, &c[i].c); // ��ȡ�۸��ϲ�����ɿ�������ţ��
    }

    // ʹ��qsort��������
    qsort(c, n, sizeof(cow), com);

    for (int i = 0; i < n; i++) {
        if (b > c[i].c * c[i].p) {
            // ���Ԥ���㹻����ǰ�ɿ���
            ans += c[i].c;
            b -= c[i].c * c[i].p;
        } else {
            // ���Ԥ�㲻�㣬������ع���
            ans += b / c[i].p;
            break; // ����ѭ������Ϊ�����ɿ�������
        }
    }

    printf("%llu\n", ans);
    return 0;
}
