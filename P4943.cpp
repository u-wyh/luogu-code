#include<bits/stdc++.h>
using namespace std;
int n,m,p,k=0,k1,u,v,w,x,y,lsg,b[1000000],vis[1000000];
int q[10000000],r,l,check=0,ans[1000000],c[1000000];
int zc[100];//���������ʱ�𰸡�
struct sb {
	int u,v,w,next;
};
sb a[1000000];
void ctt(int u,int v,int w) {
	a[++k].u=u;
	a[k].v=v;
	a[k].w=w;
	a[k].next=b[u];
	b[u]=k;
	return;
}
void SPFA() {
	for(int i=1; i<=n; i++)ans[i]=1e9;
	r=0;
	l=1;
	memset(c,0,sizeof(c));//j��Ϊ�ж��SPFA����Ҫ�ǵü�ʱ�����
	if(check!=2) {//������һ���ж�ʱ,��һ��ʼ��
		q[++r]=1;
		ans[1]=0;
	}
	else {//�������Լ��ж�ʱ��ֻҪ������ռǵ����ݡ�
		q[++r]=x;
		ans[x]=0;
	}
	while(l<=r) {
		int u=q[l++];
		c[u]=0;
		if(!check&&vis[u])continue;//�޶��޷�ͨ�����ߵķ��䡣
		for(int i=b[u]; i; i=a[i].next) {
			int v=a[i].v;
			if(ans[v]>ans[u]+a[i].w) {
				ans[v]=ans[u]+a[i].w;
				if(c[v]==0) {
					c[v]=1;
					q[++r]=v;
				}
			}
		}
	}
}
int main() {
	cin>>n>>m>>k1;
	for(int i=1; i<=k1; i++) {
		cin>>lsg;
		vis[lsg]=1;//���ߵķ�����ϱ�ǡ�
	}
	for(int i=1; i<=m; i++) {
		cin>>u>>v>>w;
		ctt(u,v,w);
		ctt(v,u,w);
	}
	cin>>x>>y;
	SPFA();//�ȴ��޶���ʼ������˼·��΢�����㣬��ʱcheck=0��
	zc[1]=ans[x];//�޶������ݵ�·�̡�
	zc[2]=ans[y];//�޶����ռǵ�·�̡�
	check++;
	SPFA();//��ʱ�������·�̣�check=1�������ж����߷�����ж���ʧЧ��
	zc[3]=ans[x];//���������ݵ�·�̡�
	zc[4]=ans[y];//�������ռǵ�·�̡�
	check++;
	SPFA();//���ռǵ����ݵ�·�̣���ʱcheck=2���Ϸ����ж���Ч��
	zc[5]=ans[y];//�ռǵ����ݵ�·�̡�
	int x2,y2,z2;//������ʱ��ŵ�
	x2=max(zc[1],zc[4]);//�����޶��Ƚ��ݣ��������ռǵ����ֵ����Ϊ��ʱʱ��Ӧ�������ɵ�ʱ�䣬���ǽ������������ɿ�����
	y2=max(zc[2],zc[3]);//��������Ƚ��ݣ��޶����ռǵ���Сֵ��
	z2=min(zc[3],zc[4])+zc[5];//��������Լ��ж�����Сֵ��ʹ��min��Ϊ��ʱһ���ж�������С��ʼ�����š�
	x2=min(x2,y2);//�Ƚ��޶��Ƚ��ݣ��������ռǺ͹����Ƚ��ݣ��޶����ռǵ���Сֵ��x2����Ϊ��ʱ����Сֵ��
	cout<<min(x2,z2);//����һ�αȽϵ���Сֵͬ�����Լ��ж���·�̱Ƚϣ���Сֵ�������մ𰸡�
	return 0;
}
