#include <stdio.h>

typedef long long ll;

// ������ϣ�b�����棬a�����棩
ll C(ll b, ll a) {
    ll sum = 1;
    for (ll i = b, j = 1; j <= a; i--, j++) {
        sum = sum * i / j;
    }
    return sum;
}

int main() {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    ll cnt = 0, ans = 0;

    if (n == k && k == 1) {
        ans = 1;
        printf("%lld\n", ans);
        return 0;
    }

    for (int i = 62; i >= 1; --i) {
        if (k - cnt + 1 == 0)
            break;
        if ((1ll << i) & n) {
            cnt++;
            if (i >= k - cnt + 1) {
                //����ͳ�Ƶ��� ��һλ������1��ʱ��  ���ǿ��Ϊ0  ��ô�����ж����ִ�
                //�����ڴ�֮ǰλ������1�� ���ڻ���1
                ans += C(i, k - cnt + 1);
            }
        }
    }

    if (cnt == k)
        ans++;

    printf("%lld\n", ans);
    return 0;
}
