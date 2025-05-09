// �ŷ�����(��������)
// һ��n���ˣ�ÿ���˶�д��һ����
// ÿ���˱���ĳ�һ���ţ�ÿ���˱����յ�һ���ţ����Ҳ����Լ��ĸ��Լ�
// ����һ���ж����ּ��ŵķ���
// 1 <= n <= 20
// �������� : https://www.luogu.com.cn/problem/P1595
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;

// ��ͨ��̬�滮�ķ���
long ways1(int n) {
    long dp[n + 1];
    for (int i = 1; i <= n; i++) {
        if (i == 1) {
            dp[i] = 0;
        } else if (i == 2) {
            dp[i] = 1;
        } else {
            dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]);
        }
    }
    return dp[n];
}

// ����ʽ���ݵķ���
long ways2(int n) {
    long facn = 1; // n!
    for (int i = 1; i <= n; i++) {
        facn *= i;
    }
    long ans = facn; // i = 0ʱ����
    long faci = 1; // i!
    for (int i = 1; i <= n; i++) {
        // i = 1...n
        // (-1)��i�η� * (n! / i!)
        faci = faci * i;
        if ((i & 1) == 0) {
            ans += facn / faci;
        } else {
            ans -= facn / faci;
        }
    }
    return ans;
}

int main()
{
    int n;
    cin>>n;
    //cout<<ways1(n)<<endl;
    cout<<ways2(n)<<endl;
    return 0;
}
