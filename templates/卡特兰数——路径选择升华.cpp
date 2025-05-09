// �����ַ���
// ��n��1��m��0��Ҫ���n+m���ȵ����У���֤����ǰ׺�ϣ�1������ >= 0������
// �����ж��������з������𰸶� 20100403 ȡģ
// 1 <= m <= n <= 10^6
// �������� : https://www.luogu.com.cn/problem/P1641
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MOD = 20100403;
const int MAXN = 2000001;

// �׳�������
long long fac[MAXN];
// �׳���Ԫ��
long long inv[MAXN];

long long power(long long x, long long p) {
	long long ans = 1;
	while (p > 0) {
		if ((p & 1) == 1) {
			ans = (ans * x) % MOD;
		}
		x = (x * x) % MOD;
		p >>= 1;
	}
	return ans;
}

// ���Խ���099����Ŀ3�����ɽ׳��������׳���Ԫ��
void build(int n) {
	fac[0] = inv[0] = 1;
	fac[1] = 1;
	for (int i = 2; i <= n; i++) {
		fac[i] = ((long long) i * fac[i - 1]) % MOD;
	}
	inv[n] = power(fac[n], MOD - 2);
	for (int i = n - 1; i >= 1; i--) {
		inv[i] = ((long long) (i + 1) * inv[i + 1]) % MOD;
	}
}

long long c(int n, int k) {
	return (((fac[n] * inv[k]) % MOD) * inv[n - k]) % MOD;
}

int main()
{
    int n,m;
    cin>>n>>m;
    build(n + m);
	cout<<((c(n + m, m) - c(n + m, m - 1) + MOD) % MOD);
    return 0;
}
