#include <stdio.h>
#include <stdlib.h>

#define LL long long
#define N 10000005

LL f[N];
LL w, c, n, m;

int main() {
    int i;
    scanf("%lld %lld", &m, &n);  // ��ȡm��n

    // ��ʼ��f����Ϊ0����ѡ�����������ȫ���������壬���Զ���ʼ��Ϊ0��
    for (i = 0; i <= m; i++) {
        f[i] = 0;
    }

    while (n--) {
        scanf("%lld %lld", &w, &c);  // ��ȡw��c
        for (i = w; i <= m; i++) {
            f[i] = (f[i] > f[i - w] + c) ? f[i] : f[i - w] + c;
        }
    }

    printf("%lld\n", f[m]);  // ���f[m]

    return 0;
}
