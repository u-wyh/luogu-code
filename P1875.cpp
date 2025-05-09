#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
#define ll long long
#define db double
using namespace std;
inline int read()
{
	char ch=getchar();
	int a=0,x=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') x=-x;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		a=(a<<1)+(a<<3)+(ch^48);
		ch=getchar();
	}
	return a*x;
}
const int N=1005;
int n,Edge;
int cost[N],vis[N],f[N][N];
ll cnt[N];
void Dijkstra()
{
	for(int i=1;i<n;i++)                    //����n-1���ɳڲ���
	{
		int Min=1e9,u;
		//ÿ��һ�������ҵ�һ��Ŀǰ��ͼ۸��  ��һ���޷����Ż���
		for(int j=1;j<=n;j++)               //ȡһ���ó���С���ѵ�ҩˮ�����±��ҩˮ
		{
			if(!vis[j]&&cost[j]<Min)        //ֻȡû���й��ɳڲ�����j,�������ʱ���˷�
			{
				u=j;Min=cost[j];
			}
		}
		vis[u]=1;                           //��¼һ��u���Ѿ��ɳڹ����ĳ����յ���
		for(int v=1;v<=n;v++)
		{
			if(vis[v]&&f[u][v])             //�������Ѿ��ó���С���ѵ�ҩˮ(�ɳڹ����������ҩˮ)
			{
				int w=f[u][v];              //�������ܺϳɵ�ҩˮ
				if(cost[w]==cost[u]+cost[v])//���ͨ��u��v�ϳɵĻ��Ѻ�ԭ��һ��
				{
					cnt[w]+=cnt[u]*cnt[v];  //�����ֶ���cnt[u]*cnt[v]��
				}
				else if(cost[w]>cost[u]+cost[v]) //������Ѹ���
				{
					cost[w]=cost[u]+cost[v];//�ɳڳɹ�
					cnt[w]=cnt[u]*cnt[v];   //���¼�¼������
				}
			}
		}
	}
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++) cost[i]=read();   //ÿ��ҩˮ���̵깺��ĳ�ʼ����
	for(int i=1;i<=n;i++) cnt[i]=1ll;       //��¼��С���ѷ�����,��ʼ��Ϊ1,��ʾ���̵깺��
	int u,v,w;
	while(cin>>u>>v>>w)
	{
		u++;v++;w++;                        //���+1
		f[u][v]=f[v][u]=w;                  //��ʾ u+v->w
	}
	Dijkstra();
	printf("%d %lld\n",cost[1],cnt[1]);     //�����С���Ѻͷ�����
	return 0;
}
