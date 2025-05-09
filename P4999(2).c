#include <stdio.h>
#include <stdlib.h>
#define mod 1000000007

long long count(long long num, int d) {
    long long ans = 0;
    for (long long right = 1, tmp = num, left, cur; tmp != 0; right *= 10, tmp /= 10) {
        left = tmp / 10;
        //left����һλ��߿����е������  ��0��ʼ
        if (d == 0) {
            left--;
        }
        //���d����0   ��ôleft��1��ʼ
        ans =(ans+(left * right)%mod)%mod;
        //ans��������ߵ����������ұ����
        cur = tmp % 10;
        //cur�ǵ�ǰλ���ϵ�����
        if (cur > d) {
            ans =(ans+ (right%mod))%mod;
            //���cur����d   ��ô������Ҫ����1  �ұ��Ǵ�0  ��right-1
        } else if (cur == d) {
            ans =(ans+((num % right)%mod)+1)%mod;
            //���cur����d   ��ô���ǰ��ұ�ʣ������ּ���
        }
    }
    return ans;
}
//right��ȡֵʼ�ն���10 100 1000 10000 ����������

long long digitsCount(int d, long long  a, long long b) {
    return (count(b, d)%mod - count(a - 1, d)%mod +mod)%mod;
}
//d�ĺ���������d  0 1 2 3 4 5 6 7 8 9
//�����a��b���������ֵ��������   �൱�����1��b��  ��ȥ��1��a��

int main() {
    int t;
    scanf("%d",&t);
    long long a, b;
    while(t--)
    {
        scanf("%lld %lld",&a,&b);
        long long ans=0;
        for (int i = 1; i <= 9; i++) {
            ans=(ans+(digitsCount(i,a,b)*i)%mod)%mod;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
