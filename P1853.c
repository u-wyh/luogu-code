#include <stdio.h>
#include <string.h>

int m, n, d;
int w[15], v[15], f[1000005];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d %d", &m, &n, &d);
    int sum = m;
    // ��ʼ���ʲ�
    for (int i = 1; i <= d; i++) {
        scanf("%d %d", &w[i], &v[i]);
    }

    for (int k = 1; k <= n; k++) {
        memset(f, 0, sizeof(f));
        // ��ʼ״̬�����㣩
        for (int i = 1; i <= d; i++) { // �׶�
            for (int j = w[i] / 1000; j <= sum / 1000; j++) { // ����
                f[j] =  max(f[j], f[j - w[i] / 1000] + v[i]) ; // ״̬ת�ƣ�ע�⴦��jΪ0�����
            }
        }
        sum += f[sum / 1000]; // �ۼ�������ʲ�
    }

    printf("%d\n", sum);
    return 0;
}

