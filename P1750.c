#include <stdio.h>
#include <stdbool.h>

#define MAXN 10005

long long a[MAXN];
bool used[MAXN];

int main() {
    long long n, c, i, j, minn, mi;
    scanf("%lld%lld", &n, &c);

    for (i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    long long l = 1, r = c,k=n;
    while (k != 0) {
        minn = 9999999999;
        for (i = l; i <= r; i++) {
            if (a[i] < minn && !used[i]) {
                minn = a[i];
                mi = i;
            }
        }

        if (k == 1) {
            printf("%lld\n", minn); // ��ֻʣ���һ����ʱ����
        } else {
            printf("%lld ", minn);
        }

        k--;
        used[mi] = true;

        long long z = 0;
        for (j = mi - 1; j >= 1; j--) {
            if (!used[j]) {
                l = j;
                z = 1;
                break;
            }
        }

        if (r < n) {
            r++; // ���r��û��������ĩβ���������ƶ�
        }

        if (z == 0) {
            l++; // ���û���ҵ�δʹ�õ����Ԫ�أ���l�����ƶ�
        }
    }

    return 0;
}
