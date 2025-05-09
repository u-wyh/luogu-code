// �����ռ�����������
// ��һ��n * m�������к��еı�Ŵ�1��ʼ
// ÿ����������(i, j, v)��ʾ��i��j�����м�ֵΪv��������
// һ����k�������㣬��������������һ���ڲ�ͬ��λ��
// һ��ʼ�����ڵ�1�е�����λ�ã�Ȼ��ÿһ�����������ƶ�
// ����ȥ���ĸ�������һ����Χ�������ǰ��(i, j)λ��
// ��ô���¿���ѡ��(i+1, j-t)...(i+1, j+t)���е�һ������
// �������һ��ʱ���ռ�����ֹͣ���������ռ��������������ֵ
// 1 <= n��m��k��t <= 4000
// 1 <= v <= 100
// �������� : https://www.luogu.com.cn/problem/P3800
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ����������
#include<bits/stdc++.h>
using namespace std;

int n,m,k,t;
int dp[4005][4005];
int q[4005];
int l,r;

void add(int i, int j) {
	if (j <= m) {
		while (l < r && dp[i][q[r - 1]] <= dp[i][j]) {
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
    cin>>n>>m>>k>>t;
    for(int i=1;i<=k;i++){
        int u,v,w;
        cin>>u>>v>>w;
        dp[u][v]=w;
    }
    for (int i = 2; i <= n; i++) {
        l = r = 0;
        for (int j = 1; j <= t; j++) {
            add(i - 1, j);
        }
        for (int j = 1; j <= m; j++) {
            add(i - 1, j + t);
            overdue(j - t - 1);
            dp[i][j] += dp[i - 1][q[l]];
        }
    }
    int ans = INT_MIN;
    for (int j = 1; j <= m; j++) {
        ans = max(ans, dp[n][j]);
    }
    cout<<ans;
    return 0;
}
