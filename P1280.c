#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long int ks;
    long int js;
} ren;

int cmp(const void *a, const void *b) {
    ren *renA = (ren *)a;
    ren *renB = (ren *)b;
    return renB->ks - renA->ks; // ע�������ü���ʵ�ֽ�������
}

int main() {
    long int n, k, i, j, num = 1;
    long int sum[10001] = {0};
    long int f[10001] = {0};
    ren z[10001];

    scanf("%ld %ld", &n, &k);
    for (i = 1; i <= k; i++) {
        scanf("%ld %ld", &z[i].ks, &z[i].js);
        sum[z[i].ks]++;
    }

    qsort(z + 1, k, sizeof(ren), cmp); // ʹ��qsort��������

    for (i = n; i >= 1; i--) {
        if (sum[i] == 0) {
            f[i] = f[i + 1] + 1;
        } else {
            for (j = 1; j <= sum[i]; j++) {
                if (f[i + z[num].js] > f[i]) {
                    f[i] = f[i + z[num].js];
                }
                num++; // ��ǰ��ɨ����������
            }
        }
    }

    printf("%ld\n", f[1]);
    return 0;
}
