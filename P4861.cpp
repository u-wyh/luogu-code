#include<bits/stdc++.h>
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

int main()
{
    long long n,m;
    cin>>m>>n;
    exgcd(n,m);
    if(d!=1){
        cout<<"Let's go Blue Jays!"<<endl;
        return 0;
    }
    long long tmp=1;
    int t=1;
    while(1){
        tmp=multiply(n,tmp,m);
        if(tmp==1){
            cout<<t;
            return 0;
        }
        t++;
    }
    return 0;
}
