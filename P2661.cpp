//P2661
#include<cstdio>
#include<algorithm>//�õ�min
using namespace std;
const int MAXN=200010;
int a[MAXN],fa[MAXN],dis[MAXN];//�������
int ans=0x3f3f3f3f;//ǳ��1
int read(){//���������Ͳ���ע����
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int getfa(int u){//������
	if(fa[u]==u) return u;//�����ң�ֱ�ӷ���
	int tmp=fa[u];//��ӣ����ͼ���
	fa[u]=getfa(fa[u]);//ǳ��2
	dis[u]+=dis[tmp];
	return fa[u];//����
}
void unio(int u,int v){//�ϲ�
	int fu=getfa(u),fv=getfa(v);//��������
	if(fu==fv) ans=min(ans,dis[v]+1);//���´𰸣����ͼ���
	else fa[fu]=fv,dis[u]=dis[v]+1;//����fa��dis��ǳ��3
}
int main(){//������
	int n=read();
	for(int i=1;i<=n;i++) fa[i]=i;//ǳ��4
	for(int i=1;i<=n;i++){
		a[i]=read();
		unio(i,a[i]);//�ϲ���ǳ��5
	}
	printf("%d",ans);//���
	return 0;//��������
}
/*
�������ȣ�getfagetfa��������������Ҫ�������Ƚڵ㣬��Ҫ���¾��롣������һ���Ƚ�����ķ�����
�������������Ƚڵ���Ŀǰ�����Ƚڵ�����Ƚڵ㣬
��������㵽�������Ƚڵ�ľ����������Ŀǰ�����Ƚڵ�ľ������Ŀǰ�����Ƚڵ㵽�������Ƚڵ�ľ��롣���Ƚ��ƣ�

����һ���ϲ��ĺ�����unionunion������ֱ��ù��ˣ������������uniounio����
��������ڶ��е�ÿ����������Ҫ�뵱ʱ��ii��һ�κϲ����������ҵ���Ҫ�ϲ��������ڵ�����ȡ�

���������ͬ����ô���ֻ����˻��ĳ��Ⱦ���dis[v]+1dis[v]+1�����������⣬��ô�������ͼ��

�������ڴ���u=4,v=1u=4,v=1�ĺϲ������Եõ�fa[1]=4,dis[1]=3,fa[4]=4,dis[4]=0fa[1]=4,dis[1]=3,fa[4]=4,dis[4]=0��
���ѷ��֣�dis[u]��Զ��0�����Դ𰸾���dis[v]dis[v]����<4,1><4,1>�����ߵ�11��

������Ȳ���ͬ����ô�Ͱ��ղ��鼯�������������ټ���һ��dis[u]=dis[v]+1dis[u]=dis[v]+1�ͺ��ˡ�
*/
