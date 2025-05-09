#include<bits/stdc++.h>
using namespace std;

long long sum[400005];
long long mod;

void update(int now){
	sum[now]=(sum[now<<1]*sum[now<<1|1])%mod;//ʱ��mod
}
void build(int i,int l,int r)
{
	if(l==r)
	{
		sum[i]=1;//������1
		return ;
	}
	int mid=(l+r)>>1;
	build(i<<1,l,mid);
	build(i<<1|1,mid+1,r);
	update(now);
}
void change(int now,int l,int r,int lgo,int rgo,int nm)//�׵������޸�ģ��
{
	if(l>=lgo&&r<=rgo)
	{
		sum[now]=nm;
		return ;
	}
	int mid=(l+r)>>1;
	if(lgo<=mid)
	change(now<<1,l,mid,lgo,rgo,nm);
	if(rgo>mid)
	change(now<<1|1,mid+1,r,lgo,rgo,nm);
	update(now);
}
int main()
{
	int t;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		int q,op,m;
		cin>>q>>mod;
		build(1,1,q);
		for(int i=1;i<=q;i++)
		{
			cin>>op>>m;
			if(op==1)
			{
				change(1,1,q,i,i,m);//���Խ�i��ɢ��
				sum[1]%=mod;
			}
			else
			change(1,1,q,m,m,1);

			cout<<sum[1]%mod<<endl;//�������
		}
	}
    return 0;
}
