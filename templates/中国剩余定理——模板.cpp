// �й�ʣ�ඨ��ģ��
// ����n��ͬ�෽�̣�������ͬ�෽�̵���С������x
// һ��n��ͬ�෽�̣�x �� ri(% mi)
// 1 <= n <= 10
// 0 <= ri��mi <= 10^5
// ����miһ������
// ����mi����˻� <= 10^18
// �������� : https://www.luogu.com.cn/problem/P1495
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 11;

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

// �й�ʣ�ඨ��ģ��  ֻ������ģ�����ʵ����
long long crt(int n) {
    long long lcm = 1;
    for (int i = 1; i <= n; i++) {
        lcm = lcm * m[i];
        //��Ϊm�ǻ��ʵ�  ������С�������������ǵ��۳�
    }
    long long ai, ci, ans = 0;
    for (int i = 1; i <= n; i++) {
        // ai = lcm / m[i]
        // �� m1 * m2 *```* mi-1 * mi+1 *```* mn-1 * mn
        ai = lcm / m[i];
        // ai��Ԫ����%m[i]�����µ���Ԫ
        exgcd(ai, m[i]);
        // ci = (ri *   ai * ai��Ԫ(��x)  ) % lcm
        ci = multiply(r[i], multiply(ai, x, lcm), lcm);
        ans = (ans + ci) % lcm;
    }
    return ans;
}

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>m[i]>>r[i];
    }
    cout<<crt(n)<<endl;
    return 0;
}
