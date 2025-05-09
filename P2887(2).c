#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a, b;
} node;

node cow[2501], fss[2501];
int c, l, ans;

// �Զ���ȽϺ���������qsort
int cmp(const void *a, const void *b) {
    node *x = (node *)a;
    node *y = (node *)b;
    return x->b - y->b; // ��ţ���Ҷ˵�����
}

int cmp1(const void *a, const void *b) {
    node *x = (node *)a;
    node *y = (node *)b;
    return x->a - y->a; // ��ɹ˪����˵�����
}

int main() {
    scanf("%d%d", &c, &l);
    for (int i = 0; i < c; i++) {
        scanf("%d%d", &cow[i].a, &cow[i].b);
    }
    for (int i = 0; i < l; i++) {
        scanf("%d%d", &fss[i].a, &fss[i].b);
    }

    // ʹ��qsort��������
    qsort(cow, c, sizeof(node), cmp);
    qsort(fss, l, sizeof(node), cmp1);

    for (int i = 0; i < c; i++) {
        for (int j = 0; j < l; j++) {
            if (fss[j].b > 0 && fss[j].a >= cow[i].a && fss[j].a <= cow[i].b) {
                fss[j].b--;
                ans++;
                break;
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}
