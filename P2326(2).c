#include<stdio.h>

#define MAX_N 100010

int t, n;
int a[MAX_N], b[MAX_N];

int work() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int k = 20; k >= 0; k--) { // �����20λ
        int top = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] & (1 << k)) {
                b[++top] = a[i]; // �ж�a[i]�ĵ�kλ�Ƿ�Ϊ1
            }
        }
        if (top > 1) {
            n = top;
            for (int i = 1; i <= top; i++) {
                a[i] = b[i];
            }
        }
    }
    return (a[1] & a[2]); // �����������ʣ��������
}

int main() {
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        printf("Case #%d: %d\n", i, work());
    }
    return 0;
}
