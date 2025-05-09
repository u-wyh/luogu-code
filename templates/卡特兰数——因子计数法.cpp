// ��Ȥ������(��Ҫ! ���Ӽ�����)
// ���n���������Ҫ��𰸶�pȡģ
// 1 <= n <= 10^6
// 1 <= p <= 10^9
// p���ܲ�Ϊ����
// �������� : https://www.luogu.com.cn/problem/P3200
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2000001;

// ���minpf[i] == 0������i������
// ���minpf[i] != 0������i�Ǻ�����������С��������minpf[i]
int minpf[MAXN];
// ������
int prime[MAXN];
// �������С
int cnt;
// ���Ӽ���
int counts[MAXN];

// ���Խ���097��ŷ��ɸ��ʱ�临�Ӷ�O(n)
void euler(int n) {
    for(int i=2;i<n;i++){
        minpf[i]=0;
    }
    cnt = 0;
    for (int i = 2; i <= n; i++) {
        // minpf[i] == 0����iΪ�������ռ���������
        // minpf��������˽���097��visit���������
        if (minpf[i] == 0) {
            prime[cnt++] = i;
        }
        for (int j = 0; j < cnt; j++) {
            if (i * prime[j] > n) {
                break;
            }
            // ��ʱ�ռ�(i * prime[j])���������С������Ϊprime[j]
            // minpf[i * prime[j]] != 0��Ҳ�����(i * prime[j])�Ǻ���
            // ����097ŷ��ɸ�Ĳ��֣��ص������������̣�����ض�
            minpf[i * prime[j]] = prime[j];
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}

long long power(long x, long p, int mod) {
    long ans = 1;
    while (p > 0) {
        if ((p & 1) == 1) {
            ans = (ans * x) % mod;
        }
        x = (x * x) % mod;
        p >>= 1;
    }
    return ans;
}

// ʹ�õ��ǹ�ʽ2 + �����Ӽ�����
int compute(int n, int mod) {
    // ����ŷ��ɸ����[2 ~ 2*n]��Χ������������С������
    // ���xΪ������minpf[x] == 0
    // ���xΪ������x����С������Ϊminpf[x]
    euler(2 * n);
    // ��ĸÿ���������ü���
    for(int i=2;i<n+1;i++){
        counts[i]=-1;
    }
    // ����ÿ���������ü���
    for(int i=n+2;i<=2*n;i++){
        counts[i]=1;
    }
    // �Ӵ�С��ÿ����ͳ�Ƽ���
    // ����������С���������ֽ⣬��ɸ�С���ֵļ���
    // �����޷��ֽ⣬����ȷ�����������ݼ���˻�
    for (int i = 2 * n; i >= 2; i--) {
        if (minpf[i] != 0) {
            counts[minpf[i]] += counts[i];
            counts[i / minpf[i]] += counts[i];
            counts[i] = 0;
        }
    }
    // ÿ���������ݣ�������������������
    long long ans = 1;
    for (int i = 2; i <= 2 * n; i++) {
        if (counts[i] != 0) {
			ans = ans * power(i, counts[i], mod) % mod;
        }
    }
    return (int) ans;
}

int main()
{
    int n;
    cin>>n;
    int mod;
    cin>>mod;
    cout<<compute(n,mod);
    return 0;
}
