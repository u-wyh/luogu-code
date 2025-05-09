#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n;
int arr[MAXN];
int dp[MAXN][5];//��ʾ���ʳ�ﱻ��߳�  �ұ߳�  һ���  û�˳�  �Լ�ת�ƹ�����״̬
int ans[MAXN];

bool check(int x){
    for(int i=1;i<=n+1;i++){
        dp[i][1]=dp[i][2]=dp[i][3]=dp[i][4]=0;
    }
    dp[1][x]=1;
    for(int i=2;i<=n+1;i++){
        if(dp[i-1][1] && arr[i-1]<=arr[i]*2)
			dp[i][1]=1;
		if(dp[i-1][1] && arr[i-1]<=arr[i])
			dp[i][3]=1;

		if(dp[i-1][2] && arr[i]<=arr[i-1]*2)
			dp[i][2]=2;
		if(dp[i-1][2] && arr[i]<=arr[i-1])
			dp[i][4]=2;

		if(dp[i-1][3] && arr[i]<=arr[i-1])
			dp[i][2]=3;
		if(dp[i-1][3] && arr[i]*2<=arr[i-1])
			dp[i][4]=3;

		if(dp[i-1][4] && arr[i-1]<=arr[i])
			dp[i][1]=4;
		if(dp[i-1][4] && arr[i-1]*2<=arr[i])
			dp[i][3]=4;
    }
    return dp[n+1][x];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    arr[n+1]=arr[1];//�����ĳ���
    for(int i=1;i<=4;i++){
        //ö�ٵ�һ�������״̬
        if(check(i)){
            int m=i;
            for(int j=n+1;j>=1;j--){
                if(m==1){
                    //��������Ǳ���߳�
                    ans[j-1]=(j-1)%n+1;
                }
                else if(m==2){
                    //��������Ǳ��ұ߳�
                    ans[j]=(j-1)%n+1;
                }
                else if(m==3){
                    ans[j]=ans[j-1]=(j-1)%n+1;
                }
                m=dp[j][m];//ת��״̬
            }
            for(int i=1;i<=n;i++){
                cout<<ans[i]<<' ';
            }
            return 0;
        }
    }
    cout<<"NIE"<<endl;
    return 0;
}
