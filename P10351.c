#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int tot;
} num;

// �ȽϺ���������qsort
int compare(const void *a, const void *b) {
    num *numA = (num *)a;
    num *numB = (num *)b;
    // ע�⣬������C++�е�����������෴����Ϊqsort��Ҫ���ظ������������
    if (numA->tot > numB->tot) return -1;
    if (numA->tot < numB->tot) return 1;
    return 0;
}

int main() {
    int n, tot = 0, ans = 0;
    scanf("%d", &n);
    num cnt[500001] = {0}; // ��ʼ������

    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        if (!cnt[x].tot) tot++;
        cnt[x].tot++;
    }

    // ʹ��qsort��������
    qsort(cnt + 1, n, sizeof(num), compare);

    // ���¼���tot����Ϊqsort�����ԭ���飬�����������ǲ���Ҫ��ֻ����n����tot���к�������
    tot = n;

    for (int i = 1; i <= n; ++i) {
        if (cnt[i].tot * 2 - 1 >= tot) {
            ans++;
            break;
        }
        ans++;
        tot -= cnt[i].tot * 2 - 1;
    }

    printf("%d\n", ans);

    return 0;
}
