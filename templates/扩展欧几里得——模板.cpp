// ͬ�෽��
// �����x��ͬ�෽�� ax �� 1(mod b) ����С��������
// ��Ŀ��֤һ���н⣬Ҳ����a��b����
// 2 <= a��b <= 2 * 10^9
// �������� : https://www.luogu.com.cn/problem/P1082
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;

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

int main()
{
    long long a,b;
    cin>>a>>b;
    exgcd(a,b);
    cout<<((x % b + b) % b);
    return 0;
}
