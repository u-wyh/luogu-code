#include <stdio.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

int a[101][101], n, m, f[101][101], ans = 0;

int main()
{
    scanf("%d %d", &n, &m); // ����
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &a[i][j]);
            // ��Ϊֻ���õ�i, j�Ϸ����󷽣����Ϸ�����Ϣ������ͬ������
            // ע�⣺��ʼʱf[i][j]��Ҫ��ʼ����������ܰ���δ�����ֵ
            if (i == 1 || j == 1) {
                f[i][j] = a[i][j]; // �߽��������һ��Ԫ��ֱ�Ӹ�ֵ
            } else if (a[i][j] == 1) {
                f[i][j] = min(min(f[i][j-1], f[i-1][j]), f[i-1][j-1] ) + 1;
                // ע�⣺��i��jΪ1ʱ��f[i-1][j-1]��δ����ģ������Ҫ���i��j�Ƿ����1
            }
            ans = max(ans, f[i][j]); // ͬ�����´�
        }
    }
    printf("%d", ans);
    return 0;
}
