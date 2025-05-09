// ����������м������
// ��ά������ֻ��x��y��ֵ��Ϊ���������꣬�Žи��
// ����������㣬A��(x1, y1)��B��(x2, y2)
// ����A��B�������ϣ�����A��B���ڣ�һ���м������
// -10^9 <= x1��y1��x2��y2 <= 10^9
// �������� : https://lightoj.com/problem/how-many-points
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;

long gcd(long a, long b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main()
{
    int cases ;
    cin>>cases;
    for (int t = 1; t <= cases; t++) {
        long x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        long ans = gcd(abs(x1 - x2), abs(y1 - y2)) + 1;
        cout<<"Case " << t + ": " << ans<<endl;
    }
    return 0;
}
