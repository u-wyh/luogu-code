#include <stdio.h>
#include <limits.h> // ����INT_MAX�����ڳ�ʼ��ans

int a[100001];

int main() {
    int m, n, t, k, ans;
    scanf("%d%d", &m, &n);

    for (int i = 1; i <= m; i++) {
        scanf("%d", &a[i]);
    }

    // ʹ��INT_MAX��ʼ��ans����Ϊ����C������int�����ܱ�ʾ�����ֵ
    ans = INT_MAX;

    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &t, &k);
        ans = INT_MAX; // ÿ�β�ѯǰ����ans

        for (int j = t; j <= k; j++) {
            ans = (ans < a[j]) ? ans : a[j]; // ʹ����Ԫ���������min����
        }

        printf("%d ", ans);
    }

    printf("\n"); // ͨ���������ɺ��һ�����з�
    return 0;
}
