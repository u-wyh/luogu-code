#include <stdio.h>
#include <stdlib.h>

// ���� long long ���ͣ������������֧���������Ҫ����
typedef long long ll;

// ��� min �����Ķ��壬��Ϊ C ��׼����û��ֱ���ṩ
ll min(ll a, ll b) {
    return a < b ? a : b;
}

int main() {
    ll n, t, sum = 0, ans = 0, pos, d[100010], b[100010];
    scanf("%lld%lld", &n, &t);

    // ע�⣺d[0] δ����ʼ������������ d[i-1] �� i=1 ʱ��δ����ģ���Ҫ�ر���
    // ���� d[0] = 0��������Ӷ� i=1 �����⴦��
    d[0] = 0; // ������ʼλ��Ϊ0

    for (ll i = 1; i <= n; i++) {
        scanf("%lld%lld", &d[i], &b[i]);

        // ע�⣺�� i=1 ʱ��d[i-1] �� d[0]�������Ѿ�����Ϊ0
        pos = min(sum, d[i] - d[i - 1]); // �� i=1 ʱ�����ƶ�
        sum -= pos;
        ans += pos;
        sum += b[i];
    }

    // ע�⣺t-d[n]+1 ���ܳ��� ll ��Χ����������費��
    printf("%lld\n", ans + min(sum, t - d[n] + 1));

    return 0;
}
