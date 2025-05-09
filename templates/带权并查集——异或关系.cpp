// ����ϵ
// һ��n���������0 ~ n-1��ʵ�������������͵Ĳ�����һ������m��
// I x v        : ���� ��x���� = v
// I x y v      : ���� ��x���� ^ ��y���� = v
// Q k a1 .. ak : ��ѯ һ��k���������Ϊa1 .. ak����Щ�������������ֵ�Ƕ���
// ��ÿ��Q�Ĳ�����ӡ�𰸣��������֮ǰ�������޷��Ƴ��𰸣���ӡ"I don't know."
// ���������s��������������ì�ܣ���ӡ"The first s facts are conflicting."
// ע��ֻ�������������֣�s�Ż����ӣ���ѯ������ռ�����������ļ���
// ����ì��֮�����еĲ��������ٴ��������ϸ�ڿ��Դ򿪲������Ӳ鿴��Ŀ
// 1 <= n <= 20000    1 <= m <= 40000    1 <= k <= 15
// �������� : https://acm.hdu.edu.cn/showproblem.php?pid=3234
// �������� : https://www.luogu.com.cn/problem/UVA12232
// �������� : https://vjudge.net/problem/UVA-12232
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<iostream>
using namespace std;
#define gc getchar
inline int read()
{
	int ret=0,f=0;char c=gc();
	while(!isdigit(c)){if(c=='-')f=1;c=gc();}
	while(isdigit(c)){ret=ret*10+c-48;c=gc();}
	if(f)return -ret;return ret;
}
const int N=20005;
int n,m,fa[N],val[N],vis[N];
struct query{
    char c;
    int a,b,v,k,x[20];
} q[N*2];
int find(int x)
{
    if(fa[x]==x)return x;
    int tmp=fa[x];
    fa[x]=find(fa[x]);
    val[x]^=val[tmp];
    return fa[x];
}
void init()//��һ�����õĵ�n����ֵȷ���ĵ�����n
{
    for(int i=0;i<=n;i++)
	{
		fa[i]=i;
		val[i]=0;
    }
    char Q[105];
    for(int i=0;i<m;i++)
	{
		scanf("%s",Q);
		q[i].c=Q[0];
		int a,b,v;
		if(Q[0]=='I')
		{
		    gets(Q);
		    if(sscanf(Q,"%d%d%d",&a,&b,&v)==2)
			{
				v=b;
				b=n;
		    }
		    q[i].a=a;q[i].b=b;q[i].v=v;
		}
		else{
		    scanf("%d",&q[i].k);
		    for(int j=0;j<q[i].k;j++)scanf("%d",&q[i].x[j]);
		}
    }
}
void solve()
{
    int fir=0;
    for(int i=0;i<m;i++)
	{
		if(q[i].c=='I')
		{
		    fir++;
		    int x=find(q[i].a);
		    int y=find(q[i].b);
		    if(x==n)swap(x,y);
		    if(x==y)
			{
				if((val[q[i].a]^val[q[i].b])!=q[i].v)
				{
				    printf("The first %d facts are conflicting.\n",fir);
				    return;
				}
		    }
		    else{
				fa[x]=y;
				val[x]=val[q[i].a]^val[q[i].b]^q[i].v;//��֪��x��yȷ�е�ֵ������Ҫ��������ʽ���x^y
		    }
		}
		else{
		    int ans=0;
		    for(int j=0;j<q[i].k;j++)
			{
				int x=find(q[i].x[j]);
				ans^=val[q[i].x[j]];
				if(x!=n)vis[x]^=1;//Ϊ1�ͱ�ʾ�������һ��fa��ֵ
			}
			int flag=1;
			for(int j=0;j<q[i].k;j++)
			{
				if(vis[fa[q[i].x[j]]])flag=0;
				vis[fa[q[i].x[j]]]=0;
		    }
		    if(flag)printf("%d\n",ans);
		    else printf("I don't know.\n");
		}
    }
}
int main()
{
    int cas=0;
    while(scanf("%d%d",&n,&m)!=EOF)
	{
		if(n==0&&m==0)return 0;
		init();
		printf("Case %d:\n",++cas);
		solve();
		puts("");
    }
    return 0;
}
