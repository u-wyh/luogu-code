#include <stdio.h>
#include <string.h>

#define MAX_N 500005

int n, m;
int f[MAX_N];

typedef struct {
    int k, a;
} node;

node e[205];

int cmp(const void *a, const void *b) {
    node *na = (node *)a;
    node *nb = (node *)b;
    return nb->k - na->k; // ��������
}

void bubbleSort(node arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j].k < arr[j+1].k) {
                // ���� arr[j] �� arr[j+1]
                node temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    // freopen("watch.in", "r", stdin);
    // freopen("watch.out", "w", stdout);
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &e[i].k, &e[i].a);
    }
    // ʹ��qsort����ð������
    qsort(e, n, sizeof(node), cmp);

    memset(f, 0, sizeof(f));
    f[0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < MAX_N; j++) {
            if (j >= e[i].k && f[j - e[i].k] && f[j - e[i].k] <= e[i].a) {
                f[j] = f[j - e[i].k] + 1;
            }
            // ע�⣺��C�У����ǲ���Ҫ����ա�f[j]����Ϊmemset�Ѿ��ڿ�ʼʱ������
            // ����C�����鲻���Զ���ʼ��Ϊ0����Ҫ�ֶ�memset��ʹ��������ʽ
        }
    }

    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);
        if (f[x]) printf("Yes\n");
        else printf("No\n");
    }

    return 0;
}
