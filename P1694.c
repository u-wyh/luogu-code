#include <stdio.h>
#include <stdlib.h>

int n, m, a[1005], b[1005], s[1005];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &a[i], &b[i]);
        if (a[i] > b[i]) {
            int temp = a[i];
            a[i] = b[i];
            b[i] = temp;
        }
    }

    for (int i = 1; i <= n; i++) {
        int j;
        for (j = 1; j <= 4; j++) {
            int flag = 0;
            for (int k = 1; k <= m; k++) {
                if (b[k] == i && s[a[k] - 1] == j) { // ע�������±��0��ʼ������Ŀ�п����Ǵ�1��ʼ���ǣ����������Ŀ�߼��Ǵ�1��ʼ
                    flag = 1;
                    break;
                }
            }
            if (!flag) break;
        }
        printf("%d", j);
        s[i - 1] = j; // ͬ���������±��0��ʼ
        //if (i < n) printf(" "); // ����������һ��������ӡ�ո�ָ�
    }
    printf("\n"); // �������
    return 0;
}
