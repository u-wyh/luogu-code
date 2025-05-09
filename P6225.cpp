#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN=2e5+5;
int n,Q;
int a[MAXN];

class BIT
{
	private:
	int tree[MAXN];
	public:
	int lowbit(const int x)
	{
		return x&-x;
	}
	void modify(int pos,const int x)
	{
		for(;pos<=n;pos+=lowbit(pos))
		 tree[pos]^=x;//ά������
	}
	int query(int pos)
	{
		int res=0;
		for(;pos;pos-=lowbit(pos))
		 res^=tree[pos];//ͬ��
		return res;
	}
}tree[2];//tree[0]��ά���±�Ϊż����tree[1]��������

int main()
{
    ios_base::sync_with_stdio(false);
    cin>>n>>Q;
	for(int i=1;i<=n;i++)
	 cin>>a[i];
	for(int i=1;i<=n;i++)
	 tree[i&1].modify(i,a[i]);//����
	while(Q--)
	{
		int opt,x,y;cin>>opt>>x>>y;
		if(opt==1)
		{
			tree[x&1].modify(x,a[x]^y);//���͹���
			a[x]=y;
		}
		if(opt==2)
		{
			int ans=0;
			if(!((x&1)^(y&1)))//l,r��ż����ͬ
			 ans=tree[x&1].query(y)^tree[x&1].query(x-1);
			cout<<ans<<endl;
		}
	}
	return 0;
}
