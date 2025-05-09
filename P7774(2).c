#include <stdio.h>
#include <stdbool.h>

int n, m;
int a[15], b[15];
bool f[1005]; // ע������ʹ��bool����

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d", &b[i]);
    }

    // ��ʼ��f���飬��f[0]Ϊtrue
    memset(f, 0, sizeof(f));
    f[0] = true;

    // ���f����
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 1000; j++) {
            // ע������ʹ���߼���������Ľ��������f�����ֵ
            if (j >= a[i]) {
                f[j % 360] = f[j % 360] || f[(j - a[i]) % 360];
            }
            f[j % 360] = f[j % 360] || f[(j + a[i]) % 360];
        }
    }

    // �����
    for (int i = 1; i <= m; i++) {
        if (f[b[i] % 360]) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}
