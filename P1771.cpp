#include<bits/stdc++.h>
using namespace std;

int m,n;
int dp[105][1005];

int power(int a,int b,int mod){
    int ans=1;
    while(b>0){
        if(b&1){
            ans=(ans*a)%mod;
        }
        a=(a*a)%mod;//aÿ���൱�ڱ���  ֻ��b����һλ����1��ʱ�� �ŻὫa�˽�ans��
        b>>=1;//b�����ƶ�һλ
    }
    return ans;
}

int main()
{
    cin>>m>>n;
    n=power(n,n,1000);
    //cout<<' '<<n<<endl;
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        dp[1][i]=i;
    }
    for(int i=2;i<=m;i++){
        for(int j=i;j<=n;j++){
            dp[i][j]=dp[i-1][j-1]-dp[i-1][i-2];
            dp[i][j]+=dp[i][j-1];
        }
    }
    cout<<(dp[m][n]-dp[m][n-1]);
    return 0;
}
