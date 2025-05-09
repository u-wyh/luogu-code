#include <stdio.h>
#include <stdlib.h>

int n, a, ans, i[100005], z[100005];

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d %d", &n, &a);
    for (int k = 1; k <= n; k++) {
        scanf("%d", &i[k]);
    }
    i[0] = i[n];
    i[n + 1] = i[1];

    // ����ÿ��λ�õķ�1�ھ�����
    for (int k = 1; k <= n; k++) {
        z[k] = 0; // ��ʼ��������
        for (int j = k - 1; j <= k + 1; j++) {
            // ע��������������Խ�磬������ͨ��i[0]��i[n+1]�����ñ�����
            if (i[j] != 1) {
                z[k]++;
            }
        }
    }

    // ��z�����������
    qsort(z + 1, n, sizeof(int), cmp);

    // �ۼ�ǰa�����ķ�1�ھ�����
    for (int k = 1; k <= a; k++) {
        ans += z[k];
    }

    printf("%d\n", 3 * n - ans);

    return 0;
}
