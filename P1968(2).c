#include <stdio.h>

// �Զ���max��������ΪC��׼����û��
int max(int a, int b) {
    return a > b ? a : b;
}

// ������Ҫ�Ƚ�double���ͣ���ʵ��һ��double�汾��max
double max_double(double a, double b) {
    return a > b ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);
    int a[100000];
    double f[10000][2]; // ��̬�滮���飬�洢ÿ�����ʱ�������Ԫ����˼�ֵ

    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    f[1][0] = 100; // ��һ�쿪ʼʱ��100��Ԫ
    f[1][1] = a[1]; // ��һ�쿪ʼʱ����ȫ���������

    for (int i = 2; i <= n; i++) {
        // �����i�����ʱ������Ԫ������ֵ
        f[i][0] = max_double(f[i-1][0], (f[i-1][1] / (double)a[i]) * 100);
        // �����i�����ʱ������˵�����ֵ������Ԫ��ʾ��
        f[i][1] = max_double(f[i-1][1], f[i-1][0] * a[i] / 100.0);
    }

    // ������һ�����ʱ�ܻ�õ������Ԫ��ֵ
    printf("%.2f\n", max_double(f[n][0], (f[n][1] / (double)a[n]) * 100));

    return 0;
}
