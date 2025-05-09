#include<bits/stdc++.h>
using namespace std;
const int N=100005;

int n,a[N],c[N];
long long ans;

void swap(int& x,int& y){
    x^=y;y^=x;x^=y;
}//��������Ԫ��

void reverse(int l,int r){//��ת����[l,r]�ڵ�Ԫ��
	for(int i=l;i<=r&&(i<<1)<l+r;++i)
        swap(a[i],a[r+l-i]);
	++ans;//˳��ͳ�ƴ�
}

int lowbit(int x){
    return x&-x;
}//���������Ǿ������״����

void update(int i,int v){
    for(;i<=n;i+=lowbit(i))
        c[i]+=v;
}

int getsum(int i){
    int ans=0;
    for(;i;i-=lowbit(i))
        ans+=c[i];
    return ans;
}

int main()
{
	scanf("%d",&n);
	int las=1;scanf("%d",&a[1]);//�Ƚ����а�Ҫ��תһ��
	for(int i=2;i<=n;++i){
		scanf("%d",&a[i]);
		if(a[i]>a[i-1]){
			reverse(las,i-1);
			las=i;
		}
	}
	reverse(las,n);
	for(int i=n;i>=1;--i){//Ȼ��ֱ����״�������������ȷ�ԾͿ��Ա�֤��
		ans+=getsum(a[i]);
		update(a[i],1);
	}
	printf("%lld\n",ans);
	return 0;
}
