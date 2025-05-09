#include <stdio.h>
#include <stdlib.h>

#define MAXN 100001

int n, ma, d[MAXN], a[MAXN], k, x[MAXN], xl = 1, t, len = 1;

// ģ����ֲ��ң��ҵ���һ������key��Ԫ�ص�������upper_bound��
int upper_bound(int *arr, int r, int key) {
    int left = 1, right = r;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return left;
}

// ģ����ֲ��ң��ҵ���һ����С��key��Ԫ�ص�������lower_bound��
int lower_bound(int *arr, int r, int key) {
    int left = 1, right = r;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return left + 1; // ע������Ҫ��1����Ϊlower_boundҪ�󷵻ص�һ����С��key��Ԫ�ص�����
}

int main() {
    x[1] = INT_MAX; // ʹ��INT_MAX����0x7fffffff
    while (scanf("%d", &a[++n]) != EOF);
    --n; // ����n��ֵ����Ϊ���һ��ѭ���������1

    d[1] = a[1];
    for (int i = 2; i <= n; i++) {
        if (a[i] <= d[len]) {
            d[++len] = a[i];
        } else {
            int pos = upper_bound(d, len, a[i]);
            if (pos <= len) { // ȷ����Խ��
                d[pos] = a[i];
            }
        }
    }
    printf("%d\n", len - 1); // �������������еĳ���

    for (int i = 1; i <= n; i++) {
        if (x[xl] < a[i]) {
            xl++;
            x[xl] = a[i];
        } else {
            int k = lower_bound(x, xl, a[i]);
            if (k <= xl) { // ȷ����Խ��
                x[k] = a[i];
            }
        }
    }
    printf("%d\n", xl); // �����ݼ������еĳ��ȣ�������ʵֻ�����˲�ͬԪ�ص����������Ҫ���ϸ�ݼ���Ԫ�ز�ͬ������ȷ��������ܲ�׼ȷ��

    return 0;
}

// ע�⣺���������е�lower_bound���ڵݼ�������ʱ���ܲ�����ȫ׼ȷ�ģ�
// ��Ϊ��ֻ���滻�˵�һ����С��a[i]��Ԫ�أ���û�б�֤�����е��ϸ�ݼ��ԡ�
// ���Ҫ�����ϸ�ݼ���Ԫ�ز��ظ��������г��ȣ�������Ҫ�����߼���
