// ��������ģ��
// ��ջ˳��涨Ϊ1��2��3..n�������ж����ֲ�ͬ�ĳ�ջ˳��
// ������Ŀ����������С���õ��Ŀ�������û�ж�󣬲���Ҫȡģ����
// ��������裬��n�Ƚϴ�ʱ�����������Ǻܴ�ģ��𰸶� 1000000007 ȡģ
// �������� : https://www.luogu.com.cn/problem/P1044
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
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

// ��ʽ2
long long compute2(int n) {
    build1(2 * n);
    return c(2 * n, n) * power(n + 1, MOD - 2) % MOD;
}

// ��ʽ3
long long compute3(int n) {
    build2(n);
    long long f[n + 1];
    f[0] = f[1] = 1;
    for (int i = 2; i <= n; i++) {
        f[i] = f[i - 1] * (4 * i - 2) % MOD * inv2[i + 1] % MOD;
    }
    return f[n];
}

// ��ʽ4
long long compute4(int n) {
    long long f[n + 1];
    for(int i=0;i<=n;i++){
        f[i]=0;
    }
    f[0] = f[1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int l = 0, r = i - 1; l < i; l++, r--) {
            f[i] = (f[i] + f[l] * f[r] % MOD) % MOD;
        }
    }
    return f[n];
}

int main()
{
    int n;
    cin>>n;
    cout<<compute1(n)<<endl;
    cout<<compute2(n)<<endl;
    cout<<compute3(n)<<endl;
    cout<<compute4(n)<<endl;

    return 0;
}
