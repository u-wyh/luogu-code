#include <iostream>

using namespace std;

// ��չŷ������㷨
// ���ڷ���ax + by = gcd(a,b)
// ��a��bȷ������ôgcd(a,b)Ҳȷ��
// ��չŷ������㷨���Ը���a��b�����Լ��d���Լ�����һ���ؽ�x��y
// �ر�ע��Ҫ��֤���a��bû�и���
long long d, x, y, px, py;

void exgcd(long long a, long long b) {
    if (b == 0) {
        d = a;
        x = 1;
        y = 0;
    } else {
        exgcd(b, a % b);
        px = x;
        py = y;
        x = py;
        y = px - py * (a / b);
    }
}

// �������㷨
long long power(long long num, long long pow, long long mod) {
    long long ans = 1;
    while (pow > 0) {
        if (pow % 2 == 1) {
            ans = (ans * num) % mod;
        }
        num = (num * num) % mod;
        pow /= 2;
    }
    return ans;
}

// ����С���������Ԫ
long long fermat(long long num, long long mod) {
    return power(num, mod - 2, mod);
}

int main() {
    // ��չŷ������㷨����
    long long a = 110;
    long long b = 170;
    exgcd(a, b);
    cout << "gcd(" << a << ", " << b << ")" << " = " << d << endl;
    cout << "x = " << x << ", " << " y = " << y << endl;

    // ��չŷ������㷨����ȥ����Ԫ
    cout << "����Ԫ���Կ�ʼ" << endl;
    long long mod = 1000000007;
    long long test = 10000000;
    for (long long num = 1; num <= test; ++num) {
        exgcd(num, mod);
        x = (x % mod + mod) % mod;
        if (x != fermat(num, mod)) {
            cout << "������!" << endl;
            break; // ����ѡ���Ƿ��ж�ѭ��������ѡ���ж��Ա���ٷ�������
        }
    }
    cout << "����Ԫ���Խ���" << endl;

    return 0;
}
