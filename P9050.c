#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef long long ll;

// ��Ľṹ��
typedef struct {
    ll big;
    ll id;
} fish;

// �ȽϺ���������qsort
int fishCmp(const void *a, const void *b) {
    fish *fa = (fish *)a;
    fish *fb = (fish *)b;
    return fa->big - fb->big;
}

// �ж�һ�����Ƿ����������
bool solve(fish *a, ll n, ll x) {
    ll temp = a[x].big;
    for (ll i = 0; i < n; i++) {
        if (i == x) continue;
        if (temp > a[i].big) {
            temp += a[i].big;
        } else {
            return false;
        }
    }
    return true;
}

int main() {
    ll n;
    scanf("%lld", &n);
    fish a[500005];
    for (ll i = 0; i < n; i++) {
        scanf("%lld", &a[i].big);
        a[i].id = i + 1; // ��ĿҪ�������1��ʼ��id
    }

    // ʹ��qsort��������
    qsort(a, n, sizeof(fish), fishCmp);

    ll l = 0, r = n - 1;
    ll res = n; // ��ʼ��Ϊn����ʾû���ҵ�������������
    while (l <= r) {
        ll mid = (l + r) / 2;
        if (solve(a, n, mid)) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    // ���res��Ȼ��n�����ʾû�������������
    bool arr[500005] = {0};
    if (res != n) {
        for (ll i = res; i < n; i++) {
            arr[a[i].id - 1] = true; // ����������0��ʼ����id��1��ʼ
        }
    }

    // ������
    for (ll i = 0; i < n; i++) {
        putchar(arr[i] ? 'T' : 'N');
    }
    putchar('\n'); // ���ϻ��з���ʹ������淶

    return 0;
}
