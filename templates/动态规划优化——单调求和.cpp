// ����������k��Ԫ�ص�����ۼӺ�
// ����һ������Ϊn������arr�����������ѡ������
// Ҫ��ѡ��ķ����У�����ѡ��ĸ������ܳ���k��
// �����ܵõ�������ۼӺ�
// 1 <= n��k <= 10^5
// 0 <= arr[i] <= 10^9
// �������� : https://www.luogu.com.cn/problem/P2627
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ����������
#include<bits/stdc++.h>
using namespace std;

int n,k;
int arr[100005];
long sum[100005];
long q[100005];
long dp[100005];
int l,r;

// ��Ҫiλ�õ����ֲ�����ָ��
long value(int i) {
	return i == 0 ? 0 : (dp[i - 1] - sum[i]);
}

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + arr[i];
    }
    l = r = 0;
    q[r++] = 0;
    for (int i = 1; i <= n; i++) {
        while (l < r && value(q[r - 1]) <= value(i)) {
            r--;
        }
        q[r++] = i;
        if (l < r && q[l] == i - k - 1) {
            l++;
        }
        dp[i] = value(q[l]) + sum[i];
    }
    cout<<dp[n];
    return 0;
}
