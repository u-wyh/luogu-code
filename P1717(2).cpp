#include<bits/stdc++.h>
using namespace std;
int m,n,sum,t[1000],ans=-1,bj,b[1000],t1;
struct s
{
	int f,d,ti;
}a[1000];

void init()
{

	sum=0;
	for(int i=1;i<=n;i++)
	b[i]=a[i].f;//�����޸ĵ�ǰ������
}
int find(int j)//�����ҵ�ǰ����ֵ
{
	int c=-1,bj;
	for(int i=j;i>=1;i--)
	if(c<b[i]) c=b[i],bj=i;//�������ֵ
	return bj;
}

int main()
{
	scanf("%d%d",&n,&m);
	m=m*60; //Сʱת����
	for(int i=1;i<=n;i++) scanf("%d",&a[i].f);
	for(int i=1;i<=n;i++) scanf("%d",&a[i].d);
	for(int i=1;i<=n-1;i++) scanf("%d",&a[i].ti);
	for(int i=1;i<=n;i++)
	t[i]=t[i-1]+a[i-1].ti*5;//�����ߵ����յ�����ʱ��
	for(int i=1;i<=n;i++)   //^��ʱ���ų�·�̵�ʱ��Ӱ��
	{
        t1=t[i];
		init();     //��ֵ
		int j=i;
		while(1)    //ö���յ�
		{
			bj=find(j);   //�ҵ���ǰf���ֵ
			if(b[bj]<=0) break;//���û��
			sum=sum+b[bj];
			b[bj]-=a[bj].d;
			t1+=5;        //ʱ�����
			if(t1+5>m) break;//ʱ��������
		}
		ans=max(ans,sum);
	}
	printf("%d",ans);
}
