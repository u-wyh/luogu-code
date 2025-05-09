#include<bits/stdc++.h>
using namespace std;

// 扩展欧几里得算法
// 对于方程ax + by = gcd(a,b)
// 当a和b确定，那么gcd(a,b)也确定
// 扩展欧几里得算法可以给出a和b的最大公约数d、以及其中一个特解x、y
// 特别注意要保证入参a和b没有负数
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

// 原理来自，讲解033，位运算实现乘法
// a * b的过程自己实现，每一个中间过程都%mod
// 这么写目的是防止溢出，也叫龟速乘
long long multiply(long long a, long long b, long long mod) {
	// 既然是在%mod的意义下，那么a和b可以都转化成非负的
	// 本题不转化无所谓，但是其他题目可能需要转化
	// 尤其是b需要转化，否则while循环会跑不完
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

// 原理来自，讲解098，乘法快速幂
// 计算a的b次方，最终 % mod 的结果
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
