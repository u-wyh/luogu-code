#include <stdio.h>
#include <stdlib.h>

#define MAX_N 101
#define MAX_F 20001 // ���� f ������Ҫ���㵽 N+max{ai}������ٶ����ֵ�㹻��

int a[MAX_N], b[MAX_F], f[MAX_F];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }

    // ��ʼ�� f ����Ϊ�������
    for (int i = 0; i < MAX_F; i++) {
        f[i] = -1e9;
    }

    f[0] = 0; // f[0] ��ʼ��Ϊ 0

    // ��̬�滮���
    for (int j = 0; j < 2 * n; j++) { // ���ǵ�������Ҫ���㵽 2N
        for (int i = 0; i < m; i++) {
            if (j >= a[i]) {
                // ע�⣺���� b[j-a[i]] ����Խ�磬��Ϊ b ����ֻ�� n ��Ԫ��
                // ������Ŀ��֤ a[i] ����ʹ j-a[i] Խ��
                f[j] = (f[j] > f[j - a[i]] + (j - a[i] < n ? b[j - a[i]] : 0)) ? f[j] : f[j - a[i]] + (j - a[i] < n ? b[j - a[i]] : 0);
            }
        }
    }

    int ans = -1e9; // ��ʼ���𰸱���Ϊ�������
    for (int i = n; i < 2 * n; i++) {
        if (f[i] > ans) {
            ans = f[i];
        }
    }

    printf("%d\n", ans);

    return 0;
}
