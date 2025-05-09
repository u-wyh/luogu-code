// Բ������
// Բ����2n���㣬��Щ��ɶ������������γ�n���߶Σ����������߶β����ཻ���������ӵķ�����
// ע�⣡�𰸲��� 10^9 + 7 ȡģ�����Ƕ� 10^8 + 7 ȡģ��
// 1 <= n <= 2999
// �������� : https://www.luogu.com.cn/problem/P1976
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MOD = 100000007;
const int MAXN = 1000001;

// �׳�������
long long fac[MAXN];
// �׳���Ԫ��
long long inv1[MAXN];
// ��������Ԫ��
long long inv2[MAXN];

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
void build1(int n) {
	fac[0] = inv1[0] = 1;
	fac[1] = 1;
	for (int i = 2; i <= n; i++) {
		fac[i] = ((long long) i * fac[i - 1]) % MOD;
	}
	inv1[n] = power(fac[n], MOD - 2);
	for (int i = n - 1; i >= 1; i--) {
		inv1[i] = ((long long) (i + 1) * inv1[i + 1]) % MOD;
	}
}
	// ���Խ���099����Ŀ2��������������Ԫ��
void build2(int n) {
	inv2[1] = 1;
	for (int i = 2; i <= n + 1; i++) {
		inv2[i] = MOD - inv2[MOD % i] * (MOD / i) % MOD;
	}
}

long long c(int n, int k) {
	return (((fac[n] * inv1[k]) % MOD) * inv1[n - k]) % MOD;
}

// ��ʽ1
long long compute1(int n) {
    build1(2 * n);
    return (c(2 * n, n) - c(2 * n, n - 1) + MOD) % MOD;
}

int main()
{
    int n;
    cin>>n;
    cout<<compute1(n)<<endl;
    return 0;
}
