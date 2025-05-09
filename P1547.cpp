#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

int fa[200004];
int n,m,l,r,tot,ans,k;//tot�Ǻϲ�����  ���n-1

inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}

struct node{
	int fir;//��һ����
	int sec;//�ڶ�����
	int data;//��Ȩ
}edge[400005];

inline int find(int x){
	if(x==fa[x])return x;
	else return fa[x]=find(fa[x]);
}

inline bool cmp(node a,node b){
	return a.data<b.data;
}

inline void kruskal(){
	for(register int i=1;i<=m;i++){
		l=find(edge[i].fir);
		r=find(edge[i].sec);
		if(l==r)continue ;//�����ͨ������
		fa[l]=r;//����ͺϲ�
		k=edge[i].data;
		tot++;
		if(tot==n-1)break;
	}
}

int main(){
	n=read();
	m=read();
	for(register int i=1;i<=n;i++)
        fa[i]=i;//��ʼ�����鼯
	for(register int i=1;i<=m;i++){
		edge[i].fir=read();
		edge[i].sec=read();
		edge[i].data=read();
	}
	sort(edge+1,edge+m+1,cmp);//����Ȩ����ÿ�μ�С��
	kruskal();
	cout<<k;//��ϲ��cout...

	return 0;
}
