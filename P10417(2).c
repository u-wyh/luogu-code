#include <stdio.h>
#include <stdlib.h>

int n, m;
long long K, l, r = 2e9, mid, A[100005], B[100005];

int cmp(const void *a,const void *b){
    return (*(long long  *)a - *(long long *)b);
}
// �ж�С�ڵ��ڵ�ǰ mid �� C[i] = A[i] + B[j] �ĸ����Ƿ�С�� K
int check() {
    long long cnt = 0;
    for (int i = 1; i <= n; ++i) {
        int j;
        for (j = 1; j <= m; ++j) {
            if (B[j] > mid - A[i]) break; // �ҵ���һ������ mid - A[i] �� B[j]
        }
        cnt += j - 1; // �ۼ�С�ڵ��� mid - A[i] �� B[j] ����
    }
    return cnt < K;
}

int main() {
    scanf("%d%d%lld", &n, &m, &K);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &A[i]);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%lld", &B[i]);
    }
    qsort(B + 1, m, sizeof(long long), cmp);
    while (l < r) {
        mid = l + (r - l) / 2; // ��ֹ���
        if (check()) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    printf("%lld", l);
    return 0;
}
