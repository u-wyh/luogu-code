// ��¥�Ӽ�������
// һ����kö��ͬ�ļ�����һ����n��¥
// ��֪һ������¥��f(0<=f<=n)����>f��¥���Ӽ���һ�����飬��<=f��¥���Ӽ������Ӽ��ζ�������
// ����һ�����˾Ͳ�����ʹ�ã�ֻ��ѡ������ļ���
// ������ȷ��f��ֵ�����������Ӽ��μ���������ȷ�������ֵ
// 1 <= k <= 100
// 1 <= n <= 10^4
// �������� : https://leetcode.cn/problems/super-egg-drop/
#include<bits/stdc++.h>
using namespace std;

int n,k;
int dp[10005][105];

int main()
{
    cin>>n>>k;
    if(k==1){
        cout<<n;
    }
    else{
        for (int j = 1; j <= n; j++) {
			for (int i = 1; i <= k; i++) {
				dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1] + 1;
				if (dp[i][j] >= n) {
					cout<<j;
					return 0;
				}
			}
		}
    }
    return 0;
}
