#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int n, k;
double a[10005];
double l, r, mid;
char s[100];

int check(double x) {
    int tot = 0;
    for (int i = 0; i < n; i++) { // ע������������0��ʼ
        tot += floor(a[i] / x);
    }
    return tot >= k;
}

int main() {
    scanf("%d%d", &n, &k);
    r = 0.0; // ��ʼ��rΪ0.0
    for (int i = 0; i < n; i++) { // ע������������0��ʼ
        scanf("%lf", &a[i]);
        r += a[i]; // �ۼ�����a[i]��ֵ��r
    }
    l = 0.0; // ��ʼ��lΪ0.0����Ϊ����Ҫ�ҵ���������
    while (r - l > 1e-4) {
        mid = (l + r) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    // ʹ��snprintf����ʽ���ַ���������ֱ��ʹ��strlen���ַ�������
    snprintf(s, sizeof(s), "%.3f", l);
    printf("%s\n", s); // ������
    return 0;
}
