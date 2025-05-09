#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 501

typedef long long ll;

ll n, k, a[MAX_N], ans = 0, sum = 0;

int compare(const void *a, const void *b) {
    ll val1 = abs(ans + *(ll *)a);
    ll val2 = abs(ans + *(ll *)b);
    if (val1 < val2) return -1;
    if (val1 > val2) return 1;
    return 0;
}

int main() {
    scanf("%lld %lld", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    for (int i = 0; i < n; i++) {
        ll temp_ans = ans;
        // �ȸ���ans��ֵ����Ϊqsort�����޸����ֵ
        qsort(a + i, n - i, sizeof(ll), compare);
        // ע�⣬����ֻ����ʣ������鲿��

        ans += a[i];
        sum++;

        // ע�⣬pow������C�����з���double����Ҫ����ת��
        if (ans < -(1LL << (k - 1)) || ans >= (1LL << (k - 1))) {
            printf("%lld\n", sum - 1);
            return 0;
        }
    }

    printf("%lld\n", n);
    return 0;
}
