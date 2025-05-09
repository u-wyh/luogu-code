#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Node {
    ll val, l, r;
};

const int MAXN = 500010;

ll a[MAXN], l[MAXN], r[MAXN];
Node g[MAXN], o[MAXN];
ll cnt_g, cnt_o;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, k, ans = 0;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; ++i) {
        // ���� gcd �б�
        for (int j = 1; j <= cnt_g; ++j) {
            g[j].val = gcd(g[j].val, a[i]);
        }
        cnt_g++;
        g[cnt_g] = {a[i], i, i};

        // ȥ�� gcd �б�
        int len = 0;
        for (int j = 1; j <= cnt_g; ++j) {
            if (g[j].val == g[j - 1].val) {
                g[len].r = g[j].r;
            } else {
                len++;
                g[len] = g[j];
            }
        }
        cnt_g = len;

        // ��¼ÿ�� gcd ֵ��Ӧ�����ұ߽�
        for (int j = 1; j <= cnt_g; ++j) {
            l[g[j].val] = g[j].l;
            r[g[j].val] = g[j].r;
        }

        // ���°�λ���б�
        for (int j = 1; j <= cnt_o; ++j) {
            o[j].val |= a[i];
        }
        cnt_o++;
        o[cnt_o] = {a[i], i, i};

        // ȥ�ذ�λ���б�
        len = 0;
        for (int j = 1; j <= cnt_o; ++j) {
            if (o[j].val == o[j - 1].val) {
                o[len].r = o[j].r;
            } else {
                len++;
                o[len] = o[j];
            }
        }
        cnt_o = len;

        // ͳ������������������
        for (int j = 1; j <= cnt_o; ++j) {
            ll target = o[j].val ^ k;
            if (l[target] != 0 && min(o[j].r, r[target]) >= max(o[j].l, l[target])) {
                ans += min(o[j].r, r[target]) - max(o[j].l, l[target]) + 1;
            }
        }

        // ��� gcd ֵ�����ұ߽��¼
        for (int j = 1; j <= cnt_g; ++j) {
            l[g[j].val] = r[g[j].val] = 0;
        }
    }

    cout << ans << endl;
    return 0;
}
