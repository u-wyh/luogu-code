#include <bits/stdc++.h>
using namespace std;
const int M = 1e4+5;

int n,m,dp[M],ans;
struct node{
	int t,x,y;
}a[M];//��λ�ýṹ��

int main()
{
	cin >> n >> m;
	for ( int i = 1;i <= m; i++ )
	{
		dp[i] = 1;//��ʼ������λ�ö��ܴﵽ���Լ�
		scanf ("%d%d%d",&a[i].t,&a[i].x,&a[i].y);
	}
	for ( int i = m; i > 1; i-- )
	    for ( int j = i-1; j >= 1; j-- )
	    {
	    	if (a[i].t-a[j].t>=abs(a[i].x-a[j].x)+abs(a[i].y-a[j].y))
	    	{
	    		dp[j] = max(dp[i]+1,dp[j]);
	    		//���ڹ涨ʱ����i�ܴﵽj��dp����
			}
		}
	for ( int i = 1; i <= m; i++ )
	{
	    ans = max(dp[i],ans);
	    //���ȡ���ֵ���ﵽ�����
	}
	printf ("%d",ans);//���
	return 0;
}
