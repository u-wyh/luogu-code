#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9 + 7;

// �����ݺ��������� a^b % MOD
int power(int a, int b) {
    int ans = 1;
    a = a % MOD;
    while (b > 0) {
        if (b & 1) {
            ans = (ans * a) % MOD;
        }
        a = (a * a) % MOD;
        b >>= 1;
    }
    return ans;
}

// ����ģ MOD �µ���Ԫ
int inv(int x) {
    return power(x, MOD - 2);
}

signed main() {
    int n, p, t;
    cin >> n >> p >> t;

    int inv2 = inv(2); // 1/2 ����Ԫ
    int inv2n = inv(2 * n); // 1/(2n) ����Ԫ
    int invt1 = inv(t + 1); // 1/(t+1) ����Ԫ

    int q = ((1 - 2 * p) % MOD + MOD) % MOD;
    q = (q * q) % MOD;

    // ����ȱ����еĺͣ�sum = (q^(t+1) - 1) / (q - 1)
    int sum;
    if (q == 1) {
        // ��� q == 1���ȱ����еĺ�Ϊ t + 1
        sum = (t + 1) % MOD;
    } else {
        // ����ʹ�õȱ�������͹�ʽ
        sum = q*(power(q, t + 1) - 1 + MOD) % MOD;
        sum = sum * inv(q - 1) % MOD;
    }

    // �����
    int ans = (1+t + sum) % MOD; // 1 + sum
    ans = ans * inv2 % MOD; // ���� 1/2
    ans = ans * inv2n % MOD; // ���� 1/(2n)
    ans = ans * invt1 % MOD; // ���� 1/(t+1)

    // ������
    cout << (ans+MOD)%MOD << endl;
    return 0;
}
