#include<bits/stdc++.h>
using namespace std;
const int MOD = 1000003;

int n, k, m;
string str[15];
int cnt[1 << 15];
int match[50][26]; // ������match ����Ĵ�С��Ϊ 50 * 26

int main() {
    // ��ʼ�� cnt ����
    cnt[0] = 0;
    for (int i = 1; i < (1 << 15); i++) {
        cnt[i] = cnt[i - (i & -i)] + 1;
    }

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> str[i];
        }

        if (k > n) {
            cout << 0 << endl;
            continue;
        }

        m = str[0].size();
        memset(match, 0, sizeof(match));

        // ��ʼ�� match ����
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < 26; j++) {
                for (int p = 0; p < n; p++) {
                    if (str[p][i] == '?' || str[p][i] - 'a' == j) {
                        match[i][j] |= (1 << p);
                    }
                }
            }
        }

        // ʹ���ݳ�ԭ�����ǡ��ƥ�� k ���ַ����ķ�����
        int ans = 0;
        for (int i = k; i <= n; i++) {
            int tmp = 0;
            for (int s = 0; s < (1 << n); s++) {
                if (cnt[s] == i) {
                    int res = 1;
                    for (int j = 0; j < m; j++) {
                        int cnt_match = 0;
                        for (int p = 0; p < 26; p++) {
                            if ((match[j][p] & s) == s) { // ��� match[j][p] �Ƿ���� s �������ַ���
                                cnt_match++;
                            }
                        }
                        res = (res * cnt_match) % MOD;
                    }
                    tmp = (tmp + res) % MOD;
                }
            }
            // �ݳ�ϵ����(-1)^(i-k) * C(i, k)
            int sign = (i - k) % 2 == 0 ? 1 : -1;
            int comb = 1; // C(i, k)
            for (int j = 1; j <= k; j++) {
                comb = comb * (i - j + 1) / j;
            }
            ans = (ans + sign * comb * tmp + MOD) % MOD;
        }
        cout << ((ans%MOD)+MOD)%MOD << endl;
    }
    return 0;
}
