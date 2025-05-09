#include<stdio.h>
#include<string.h>
#include<stdlib.h> // ����stdlib.h��ʹ��memset

int n, w;
int a[20];
int f[1 << 18]; // f[i]��ʾ״̬i����С����
int g[1 << 18]; // g[i]��ʾ״̬iʱ�����һ�����ݵ�ʣ�����

int main() {
    scanf("%d%d", &n, &w);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    memset(f, 0x3f, sizeof(f)); // ��ʼ��f����Ϊһ������
    f[0] = 1;
    g[0] = w;

    // ö��״̬
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 1; j <= n; j++) {
            // ö��ÿһͷ��ţ
            if (i & (1 << (j - 1))) continue; // �����ͷ��ţ�Ѿ��ڵ�������
            if (g[i] >= a[j] && f[i | (1 << (j - 1))] >= f[i]) {
                // ����������������
                f[i | (1 << (j - 1))] = f[i];
                // ����ʣ�����
                g[i | (1 << (j - 1))] = (g[i] >= a[j]) ? g[i] - a[j] : 0;
            } else if (g[i] < a[j] && f[i | (1 << (j - 1))] >= f[i] + 1) {
                // ����������������
                f[i | (1 << (j - 1))] = f[i] + 1; // ���ݴ���+1
                g[i | (1 << (j - 1))] = w - a[j]; // ���¿�ʼһ������
            }
        }
    }

    printf("%d\n", f[(1 << n) - 1]);

    return 0;
}
