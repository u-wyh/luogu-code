#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;

int n,m;
int arr[MAXN];
int sum[MAXN];
int f[MAXN][MAXN][2];//��ʾ����Щ��i��j�ĵƱ��رյ�ʱ��λ��i��0��������λ��j��1��  ���ķ���С�ĵ���

int main()
{
    cin>>n>>m;
    int v;
    for(int i=1;i<=n;i++){
        cin>>arr[i]>>v;
        sum[i]=sum[i-1]+v;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            f[i][j][0]=f[i][j][1]=1e9;
        }
    }
    f[m][m][0]=f[m][m][1]=0;
    for(int len=2;len<=n;len++){
        for(int l=1;l+len-1<=n;l++){
            int r=l+len-1;
            f[l][r][0]=min(f[l+1][r][0]+(arr[l+1]-arr[l])*(sum[l]+sum[n]-sum[r]),f[l+1][r][1]+(arr[r]-arr[l])*(sum[l]+sum[n]-sum[r]));
            f[l][r][1]=min(f[l][r-1][0]+(arr[r]-arr[l])*(sum[l-1]+sum[n]-sum[r-1]),f[l][r-1][1]+(arr[r]-arr[r-1])*(sum[l-1]+sum[n]-sum[r-1]));
        }
    }cout<<min(f[1][n][0],f[1][n][1])<<endl;
    return 0;
}
