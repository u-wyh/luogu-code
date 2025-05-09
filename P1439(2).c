#include <stdio.h>
#include <limits.h> // ����INT_MAX

#define MAX_N 100001

int a[MAX_N], b[MAX_N], map[MAX_N], f[MAX_N];

int main() {
    int n;
    scanf("%d", &n);

    // ��ʼ��map��f����
    for (int i = 0; i < MAX_N; i++) {
        map[i] = 0; // ͨ����ʼ��Ϊ0���ض�ֵ������ʵ������
        f[i] = INT_MAX; // ��ʼ��f����Ϊ�������
    }

    // ��ȡa���鲢���map
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        map[a[i]] = i;
    }

    // ��ȡb����
    for (int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
    }

    int len = 0;
    f[0] = 0; // ��ʼ��f[0]Ϊ0

    for (int i = 1; i <= n; i++) {
        int l = 0, r = len, mid;

        // �����ǰb[i]��ӳ��ֵ����f[len]����ֱ����ӵ�f����ĩβ
        if (map[b[i]] > f[len]) {
            f[++len] = map[b[i]];
        } else {
            // ���ֲ��Һ��ʵĲ���λ��
            while (l < r) {
                mid = (l + r) / 2;
                if (f[mid] > map[b[i]]) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            // ����f[l]Ϊ��Сֵ
            f[l] = (map[b[i]] < f[l]) ? map[b[i]] : f[l];
        }
    }

    printf("%d\n", len);
    return 0;
}
