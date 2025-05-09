//P3167
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int BASE = 499;

long long h1[MAXN],h2[MAXN],p[MAXN];
int num=0,q,n,m,f[12][MAXN],id[MAXN];
char t[MAXN],s[MAXN];

long long get(int l, int r,long long *h ){
	if( r<l )
        return 0;
    return h[r] - h[l - 1] * p[r - l + 1];
}

int main()
{
    scanf("%s%d",t+1,&q);
    p[0]=1;
    for(int i=1;i<=MAXN;i++){
        p[i]=p[i-1]*BASE;
    }
    n = strlen( t+1 );
    t[++n] = '?';
    for(int i=1;i<=n;i++){
        if( t[i]=='*'||t[i]=='?' ){
            id[++num] = i;//ͨ����±�
        }
    }
    for(int i=1;i<=num;i++){
        for(int j=id[i-1]+1;j<=id[i]-1;j++){
            h1[i] = h1[i]*BASE+t[j];//�ַ���hash
            //��ʾ���Ǵ����ͨ�������һ��ͨ���֮��Ĺ�ϣ��ֵ
        }
    }
    while( q-- ){
		scanf("%s",s+1);
		m = strlen( s+1 );
		s[++m] = 'k';//���ڶ�Ӧ��������ӵ�'?'
		memset( f,0,sizeof f );
		for(int i=1;i<=m;i++)
            h2[i] = h2[i-1]*BASE+s[i];
		f[0][0] = 1;
		for(int i=0;i<num;i++){
            //ö��ƥ�䵽�ڼ���ͨ���
            for(int j=0;j<=m;j++){
                if( f[i][j]==0 )
                    continue;//�޷�����ת��
                if( f[i][j]==2 )
                    f[i][j+1] = 2;//������ȥ,���涼�Ƿ��ϵ�
                int r = j+id[i+1]-id[i]-1;

                if( h1[i+1]!=get(j+1,r,h2) )
                    continue;//����ƥ������ͨ����м����ĸ

                if( t[id[i+1]]=='?' )
                    f[i+1][r+1] = 1;//'?'Ҳ����ƥ���,������r+1
                else
                    f[i+1][r] = 2;//'*'����Ϊ��,������r
            }
		}
		if( f[num][m] )
            printf("YES\n");
		else
            printf("NO\n");
	}
    return 0;
}
