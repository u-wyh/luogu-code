#include<bits/stdc++.h>
using namespace std;
const int maxn=100100;
int n;
int l[maxn],r[maxn];
struct node{
	int x,y;
	bool operator<(node u)const{
		return y==u.y?x<u.x:y<u.y;
	}//��ǰ��������򣬵���y������ͬʱx������ĳɴ�С����
}moo[maxn];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&moo[i].x,&moo[i].y);
	}
	stable_sort(moo+1,moo+1+n);
	l[1]=moo[1].x;
	for(int i=2;i<=n;i++){
		l[i]=min(l[i-1],moo[i].x);
	}//����l
	r[n]=moo[n].x;
	for(int i=n-1;i>=1;i--){
		r[i]=max(r[i+1],moo[i].x);
	}//����r
	int ans=1;//����ans�ĳ�ʼֵ��Ҫ��Ϊ1
	for(int i=1;i<n;i++){
		if(l[i]>r[i+1]){
			ans++;
		}
	}
	printf("%d",ans);
	return 0;
}
