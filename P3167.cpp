#include <bits/stdc++.h>
using namespace std;
#define ULL unsigned long long
const int maxn = 1e5+10;
ULL h1[maxn],h2[maxn],p[maxn];

const ULL P = 131;
ULL get(int l, int r,ULL h[] )
{
	if( r<l )	return 0;
    return h[r] - h[l - 1] * p[r - l + 1];
}

int num,q,m,n,f[12][maxn],id[maxn];
char t[maxn],s[maxn];
int main()
{
    p[0] = 1;
    for(int i = 1; i <= 100000; i ++ )    p[i] = p[i - 1] * P;
    scanf("%s%d",t+1,&q);
    n = strlen( t+1 ); t[++n] = '?';
    for(int i=1;i<=n;i++)	if( t[i]=='*'||t[i]=='?' )	id[++num] = i;//ͨ����±�

    for(int i=1;i<=num;i++)
   	for(int j=id[i-1]+1;j<=id[i]-1;j++)
	   	h1[i] = h1[i]*P+t[j];//�ַ���hash
   	while( q-- )
   	{
		scanf("%s",s+1); m = strlen( s+1 ); s[++m] = 'k';
		memset( f,0,sizeof f );
		for(int i=1;i<=m;i++)	h2[i] = h2[i-1]*P+s[i];

		f[0][0] = 1;
		for(int i=0;i<num;i++)//ö��ƥ�䵽�ڼ���ͨ���
	   	for(int j=0;j<=m;j++)
	   	{
	   		if( f[i][j]==0 )	continue;//�޷�����ת��
	   		if( f[i][j]==2 )	f[i][j+1] = 2;//������ȥ,���涼�Ƿ��ϵ�
	   		int r = j+id[i+1]-id[i]-1;
	   		if( h1[i+1]!=get(j+1,r,h2) )	continue;//����ƥ������ͨ����м����ĸ
			if( t[id[i+1]]=='?' )	f[i+1][r+1] = 1;//'?'Ҳ����ƥ���,������r+1
			else		f[i+1][r] = 2;//'*'����Ϊ��,������r
		}
		if( f[num][m] )	printf("YES\n");
		else	printf("NO\n");
	}
}
