// ������Ծ������÷�
// ��������Ϊn+1������arr���±���0 ~ n����������a��b
// һ��ʼ��0λ�ã�ÿ�ο���ѡ��[a,b]֮���һ����������Ϊ������Ծ�ľ���
// ÿ����һ��λ��i�����Ի��arr[i]��Ϊ�÷֣�λ��һ������n��ֹͣ
// �����ܻ�õ����÷�
// 1 <= n <= 2 * 10^5
// 1 <= a <= b <= n
// -1000 <= arr[i] <= +1000
// �������� : https://www.luogu.com.cn/problem/P1725
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ����������
#include<bits/stdc++.h>
using namespace std;

int NA = INT_MIN;
int n,a,b;
int l,r;
int q[200005];
int arr[200005];
int dp[200005];

void add(int j) {
    if (j >= 0 && dp[j] != NA) {
		while (l < r && dp[q[r - 1]] <= dp[j]) {
			r--;
		}
		q[r++] = j;
	}
}

void overdue(int t) {
	if (l < r && q[l] == t) {
		l++;
	}
}

int main()
{
    cin>>n>>a>>b;
    for(int i=0;i<=n;i++){
        cin>>arr[i];
    }
    dp[0] = arr[0];
    l = r = 0;
    for (int i = 1; i <= n; i++) {
        add(i - a);
        overdue(i - b - 1);
        dp[i] = l < r ? dp[q[l]] + arr[i] : NA;
    }
    int ans = NA;
    for (int i = n + 1 - b; i <= n; i++) {
        ans = max(ans, dp[i]);
    }
    cout<<ans;
    return 0;
}
