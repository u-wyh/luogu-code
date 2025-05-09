#include<cstdio>
#include<algorithm>
#include<cstring>
#define mod 1000000009
using namespace std;
int prime[1200],PRIME[1200],cnt,n,dp[10010][10][10],ans;
void getprime(){
	prime[1]=prime[0]=1;
	for(int i=2;i<=1010;i++){
		if(!prime[i]) PRIME[++cnt]=i;
		for(int j=1;j<=cnt && i*PRIME[j]<=1010;j++){
			prime[PRIME[j]*i]=1;
			if(!(i%PRIME[j])) {break;}
		}
	}
}
int get(int bai,int shi,int ge){
	return bai*100+shi*10+ge;
}
int main(){
	scanf("%d",&n);
	if(n<3) printf("0"),exit(0);
	getprime();
	for(int i=0;i<=9;i++) for(int j=0;j<=9;j++) dp[2][i][j]=1;
	for(int i=3;i<=n;i++)
		for(int now=1;now<=9;now++)
			for(int pre=0;pre<=9;pre++)
				for(int last=0;last<=9;last++)
					if(!prime[get(now,pre,last)])
						dp[i][now][pre]=(dp[i][now][pre]+dp[i-1][pre][last])%mod;
	for(int i=0;i<=9;i++)
		for(int j=0;j<=9;j++)
			ans=(ans+dp[n][i][j])%mod;
	printf("%d\n",ans);
	return 0;
}
