// ������ģ����
// ��������Ϊn��һ������ֵ[a1, a2, a3...]�����ҵ�һ����ֵ[x1, x2, x3...]
// Ҫ��a1*x1 + a2*x2 + a3*x3...�õ��Ľ��Ϊ��С������
// �����ܵõ�����С�������Ƕ���
// 1 <= n <= 20
// 1 <= ai <= 10^5
// �������� : https://www.luogu.com.cn/problem/P4549
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main()
{
    int n;
    cin>>n;
    int ans=0;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        ans=gcd(abs(k),ans);
    }
    cout<<ans<<endl;
    return 0;
}
