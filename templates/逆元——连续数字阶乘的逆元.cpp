// �����׳���Ԫ�����Ե���
// ʵ����Ϲ�ʽC(n,m)�ļ���
// ���ս�� % 1000000007�󷵻�
// 0 <= m <= n <= 1000
// ��������֤
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int LIMIT = 1000;

// �׳˱�
// fac[i] ���� i! �� %MOD �����µ�����
long long fac[LIMIT + 1];

// �׳˽������Ԫ��
// inv[i] ���� i! �� %MOD �����µ���Ԫ (1 / i!)
long long inv[LIMIT + 1];

// �����ݺ��������� x^n % MOD
long long power(long long x, int n) {
    long long ans = 1;
    while (n > 0) {
        if (n & 1) {
            ans = (ans * x) % MOD;
        }
        x = (x * x) % MOD;
        n >>= 1;
    }
    return ans;
}

// ��ʼ���׳˱����Ԫ��
void build() {
    //������׳˱�
    fac[0] = 1; // 0! = 1
    for (int i = 1; i <= LIMIT; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
    }

    // �������Ե����Ż�������Ԫ
    inv[LIMIT] = power(fac[LIMIT], MOD - 2);//������һ�����ֵĽ׳���Ԫ
    for (int i = LIMIT - 1; i >= 0; i--) {
        inv[i] = (inv[i + 1] * (i + 1)) % MOD;//���Ե���
    }
}

// ��Ϲ�ʽ C(n, m) % MOD
// ʹ�ý׳˱����Ԫ��
int c2(int n, int m) {
    if (m > n || m < 0) return 0; // �߽�����
    long long ans = fac[n];
    ans = (ans * inv[m]) % MOD;
    ans = (ans * inv[n - m]) % MOD;
    return (int)ans;
}

// ��Ϲ�ʽ C(n, m) % MOD
// ֱ�Ӽ��㣬��ʹ�ý׳˱����Ԫ��
//�����㷨
int c1(int n, int m) {
    if (m > n || m < 0) return 0; // �߽�����
    long long ans = 1;
    for (int i = 1; i <= m; i++) {
        ans = (ans * (n - m + i)) % MOD;
        ans = (ans * power(i, MOD - 2)) % MOD; // ���� i ����Ԫ
    }
    return (int)ans;
}

int main() {
    cout << "���Կ�ʼ" << endl;
    build();

    // ���� c1 �� c2 ��һ����
    int n = 500;
    for (int m = 0; m <= n; m++) {
        int ans1 = c1(n, m);
        int ans2 = c2(n, m);
        if (ans1 != ans2) {
            cout << "������!" << endl;
        }
        else{
            cout<<"�� "<<setw(3)<<m<<" �����ͨ����"<<endl;
        }
    }
    cout << "���Խ���" << endl;

    // ���� C(a, b) % MOD
    int a = 537;
    int b = 367;
    cout << "���� C(" << a << ", " << b << ") % " << MOD << endl;
    cout << "����1��: " << c1(a, b) << endl;
    cout << "����2��: " << c2(a, b) << endl;

    return 0;
}
