#include <stdio.h>
#include <stdlib.h>

int a[100001]; // ע�������С��Ҫ+1����Ϊ������1��ʼ
int n, minn, s = 1e9 + 1, sum;

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    // ʹ��qsort����������Ҫ����stdlib.h�Ͷ���ȽϺ���
    qsort(a + 1, n, sizeof(int), (int (*)(const void*, const void*))compare);


    for (int j = a[1]; j <= a[n]; j++) {
        sum = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] - j > 17) {
                sum += (a[i] - j - 17) * (a[i] - j - 17);
            }
            if (a[i] < j) {
                sum += (j - a[i]) * (j - a[i]); // ע������Ӧ����j-a[i]����Ϊ����Ҫ��ȥ���ǵ���j�Ĳ���
            }
        }
        s = (sum < s) ? sum : s; // ʹ����Ԫ�����������Сֵ����
    }

    printf("%d\n", s);
    return 0;
}
