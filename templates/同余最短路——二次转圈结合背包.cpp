// ����(����תȦ��)
// һ����n����Ʒ����i����Ʒ�����Ϊv[i]����ֵΪc[i]��ÿ����Ʒ����ѡ������������������Ǹ���
// һ����m����ѯ��ÿ�β�ѯ�������jobv�����������Ҫ��
// Ҫ����ѡ��Ʒ�������һ��Ҫ�ϸ���jobv�������ܵõ�������ֵ��
// ���û�з��������ô���jobv������-1
// 1 <= n <= 50
// 1 <= m <= 10^5
// 1 <= v[i] <= 10^5
// 1 <= c[i] <= 10^6
// 10^11 <= jobv <= 10^12
// �������� : https://www.luogu.com.cn/problem/P9140
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const long long inf = LLONG_MIN; // ʹ�� LLONG_MIN ��ʾ������

int v[MAXN]; // ��Ʒ���
int c[MAXN]; // ��Ʒ��ֵ
// dp[i] : �����Ϊĳ�����Ⱦ������û�׼��Ʒ���룬ʣ������Ϊi
// ����ȥ�����ɻ�׼��Ʒ����������������Ʒ�����մ��������
// �ܻ�õ���󲹳��Ƕ���
long long dp[MAXN]; // dp ����

int n, m, x, y;

// �������Լ��
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// ���� dp ����  ���ʵ�������·
void compute() {
    fill(dp, dp + x, inf); // ��ʼ�� dp ����Ϊ������
    dp[0] = 0; // ���Ϊ 0 ʱ����ֵΪ 0

    for (int i = 1; i <= n; i++) {
        if (v[i] != x) { // ������׼��Ʒ
            int d = gcd(v[i], x); // �������Լ��
            for (int j = 0; j < d; j++) {
                for (int cur = j, next, circle = 0; circle < 2; circle += (cur == j ? 1 : 0)) {
                    next = (cur + v[i]) % x; // ������һ��״̬
                    if (dp[cur] != inf) { // �����ǰ״̬�ɴ�
                        dp[next] = max(dp[next], dp[cur] - (long long)((cur + v[i]) / x) * y + c[i]);
                    }
                    cur = next; // ���µ�ǰ״̬
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false); // �����������
    cin.tie(nullptr);

    cin >> n >> m;

    double best = 0, ratio;
    for (int i = 1; i <= n; i++) {
        cin >> v[i] >> c[i];
        ratio = (double)c[i] / v[i]; // �����Լ۱�
        if (ratio > best) { // �ҵ��Լ۱���ߵ���Ʒ
            best = ratio;
            x = v[i]; // ��׼��Ʒ���
            y = c[i]; // ��׼��Ʒ��ֵ
        }
    }

    compute(); // ���� dp ����

    long long jobv;
    for (int i = 1; i <= m; i++) {
        cin >> jobv;
        int remainder = jobv % x; // ��������
        if (dp[remainder] == inf) { // �������״̬���ɴ�
            cout << "-1\n";
        } else {
            cout << (jobv / x) * y + dp[remainder] << "\n"; // �������ֵ
        }
    }

    return 0;
}
