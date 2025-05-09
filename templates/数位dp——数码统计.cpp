// ��Χ�ڵ����ּ���
// ��������������a��b������[a,b]��Χ�ϵ�����������
// ÿ������(digit)�������˶��ٴ�
// 1 <= a, b
// �������� : https://www.luogu.com.cn/problem/P2602
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��

#include<bits/stdc++.h>
using namespace std;

long a,b;

long count(long num, int d) {
    long ans = 0;
    for (long right = 1, tmp = num, left, cur; tmp != 0; right *= 10, tmp /= 10) {
        left = tmp / 10;
        if (d == 0) {
            left--;
        }
        ans += left * right;
        cur = tmp % 10;
        if (cur > d) {
            ans += right;
        } else if (cur == d) {
            ans += num % right + 1;
        }
    }
    return ans;
}

int main()
{
    cin>>a>>b;
    for(int d=0;d<10;d++){
        cout<<(count(b,d)-count(a-1,d))<<' ';
    }
    return 0;
}
