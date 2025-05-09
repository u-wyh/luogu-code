#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} fff;

fff a[100001];

// �ȽϺ���������qsort
int cmp(const void *l, const void *v) {
    fff *left = (fff *)l;
    fff *right = (fff *)v;
    return left->x - right->x;
}

int main() {
    int m, n, t, k;
    scanf("%d%d", &m, &n);

    for (int i = 0; i < m; i++) {  // ע������������0��ʼ
        scanf("%d", &a[i].x);
        a[i].y = i + 1;  // Ϊÿ����Ŀ��ţ���1��ʼ
    }

    qsort(a, m, sizeof(fff), cmp);  // ʹ��qsort��������

    for (int i = 0; i < n; i++) {
        scanf("%d%d", &t, &k);
        int found = 0;  // ����Ƿ��ҵ�
        for (int j = 0; j < m; j++) {
            if (a[j].y >= t && a[j].y <= k) {
                printf("%d ", a[j].x);
                found = 1;
                break;  // һ��С�Ż�
            }
        }
        if (!found) {  // ���û���ҵ��������һ������ֵ�����κβ���������δ������
            // ����ѡ�����һЩ���������"Not Found"
        }
    }

    return 0;
}
