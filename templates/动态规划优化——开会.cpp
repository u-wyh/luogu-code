// �μӻ���II
// ����n�����飬ÿ�������п�ʼʱ�䡢����ʱ�䡢��������ֵ
// �μӻ�����ܵõ����棬����ͬһʱ��ֻ�ܲμ�һ������
// һ���ܲμ�k�����飬���ѡ��μ�ĳ�����飬��ô���������Ĳμ����������
// ������������ǰ����ڻ����ڵģ�һ������Ľ���ʱ�������һ������Ŀ�ʼʱ�䣬�����������鶼�μ�
// �����ܵõ��Ļ����ֵ����
// 1 <= n * k <= 10^6
// 1 <= ��ʼʱ�䡢����ʱ�� <= 10^9
// 1 <= ���� <= 10^6
// �������� : https://leetcode.cn/problems/maximum-number-of-events-that-can-be-attended-ii/
#include<bits/stdc++.h>
using namespace std;

struct meeting{
    int st,en,val;
}nums[100005];
int n,k;

bool cmp(meeting a,meeting b){
    return a.en<b.en;
}

// 0...i��Χ�ϵĻ��飬���ݽ�������������
// �ҵ�����ʱ��<s�����ҵĻ�����
// ��������������Ļ��鷵��-1
int find(int i, int s) {
	int l = 0, r = i, mid;
	int ans = -1;
	while (l <= r) {
		mid = (l + r) / 2;
		if (nums[mid].en < s) {
			ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}

int main()
{
    cin>>n>>k;
    for(int i=0;i<n;i++){
        cin>>nums[i].st>>nums[i].en>>nums[i].val;
    }
    sort(nums,nums+n,cmp);
//    for(int i=0;i<n;i++){
//        cout<<nums[i].st<<' '<<nums[i].en<<' '<<nums[i].val<<endl;
//    }
    // dp[i][j] : 0..i��Χ�����ѡj�������ٿ�����������Ƕ���
    vector<vector<int>> dp(n,vector<int>(k + 1, 0));
    for (int j = 1; j <= k; j++) {
        dp[0][j] = nums[0].val;//���ѡj��  ����һ��Ҫѡj��
    }
    for (int i = 1, pre; i < n; i++) {
        pre = find(i - 1, nums[i].st);
        for (int j = 1; j <= k; j++) {
            dp[i][j] = max(dp[i - 1][j], (pre == -1 ? 0 : dp[pre][j - 1]) + nums[i].val);
        }
    }
    cout<<dp[n-1][k]<<endl;
    return 0;
}
