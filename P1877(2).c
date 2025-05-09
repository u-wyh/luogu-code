#include <stdio.h>
#include <stdbool.h> // ���벼������

int n, begin, maxlevel;
int ans;
int a[51];
int f[51][1001]; // ʹ����������ģ�Ⲽ��ֵ��0��ʾfalse����0��ʾtrue

int main() {
    scanf("%d%d%d", &n, &begin, &maxlevel);
    // ��ʼ����ʼ״̬
    f[0][begin] = 1;

    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    // ��̬�滮���
    for (int i = 1; i <= n; i++) {
        for (int j = maxlevel; j >= 0; j--) {
            f[i][j] = 0; // ��ʼ����ǰλ��Ϊfalse
            if (j - a[i] >= 0 && f[i-1][j-a[i]] != 0) {
                f[i][j] = 1; // ������������ߣ������״̬
            }
            if (j + a[i] <= maxlevel && f[i-1][j+a[i]] != 0) {
                f[i][j] = 1; // ������������ߣ������״̬
            }
        }
    }

    // ���ҿɴ�����߶�
    for (int i = maxlevel; i >= 1; i--) {
        if (f[n][i] == 1) {
            printf("%d", i);
            return 0;
        }
    }

    printf("-1");
    return 0;
}
