#include<bits/stdc++.h>
#define maxn 100010
using namespace std;

int n,a[maxn],tree[maxn],ans[maxn];

int lowbit(int x){
    return x&(-x);
}

void add(int x,int k){
	for(int i=x;i<=n;i+=lowbit(i))
        tree[i]+=k;
}

int query(int x){
	int ret=0;
	for(int i=x;i;i-=lowbit(i))
        ret+=tree[i];
	return ret;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
	int k=0,sum=n;
	while(a[n-k]>a[n-k-1]){
		add(a[n-k],1);//加入有序序列
		sum--;
		k++;
	}
	add(a[n-k],1),sum--;//无论如何，都要把后缀的第一个元素加入，a[n-k]<a[n-k-1]，a[n-k]才是不降后缀的第一个元素
	for(int i=1;i<=sum;i++){
		add(a[i],1);
		ans[i]=sum-i+query(a[i]-1);//求有序序列前缀和
	}
	printf("%d\n",sum);
	for(int i=1;i<=sum;i++){
		printf("%d ",ans[i]);
	}
	return 0;
}
