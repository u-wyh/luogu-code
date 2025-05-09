// ��չ�й�ʣ�ඨ��ģ��
// ����n��ͬ�෽�̣�������ͬ�෽�̵���С������x
// һ��n��ͬ�෽�̣�x �� ri(% mi)
// 1 <= n <= 10^5
// 0 <= ri��mi <= 10^12
// ����mi��һ������
// ����mi����С������ <= 10^18
// �������� : https://www.luogu.com.cn/problem/P4777
// �������� : https://www.luogu.com.cn/problem/P1495
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

long long m[MAXN];
long long r[MAXN];

long long d, x, y, px, py;

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

// ��չ�й�ʣ�ඨ��ģ��
// �������ڽ��ģ�����ǻ��ʵ����  ���÷�Χ����
long long excrt(int n) {
    long long tail = 0, lcm = 1, tmp, b, c, x0;
    // ans = lcm * x + tail
    for (int i = 1; i <= n; i++) {
        // ans = m[i] * y + ri
        // lcm * x + m[i] * y = ri - tail
        // a = lcm
        // b = m[i]
        // c = ri - tail
        b = m[i];
        c = ((r[i] - tail) % b + b) % b;
        exgcd(lcm, b);
        if (c % d != 0) {
            return -1;
        }
        // ax + by = gcd(a,b)���ؽ��ǣ�x����
        // ax + by = c���ؽ��ǣ�x���� * (c/d)
        // ax + by = c����С�Ǹ��ؽ�x0 = (x * (c/d)) % (b/d) ȡ�Ǹ�����
        // ͨ�� = x0 + (b/d) * n
        x0 = multiply(x, c / d, b / d);
        // ans = lcm * x + tail������ͨ��
        // ans = lcm * (x0 + (b/d) * n) + tail
        // ans = lcm * (b/d) * n + lcm * x0 + tail
        // tail' = tail' % lcm'
        tmp = lcm * (b / d);
        tail = (tail + multiply(x0, lcm, tmp)) % tmp;
        lcm = tmp;
    }
    return tail;
}

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>m[i]>>r[i];
    }
    cout<<excrt(n)<<endl;
    return 0;
}
