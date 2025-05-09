#include <stdio.h>
#include <limits.h> // ����INT_MAX
#include <string.h> // ����memset�����������������ʵ����Ҫ

int n, m;
int a[2005][2005];
int ans = INT_MAX; // ans����Ҫ���󣬲�Ȼ�Ҳ�����Сֵ

int main() {
    scanf("%d%d", &n, &m);
    // ע�⣺��C�����У���������ͨ����0��ʼ����������ֱ�Ӵ�0��ʼ��ȡ
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // �ӵ�����2����ʼ�����һ���ƽ�
    // ע������ı߽���������Ϊj�Ǵ�n-2��ʼ�ģ�����j+1����Խ��
    for (int j = n - 2; j >= 0; j--) {
        for (int i = 0; i < m; i++) {
            // ȡ��Сֵ������Ϊ֮��Ĳ������Сֵ
            // ע��ʹ��ģ�����������ζ��е����
            a[i][j] = min(a[(i + 1) % m][j + 1], a[i][j + 1]) + a[i][j];
        }
    }

    // �Ҵ�
    for (int i = 0; i < m; i++) {
        ans = min(ans, a[i][0]);
    }

    // �����
    printf("%d\n", ans);

    return 0;
}

// ���min�������壬��ΪC��׼����û��min����
int min(int a, int b) {
    return a < b ? a : b;
}
