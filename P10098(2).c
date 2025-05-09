#include <stdio.h>
#include <stdlib.h>

#define N 105

typedef struct {
    long long z, a, b;
} node;

node mp[N];
int n;
long long p;

int judge(long long x) { // ���ֲ��ҵĸ�������
    long long sum = 0;
    for (int i = 0; i < n; i++) { // ע������������0��ʼ
        if (x <= mp[i].z) {
            sum += mp[i].a * x;
        } else {
            sum += (mp[i].a * mp[i].z + mp[i].b * (x - mp[i].z));
        }
    }
    return sum >= p; // �Ƚ�
}

int main() {
    scanf("%d %lld", &n, &p); // ʹ��scanf��������
    for (int i = 0; i < n; i++) { // ע������������0��ʼ
        scanf("%lld %lld %lld", &mp[i].z, &mp[i].a, &mp[i].b);
    }

    long long l = 1, r = p, mid, ans = 0; // �� long long
    while (l <= r) {
        mid = (l + r) / 2; // ע������ʹ����������
        if (judge(mid)) {
            r = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
    }

    printf("%lld\n", ans); // ʹ��printf�������
    return 0;
}
