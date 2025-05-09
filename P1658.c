#include <stdio.h>
#include <stdlib.h>

int n, x;
int a[2000];
int ans;

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d %d",&x,&n);
    for (int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
    }

    // ע�⣬C���Ա�׼����û��ֱ�ӵ�sort����������ʹ��qsort����
    qsort(a + 1, n, sizeof(int), compare);

    if (a[1] != 1) {
        printf("-1\n");
        return 0;
    }

    int sum = 0;
    while (sum < x) {
        int i;
        for (i = n; i >= 1; i--) {
            if (a[i] <= sum + 1)
                break;
        }
        ans++;
        sum += a[i];
    }

    printf("%d\n", ans);
    return 0;
}

