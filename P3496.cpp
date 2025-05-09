#include<cstdio>
using namespace std;
const int MAXN=200010,MAXM=1000010;//ע�����Ҫ��2

int h[MAXN],color[MAXN],tot=0;//hΪ�ڽӱ��е�head��totΪ�ܱ���
bool vis[MAXN];//��¼�Ƿ�������
struct Edge{//�ߵĽṹ��
	int v;
	int next;//next��¼���������ڽӱ���ָ��ͬ�˵����һ����
}e[MAXM];

void addEdge(int u,int v){//����
	tot++;
	e[tot].v=v;
	e[tot].next=h[u],h[u]=tot;
}

void dfs(int u){//���ѣ�uΪԭ�ڵ㣬��֤��Ⱦɫ
	for(int k=h[u];k;k=e[k].next){//�ڽӱ����
		int v=e[k].v;
		color[v]=color[u]%2+1;//��ʽ
	}
}

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	while(m--){
		int uu,vv;
		scanf("%d%d",&uu,&vv);
		vis[uu]=1,vis[vv]=1;//��¼
		addEdge(uu,vv);addEdge(vv,uu);//����
	}
	for(int i=1;i<=n;i++)//�ж��Ƿ���
	    if(!vis[i]){
	    	printf("NIE\n");//���
	    	return 0;//����
		}
	printf("TAK\n");//ֱ�����
	for(int i=1;i<=n;i++)//ÿ���㶼��һ��
		if(!color[i]){//û�ѹ�
			color[i]=1;//����Ϊ�׵�
			dfs(i);//����
		}
	for(int i=1;i<=n;i++){//���
		if(color[i]==1) printf("K\n");
		else printf("S\n");
	}
	return 0;//��������
}
