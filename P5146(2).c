#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // ����INT_MAX��INT_MIN������������������ǲ���Ҫ���ǣ���Ϊ����ֱ��ʹ��long long�ĳ���

int main() {
    int n;
    long long x = -1e10, y = 1e10;
    scanf("%d", &n); // ʹ��scanf����cin

    for (int i = 1; i <= n; i++) {
        long long d;
        scanf("%lld", &d); // ʹ��%lld��ȡlong long���͵���

        // ����x��y��ֵ
        if (d - y > x) {
            x = d - y;
        }
        if (d < y) {
            y = d;
        }
    }

    printf("%lld\n", x); // ʹ��printf����cout������ӻ��з�
    return 0;
}
