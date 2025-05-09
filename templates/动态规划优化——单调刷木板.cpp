// ��ˢľ����������
// һ����n��ľ�壬ÿ��ľ�峤��Ϊ1������ˢһ�Σ�Ҳ���Բ�ˢ
// һ����m�����ˣ�ÿ��������(li, pi, si)��ʾ��
// �ù��˱���ˢ���������ľ�壬���������ĳ��Ȳ�����li
// �ù���ÿˢһ��ľ����Եõ�pi��Ǯ
// �ù���ˢ����������������siλ�õ�ľ��
// �������й�������ܻ�ö���Ǯ
// 1 <= n <= 16000
// 1 <= m <= 100
// 1 <= pi <= 10000
// �������� : http://poj.org/problem?id=1821
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ����������
#include<bits/stdc++.h>
using namespace std;

int n,m;
struct worker{
    int l,s,p;
}nums[105];
int dp[16000][105];
int q[105];
int l, r;

bool cmp(worker a,worker b){
    return a.s<b.s;
}

// ֮ǰ���˸����������j��ľ���βʱ������ָ���ֵ
int value(int i, int pi, int j) {
	return dp[i - 1][j] - pi * j;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>nums[i].l>>nums[i].p>>nums[i].s;
    }
    sort(nums+1,nums+m+1,cmp);
    for (int i = 1, li, pi, si; i <= m; i++) {
        li = nums[i].l;
        pi = nums[i].p;
        si = nums[i].s;
        l = r = 0;
        for (int j = max(0, si - li); j < si; j++) {
            while (l < r && value(i, pi, q[r - 1]) <= value(i, pi, j)) {
                r--;
            }
            q[r++] = j;
        }
        for (int j = 1; j <= n; j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            if (j >= si) {
                if (l < r && q[l] == j - li - 1) {
                    l++;
                }
                if (l < r) {
                    dp[i][j] = max(dp[i][j], value(i, pi, q[l]) + pi * j);
                }
            }
        }
    }
    cout<<dp[m][n];
    return 0;
}
