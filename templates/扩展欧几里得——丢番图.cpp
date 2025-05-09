// ��Ԫһ�β�������ģ��
// ����a��b��c����ⷽ��ax + by = c
// ��������޽��ӡ-1
// ����������������⣬������������
// ��ӡ��Щ�������У�x����С����ֵ��y����С����ֵ
// ����������������⣬��ӡ���������������ͬʱ��ӡ�������������У�
// x����С����ֵ��y����С����ֵ��x���������ֵ��y���������ֵ
// 1 <= a��b��c <= 10^9
// �������� : https://www.luogu.com.cn/problem/P5656
// ����ʵ������ȷ�ģ��������ƽ̨�Կռ俨�ĺ��ϣ�ֻ��ʹ��C++��ȫ��ͨ��
// java�İ汾�����޷���ȫͨ���ģ��ռ�ᳬ�����ƣ���Ҫ��IO�ռ�ռ�ô�
// �������ƽ̨û���չ˸������Ե�ʵ�������µ�
// ���������ԡ�����ʱ��һ���Ǽ�˸������Եģ���ʵ����һ����ȷ��
// C++�汾����Code01_DiophantineEquation2�ļ�
// C++�汾��java�汾�߼���ȫһ������ֻ��C++�汾����ͨ�����в�������
#include <iostream>
#include <cstdio>
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

long long a, b, c, xd, yd, times;

int main()
{
    int cases;
    scanf("%d", &cases);
    for (int t = 1; t <= cases; t++) {
        scanf("%lld %lld %lld", &a, &b, &c);
        exgcd(a, b);
        if (c % d != 0) {
            printf("-1\n");
        } else {
            x *= c / d;
            y *= c / d;
            //�ҵ��ؽ�
            xd = b / d;
            yd = a / d;
            if (x < 0) {
                times = (xd - x) / xd;
                x += xd * times;
                y -= yd * times;
            } else {
                times = (x - 1) / xd;
                x -= xd * times;
                y += yd * times;
            }
            //xΪ����0����С��ֵʱ  y��ʱӦ������x>0�����������
            //��Ϊx��y�Ǵ����˳��Ĺ�ϵ
            if (y <= 0) {
                //˵����������������
                printf("%lld ", x);
                printf("%lld\n", y + yd * ((yd - y) / yd));
            } else {
                printf("%lld ", ((y - 1) / yd + 1));
                printf("%lld ", x);
                printf("%lld ", (y - (y - 1) / yd * yd));
                printf("%lld ", (x + (y - 1) / yd * xd));
                printf("%lld\n", y);
            }
        }
    }
    return 0;
}
