#include<bits/stdc++.h>
using namespace std;

long long n,m,nm,k,as,x,h[200010],s[200010],ans=0,c,ss[500010];

int main()
{
	cin>>n>>m>>nm>>k;
	ss[0]=n;
	for(int i=1;i<=nm;i++)
	{
		cin>>as>>x;
		if(as==1) {
			h[x]++;
			ss[h[x]-1]--;//Ϳ��h[x]-1�ε�������1
			ss[h[x]]++;//Ϳ��h[x]�ε�������1
		}
		else
            s[x]++;
	}
	sort(h+1,h+n+1);//��С��������
	ans=n*m;//�𰸳�ʼ��
	for(int i=1;i<=m;i++){
		c=s[i]%k;
		for(int j=(k-c)%k;j<=h[n];j+=k){
			ans=ans-ss[j];
		}
	}
	cout<<ans;

	return 0;
}
