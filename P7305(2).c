#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int n, m, cnt, flag, i;
int a[100010], b[100010];
int l, r, mid;

int cmp(const void *a,const void *b){
    return (*(int *)a-*(int *)b);
}


// ��麯��
bool check(int x) {
    int t = 1, w = 1, s = 0;
    while (t <= n && w <= m) {
        if (abs(a[t] - b[w]) <= x) {
            t++;
            w++;
            s++;
        } else if (flag) {
            w++;
        } else {
            t++;
        }
    }
    return s == cnt;
}

int main() {
    scanf("%d%d", &n, &m);
    cnt = (n < m) ? n : m; // ���Ҫ��ﵽЬ����
    if (cnt == n) {
        flag = true; // ���б��
    } else {
        flag = false;
    }
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (i = 1; i <= m; i++) {
        scanf("%d", &b[i]);
    }
    qsort(a + 1, n, sizeof(int), cmp);
    qsort(b + 1, m, sizeof(int), cmp);

    // ����ȽϺ���
    int cmp(const void *pa, const void *pb) {
        int a = *(int *)pa;
        int b = *(int *)pb;
        return a - b;
    }

    l = 0;
    r = 1e9;
    while (l < r) {
        mid = l + (r - l) / 2; // ע�����������ŷ�ֹ�������
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    printf("%d", l); // ע������Ӧ����l����Ϊ����������С�������߽�

    return 0;
}
