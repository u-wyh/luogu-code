#include<bits/stdc++.h>
using namespace std;
int a[200001]={0};
int fa[200001]={0};  // father ����
int dfs(int x,int y){     //������
	if(x == 0) return -1;
	if(__gcd(a[x],a[y]) > 1) return x;  //͵һ����~ֱ��ʹ��gcd������
	return dfs(fa[x],y);
}
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n-1;i++){
		int x,y;
		cin>>x>>y;
		fa[y]=x;  //����
	}
	for(int i=1;i<=k;i++){
		int x,y;
		cin>>x;
		if(x==1){
			cin>>y;
			cout<<dfs(fa[y],y)<<endl;  //����
		}
		else{
			cin>>x>>y;
			a[x]=y;
		}
	}
	return 0;
}
