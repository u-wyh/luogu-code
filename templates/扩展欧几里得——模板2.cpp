// ϴ��
// һ����n���ƣ�nһ����ż����ÿ���Ƶ������1��n��ϴ�ƹ�������
// ����n = 6�������������Ϊ1 2 3 4 5 6
// �ȷֳ����1 2 3���Ҷ�4 5 6��Ȼ�����Ҷѵ�i����ǰ����ѵ�i���ں�ķ�ʽ���η���
// ����ϴһ�κ󣬵õ� 4 1 5 2 6 3
// �����ϴһ�Σ��õ� 2 4 6 1 3 5
// �����ϴһ�Σ��õ� 1 2 3 4 5 6
// ��֪��n����ϴm�ε�֮�󣬵�l���ƣ���ʲô����
// 1 <= n <= 10^10��nΪż��
// 0 <= m <= 10^10
// �������� : https://www.luogu.com.cn/problem/P2054
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
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

// ԭ�����ԣ�����033��λ����ʵ�ֳ˷�
// a * b�Ĺ����Լ�ʵ�֣�ÿһ���м���̶�%mod
// ��ôдĿ���Ƿ�ֹ�����Ҳ�й��ٳ�
long long multiply(long long a, long long b, long long mod) {
	// ��Ȼ����%mod�������£���ôa��b���Զ�ת���ɷǸ���
	// ���ⲻת������ν������������Ŀ������Ҫת��
	// ������b��Ҫת��������whileѭ�����ܲ���
	a = (a % mod + mod) % mod;
	b = (b % mod + mod) % mod;
	long long ans = 0;
	while (b != 0) {
		if ((b & 1) != 0) {
			ans = (ans + a) % mod;
		}
		a = (a + a) % mod;
		b >>= 1;
	}
	return ans;
}

// ԭ�����ԣ�����098���˷�������
// ����a��b�η������� % mod �Ľ��
long long power(long long a, long long b, long long mod) {
	long ans = 1;
	while (b > 0) {
		if ((b & 1) == 1) {
			ans = multiply(ans, a, mod);
		}
		a = multiply(a, a, mod);
		b >>= 1;
	}
	return ans;
}

long long compute(long long n, long long m, long long l) {
	long long mod = n + 1;
	exgcd(power(2, m, mod), mod);
	long long x0 = (x % mod + mod) % mod;
	return multiply(x0, l, mod);
}

int main()
{
    long long n,m,l;
    cin>>n>>m>>l;
    cout<<compute(n,m,l);
    return 0;
}
