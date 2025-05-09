// ������
// һ���б��1~n�ı���������a�ź�b�ű����Ѿ��޺���
// Yuwgna��Iaka����������������Yuwgna���֣�Iaka���֣�˭���������е���˭Ӯ
// ÿ�ο���ѡ��j+k�Ż���j-k����������������j��k�����������Ѿ��޺õ���
// Ҳ��������n��a��b���������Ӯ��ӡ"Yuwgna"������Ӯ��ӡ"Iaka"
// 2 <= n <= 2 * 10^4
// �������� : https://acm.hdu.edu.cn/showproblem.php?pid=5512
// �������� : https://vjudge.net/problem/HDU-5512
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<iostream>
using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main()
{
    int cases;
    cin>>cases;
    for (int t = 1, n, a, b; t <= cases; t++) {
        cin>>n>>a>>b;
        cout<<"Case #" << t << ": ";
        if (((n / gcd(a, b)) & 1) == 1) {
            cout<<"Yuwgna"<<endl;
        } else {
            cout<<"Iaka"<<endl;;
        }
    }
    return 0;
}
