#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10,M=1e5+10;

int n,C[N*2],c[N*2],top,kind[M],k[M],cnt;
//kind����һ�಻��ʽ��	k������ʽ�Ϸ���Ҫ�� k (k=(c-b)/a)��
//C/c�����಻��ʽ��k < x | k > x��
//cnt�����������ʽ������
bool used[M];//��¼�������ʽ�Ƿ�ɾ��
char s[20];

void modify(int x,int y,int t[])//��Ҫ����Ϊʲô��������֣��ʾ���lxl
{
	x+=N;//������
	for(;x<=2e6+10;x+=x&(-x))//lowbit(x)=x&(-x)
		t[x]+=y;
	return ;
}

int sum(int x,int t[])
{
	x+=N;
	int res=0;
	for(;x;x-=x&(-x))
		res+=t[x];
	return res;
}

int main()
{
// 	freopen("work.in","r",stdin); freopen("work.out","w",stdout);
	scanf("%d",&n);
	int x,y,z;
	while(n--)
	{
		while(1)
		{
			scanf("%s",s);//�������
			if(s[0] == 'A' || s[0] == 'Q' || s[0] == 'D')
				break ;
		}
		if(s[0] == 'A')
		{
			scanf("%d%d%d",&x,&y,&z);
			if(!x)//x=0 ����ʽת��Ϊ b > c
			{
				if(y > z)
				{
					cnt++;
					kind[++top]=3;//��ʾ�����
				}
				else kind[++top]=0;//�㲻����
			}
			if(x > 0)//x > (c-b)/a
			{
				k[++top]=floor((z*1.0-y)/x);//��ȡ��
				kind[top]=1;//��ʾ�Ϸ��� k < x
				//k < x ��k�Ѿ�����
				if(k[top] > 1e6) kind[top]=0;//��ʾ�㲻����
				else if(k[top] < -1e6)//k < x ��k�Ѿ�����
				{
					cnt++;//�����
					kind[top]=3;
				}
				else modify(k[top],1,C);
			}
			if(x < 0)//ͬ��������������
			{
				k[++top]=ceil((z*1.0-y)/x);
				kind[top]=2;
				if(k[top] < -1e6) kind[top]=0;
				else if(k[top] > 1e6)
				{
					cnt++;
					kind[top]=3;
				}
				else modify(k[top],1,c);
			}
		}
		if(s[0] == 'Q')
		{
			scanf("%d",&x);
			printf("%d\n",sum(x-1,C)+(sum(1e6,c)-sum(x,c))+cnt);
			//�Ϸ���(k < x) + �Ϸ���(k > x) + �����
		}
		if(s[0] == 'D')//Delete
		{
			scanf("%d",&x);
			if(used[x]) continue ;
			used[x]=true;
			if(kind[x] == 3) cnt--;
			if(kind[x] == 1) modify(k[x],-1,C);
			if(kind[x] == 2) modify(k[x],-1,c);
		}
	}
	return 0;
}
