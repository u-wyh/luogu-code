#include <cstdio>
#include <cstring>
#include <cmath>
#define min(a,b) (((a)<(b))?(a):(b))
double a[20][20];//Ԥ�����ӵ�i�鵽��j��ľ��룬ʹ������֮����빫ʽ
double x[20],y[20];//ÿ�����ҵĺᡢ������
double F[18][34000];//״ѹDP���� �ڵ�i�����ϣ��߹��Ķ�����״̬��ʮ���Ʊ��Ϊjʱ����̵ľ���
int N;
double distance(int v,int w)//�����v���͵�w������֮��ľ���
{
	return sqrt((x[v]-x[w])*(x[v]-x[w])+(y[v]-y[w])*(y[v]-y[w]));//�������빫ʽ
}
int main()
{
	int i,j,k;
	double ans;
	memset(F,127,sizeof(F));//�������Ը���������ֵ�����
	ans=F[0][0];
	scanf("%d",&N);
	for(i=1;i<=N;i++)
	{
		scanf("%lf%lf",&x[i],&y[i]);//���ݶ���
	}
	x[0]=0;y[0]=0;
	for(i=0;i<=N;i++)
	{
		for(j=i+1;j<=N;j++)
		{
			a[i][j]=distance(i,j);//��ʼ����������
			a[j][i]=a[i][j];
		}
	}
	for(i=1;i<=N;i++)//��ʼ��
	{
		F[i][(1<<(i-1))]=a[0][i];//��i������ֻ�о���i��ʱ������ԭ�㵽i��ľ���
	}
	for(k=1;k<(1<<N);k++)//ö�����ж����Ƶ�״̬
	{
		for(i=1;i<=N;i++)
		{
			if((k&(1<<(i-1)))==0)
				continue;//i��λ��û���߹������Բ���Ҫ�ټ���������
			for(j=1;j<=N;j++)
			{
				if(i==j)
					continue;//ͬһ���㲻��Ҫ�ټ���
				if((k&(1<<(j-1)))==0)
					continue;//j��λ��û�߹�
				F[i][k]=min(F[i][k],F[j][k-(1<<(i-1))]+a[i][j]);
			}
		}
	}
	for(i=1;i<=N;i++)
	{
		ans=min(ans,F[i][(1<<N)-1]);
	}
	printf("%.2f\n",ans);
}
