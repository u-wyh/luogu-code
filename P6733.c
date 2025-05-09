#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define eps 1e-3
#define MAX_N 100005

int n;
ll k;
int a[MAX_N], c[MAX_N]; // a ����, c �¶�
double p[MAX_N], q[MAX_N];

int cmp(const void *a, const void *b) {
    double d1 = *(double *)a;
    double d2 = *(double *)b;
    return d1 < d2 ? -1 : (d1 > d2 ? 1 : 0);
}
//��С����

int check(double v) {
    ll tot = 0;
    for (int i = 1; i <= n; i++) {
        double x = a[i] * 1.0 * c[i], y = v * a[i];
        p[i] = x - y;
        q[i] = y - x;
        if (q[i] - p[i] < eps) tot--;
    }
    //���ȼ�ȥ�Լ����Լ��Ŀ�����  ��Ϊ�������Ҫ����2  �������ǰ��ȥ  �𰸲�����
    qsort(p + 1, n, sizeof(double), cmp);
    qsort(q + 1, n, sizeof(double), cmp);
    int j = 0;
    for (int i = 1; i <= n; i++) {
        while ((q[j + 1] <= p[i]) && j + 1 <= n) j++;
        tot += j;
    }
    return (tot / 2 < k);
    //����ΪʲôҪ����2
    //i��5 -5(��Ȼ)  j��2 -2
    //��ô�ͻ���ij(5  -2)  ��ji(2  -5)  ���¶�������
    //����ii(5 -5)  jj(2  -2)Ҳ�ᱻ����   ����֮ǰ�Ѿ���ȥ��
}

int main() {
    scanf("%d%lld", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i], &c[i]);
    }
    double l = 1, r = 1000000000, mid;
    //����r��ʼֵ������c[i]�����ֵ�Ϳ�����
    while ((r - l) > eps) {
        mid = (l + r) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    printf("%.3f\n", l);
    return 0;
}
