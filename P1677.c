#include <stdio.h>
#include <stdlib.h>

#define INF 2000000000
#define N 105

int n, ans;
int a[N], to[N], cnt[N];

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    qsort(a+1, n, sizeof(int), compare);

    a[n+1] = INF;
    a[0] = -INF;  // ע�⣺����C���Ե������Ǵ�0��ʼ�ģ�����������΢����

    for (int i = 1; i <= n; i++) {
        if (a[i] - a[i - 1] > a[i + 1] - a[i]) {
            to[i] = i + 1;
            cnt[i + 1]++;
        } else {
            to[i] = i - 1;
            cnt[i - 1]++;
        }
    }

    // ��ʼ��ans
    ans = 0;

    // �ҳ�����ͨ������õ������ţ
    for (int i = 1; i <= n; i++) {
        if (cnt[i] == 0) {
            ans++;
        }
    }

    // �ҳ��໥�������ţ��
    for (int i = 1; i < n; i++) {
        if (cnt[i] == 1 && cnt[i + 1] == 1 && to[i] == i + 1 && to[i + 1] == i) {
            ans++;
        }
    }

    printf("%d\n", ans);
    return 0;
}
