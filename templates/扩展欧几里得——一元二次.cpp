// ���ܵ�Լ��
// ��һ���ܳ�Ϊl�Ļ����ӻ���0λ�ÿ�ʼ���涨ֻ������˳ʱ�뷽��ͣתȦ
// ����A�ڻ���x1λ�ã�ÿ����m����λ������B��x2λ�ã�ÿ����n����λ
// ֻ����ĳʱ�̣�����A������B��������ͬһ��λ�ã���������
// �����ֻ�����������ˣ���ӡ"Impossible"
// ���������������ӡ��ֻ�������ٶ�ò�������
// 1 <= l <= 3 * 10^9
// 1 <= x1��x2��m��n <= 2 * 10^9
// x1 != x2
// �������� : https://www.luogu.com.cn/problem/P1516
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
    long long x1,x2,m,n,l;
    cin>>x1>>x2>>m>>n>>l;
    long long a,c;
    if (x1 < x2) {
        //����ڶ�ֻ��ǰ  ���ǵ�һֻ׷�ڶ�ֻ
        a = m - n;
        c = x2 - x1;
    } else {
        a = n - m;
        c = x1 - x2;
    }
    if (a < 0) {
        a = -a;
        c = l - c;
    }
    exgcd(a, l);
    if (c % d != 0) {
        cout<<"Impossible"<<endl;
    } else {
        // ������ؽ�
        long long x0 = x * c / d;
        // ���η���
        long long xd = l / d;
        // x0������>=1����С������������취����һ��һ��
        if (x0 < 0) {
            x0 += (1 - x0 + xd - 1) / xd * xd;
        } else {
            x0 -= (x0 - 1) / xd * xd;
        }
        cout<<x0<<endl;
    }
    return 0;
}
