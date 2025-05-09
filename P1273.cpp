#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int n,m;
int head[3010],k;
int val[3010];//�û�Ϊ�ۿ�������׼��֧����Ǯ��
int dp[3010][3010];//dp[i][j]��ʾi�ڵ㣬ѡj���û����ܵõ���Ǯ�����ֵ
struct node{
	int to,next,w;
}edge[6010];

void adde(int u,int v,int w)
{
	edge[++k].to=v; edge[k].next=head[u];
	edge[k].w=w; head[u]=k;
}
int dfs(int u)
{
	if(u>n-m)//uΪ�û��ն�
	{
		dp[u][1]=val[u];
		return 1;
	}
	int sum=0,t;
	for(int k=head[u];k;k=edge[k].next)//�õ������˼����ڵ���Ϊ�м��飬����ÿһ��
	{
		int v=edge[k].to;
		t=dfs(v);
		sum+=t; //tΪ�����Ԫ�ظ���������˵�������Ϊ����������С������Ĵ�Сָ�������û��ĸ�������sumΪ�ýڵ�������ѡ���ٸ��û�������������
		for(int j=sum;j>0;j--)
		{
			for(int i=1;i<=t;i++)//�������е�Ԫ�أ�ѡ���ٸ��û��൱��һ��Ԫ��
			{
				if(j-i>=0) dp[u][j]=max(dp[u][j],dp[u][j-i]+dp[v][i]-edge[k].w);
			}
		}
	}
	return sum;
}
int main()
{
	memset(dp,~0x3f,sizeof(dp));//��ʼ��һ������ֵ����Ϊdp����Ϊ��
	scanf("%d%d",&n,&m);
	for(int u=1;u<=n-m;u++)
	{
		int size,v,w;
		scanf("%d",&size);
		for(int j=1;j<=size;j++)
		{
			scanf("%d%d",&v,&w);
			adde(u,v,w);
		}
	}
	for(int i=n-m+1;i<=n;i++) scanf("%d",&val[i]);
	for (int i=1;i<=n;i++) dp[i][0]=0;//ѡ0���û��Ļ��ѿ϶���0��
	dfs(1);
	for (int i=m;i>=1;i--)
        if (dp[1][i]>=0)
		{
            printf("%d",i);
            break;
        }
	return 0;
}
