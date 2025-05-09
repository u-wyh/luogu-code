#include <stdio.h>
#include <stdlib.h>

double b[200001], a[200001];
long long n;
double l, v, q, t;

// �Զ���ȽϺ���������qsort
int cmp(const void *x, const void *y) {
    double dx = *(double *)x;
    double dy = *(double *)y;
    return (dx > dy) - (dx < dy); // �򻯱Ƚ�
}

int main() {
    // freopen("endless.in", "r", stdin);
    // freopen("endless.out", "w", stdout);

    scanf("%lld %lf %lf", &n, &l, &v);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &a[i]);
    }

    // ʹ��qsort�Ӵ�С����
    qsort(a, n, sizeof(double), cmp);

    b[0] = l / v; // ��ʹ��ħ����ʱ��
    for (int i = 1; i < n; i++) {
        b[i] = a[i] / v + b[i - 1]; // ʹ��ǰi��ħ����ʱ��
    }

    scanf("%lf", &q);
    while (q--) {
        scanf("%lf", &t);
        if (b[n - 1] <= t) {
            printf("-1\n");
            continue;
        }

        int l = 0, r = n - 1, ans = 0;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (b[mid] > t) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}
