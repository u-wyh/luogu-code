#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN(1e5+10);
int n,m,k,a[MAXN],b[MAXN],G[MAXN],sol[MAXN];
char s1[MAXN],s2[MAXN];
inline int Min(int x,int y){return x<y?x:y;}
inline bool check()
{
	if((n==1&&a[1]==0)||(m==1&&b[1]==0)) return false;
	return true;
}
inline void print(int*x,int len)
{
	for(register int i=len;i>=1;--i) putchar(x[i]^48);
	return;
}
inline void mul2(int*x,int&len)
{
	bool flag(false);
	for(register int i=1;i<=len;++i)
	{
		x[i]<<=1;
		if(flag) x[i]|=1;
		if(x[i]>=10) x[i]-=10,flag=true;
		else flag=false;
	}
	if(flag)
	{
		++len;
		x[len]=1;
	}
	return;
}
inline void div2(int*x,int&len)
{
	int num(0);
	int ans[MAXN];
	for(register int i=len;i>=1;--i)
	{
		if(x[i]&1)
		{
			int now=((num*10+x[i])>>1)<<1;
			ans[i]=(num*10+x[i])>>1;
			num=(num*10+x[i])-now;
		}
		else
		{
			ans[i]=(num*10+x[i])>>1;
			num=0;
		}
	}
	for(register int i=len;i>=1;--i)
		if(ans[i]==0) --len;
		else break;
	if(len==0) ++len;
	for(register int i=1;i<=len;++i)
		x[i]=ans[i];
	return;
}
inline bool cmp()
{
	if(n<m) return false;
	if(n>m) return true;
	for(register int i=n;i>=1;--i)
		if(a[i]<b[i]) return false;
		else if(a[i]>b[i]) return true;
	return true;
}
inline void solve(int*x,int&l1,int*y,int l2)
{
	for(register int i=1;i<=l2;++i)
	{
		x[i]-=y[i];
		if(x[i]<0) --x[i+1],x[i]+=10;
	}
	if(l1==1) return;
	while(l1>0&&x[l1]==0) --l1;
	if(l1==0) l1=1;
	return;
}
inline void change(int*x,int&l1,int*y,int l2)
{
	l1=l2;
	for(register int i=1;i<=l1;++i) x[i]=y[i];
	return;
}
int len,cnt;
int main()
{
	scanf("%s%s",s1+1,s2+1);
	n=strlen(s1+1),m=strlen(s2+1);
	G[++k]=1;
	for(register int i=1,j=n;i<=n;++i,--j) a[j]=s1[i]-'0';
	for(register int i=1,j=m;i<=m;++i,--j) b[j]=s2[i]-'0';
	while(check())
	{
		if(a[1]%2==0&&b[1]%2==0) div2(a,n),div2(b,m),++cnt;
		else if(a[1]%2==0&&(b[1]&1)) div2(a,n);
		else if((a[1]&1)&&b[1]%2==0) div2(b,m);
		else
		{
			if(!cmp()) solve(b,m,a,n);
			else solve(a,n,b,m);
		}
	}
	if(cmp()) change(sol,len,a,n);
	else change(sol,len,b,m);
	for(register int i=1;i<=cnt;i++) mul2(sol,len);
	print(sol,len);
	return 0; 
}
