#include<bits/stdc++.h>
#define mod 1000000007//ģ��
using namespace std;
const int N=1e6+10;
int n,m;
long long dp[N][2];//�ǵÿ�long long
vector<int> vec[N];
void dfs(int cur,int fa){//��Ϊ������ߣ���Ҫ��¼���ĸ����Ա����ظ�
	for(int i=0;i<vec[cur].size();i++){
		int to=vec[cur][i];
		if(to==fa)//�жϸ���
			continue;
		dfs(to,cur);//����������ת�ƣ���Ȼdp[to][0/1]��û���������ת����Ч
		dp[cur][0]=(dp[cur][0]*(dp[to][0]+m*dp[to][1]%mod))%mod;
		dp[cur][1]=(dp[cur][1]*(dp[to][0]+(m-1)*dp[to][1]%mod))%mod;//״̬ת��
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		vec[u].push_back(v);
		vec[v].push_back(u);//�ǵô�˫���
	}
    for(int i=1;i<=n;i++)
        dp[i][0]=dp[i][1]=1;//��ʼ״̬
	dfs(1,0);//�Ӹ��������
	cout<<(dp[1][0]+m*dp[1][1]%mod)%mod;//��
	return 0;
}
