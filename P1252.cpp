#include<bits/stdc++.h>
using namespace std;

int a[100][100],minn=INT_MAX,q[100],i,j,f[1000][100],qmin[100];//数组是我随手开的
void dfs(int x,int y,int s){//搜索内容 x代表还剩 x km,y代表前y人,s代表最少时间
	if (x<0)
	return;//这句话可能是多余的
	if (f[x][y]<=s)
	return;
	f[x][y]=s;//记忆化，f[x][y]表示还剩x公里，前y个人参加，能达到的最小的时间
	if (y>5){//如果所有人都跑了
		if (x==0)//如果跑完全程了
			if (minn>s){//如果时间比原来已记录的少
				minn=s;
				for (int i=1;i<=5;++i)
				qmin[i]=q[i];//记录
			}
		 return;
	}
	for (int i=1;i<=min(x,10);++i){//枚举当前这个人跑了i公里
	q[y]=i;//记录
	dfs(x-i,y+1,s+a[y][i])//;剩下路程-i,下一个人，时间加该人跑i公里所需要的时间
}
}
int main(){
	for (i=1;i<=5;++i)
	for (j=1;j<=10;++j)
	cin>>a[i][j];//输入
	for (i=0;i<=100;++i)
	for (j=0;j<=80;++j)
	f[i][j]=INT_MAX;//初始化，我也是随手写的
	dfs(25,1,0);//搜索
	cout<<minn<<endl;
	for (i=1;i<=4;++i)
	cout<<qmin[i]<<" ";cout<<qmin[5];//打印答案
}
