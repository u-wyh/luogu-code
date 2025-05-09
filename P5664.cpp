#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 2005;
const int MOD = 998244353;

int n,m;
int arr[MAXN][MAXM];
int sum[MAXN][MAXM];
long long f[MAXN][MAXN<<1];
long long g[MAXN][MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            arr[i][j]=read();
            sum[i][0]=(sum[i][0]+arr[i][j])%MOD;//sum[i][0]�������е�����ֵ�ܺ�
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            sum[i][j]=(sum[i][0]-arr[i][j]+MOD)%MOD;
        }
    }
    //�Ϸ��ķ�����=�ܷ�����-���Ϸ��ķ�����
    long long ans=0;//������ڼ�¼���в��Ϸ��ķ�����
    for(int col=1;col<=m;col++){
        //ö��ÿһ�����Ϸ�����
        for(int i=1;i<=n;i++){
            for(int j=0;j<=2*n;j++){
                f[i][j]=0;//��ʼ��  f[i][j]���ձ�ʾ����  ǰi���� ѡ���Ĳ��Ϸ����б������ж�(j-n)�ķ�����
                //�������n��Ϊ��ʹ����������Ϊ����
            }
        }
        f[0][n] = 1;
        for(int i = 1; i<=n; i++){
            for(int j = n-i; j<=n+i; j++) {
                f[i][j] = (f[i-1][j]+f[i-1][j-1]*arr[i][col]%MOD+f[i-1][j+1]*sum[i][col]%MOD)%MOD;
            }
        }
        for(int j = 1; j<=n; j++){
            ans = (ans+f[n][n+j])%MOD;//���㲻�Ϸ��ķ�����
        }
    }
    g[0][0] = 1;
	for(int i = 1; i<=n; i++){
	    for(int j = 0; j<=i; j++){
		    g[i][j] = (g[i-1][j]+(j>0?g[i-1][j-1]*sum[i][0]%MOD:0))%MOD;//�����ܷ�����
            //g[i][j]��ʾ��ǰi��ѡj���ܷ�����  ����ÿһ�����ֻ����ѡһ��
        }
    }
    for(int j = 1; j<=n; j++){
	    ans = (ans-g[n][j]+MOD)%MOD; 
    } 
	cout << ans*(MOD-1)%MOD << endl;//�൱�ڳ�-1
    return 0;
}