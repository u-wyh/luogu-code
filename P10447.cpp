#include<bits/stdc++.h>
using namespace std;
const int MAXN=25,MAXM=(1<<20),inf=0x3f;//���������infΪ����

int n,a[MAXN][MAXN],f[MAXM][MAXN];
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			scanf("%d",&a[i][j]);
	memset(f,inf,sizeof(f));
	f[1][0]=0;//��û��ʼ�ọ́�Ϊ0
	for(int i=1;i<(1<<n);i++)//ö��״̬
	{
		for(int j=0;j<n;j++)//ö��ÿ����
		{
			if(!((i>>j)&1)) continue;//������
			for(int k=0;k<n;k++)//��һ�ξ�������Щ�㣿
				if(((i^(1<<j))>>k)&1)//ö�ٴ���һ�������Ľڵ��ߵ�j�ڵ�
					f[i][j]=min(f[i][j],f[i^(1<<j)][k]+a[k][j]);//״̬ת��
		}
	}
	printf("%d\n",f[(1<<n)-1][n-1]);//out
	return 0;
    //�������
}
