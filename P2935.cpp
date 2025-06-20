#include<iostream>
#include<cstdio>
#define X 200+10
using namespace std;
int fa[X];
bool vis[X][X];              //用来标记白点
int main()
{
	int n,t,ans=0;
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>t;
		while(t!=0){
			vis[i][t]=1;
			cin>>t;
		}
	}
	for(int i=1;i<=n;++i)
        fa[i]=i;                 //并查集，让自己是自己爸爸
	for(int k=1;k<=n;++k)
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                if(vis[i][j]||(vis[i][k]&&vis[k][j]))
                    vis[i][j]=1;              //标记白点
	for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            if(vis[i][j]==1)
                fa[j]=fa[i];
	for(int i=1;i<=n;++i)
        if(fa[i]==i)
            ans++;                     //累加光盘数
	printf("%d",ans);
	return 0;                  //大功告成，程序拜拜！
}
