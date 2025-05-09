#include<stdio.h>
#include<cstring>
#include<queue>
#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b
using namespace std;
int n,m;
struct edge{
	int to,nxt;
}e[50005];//ʹ����ʽǰ���Ǵ�ͼ
int hed[50005],cnt;//ע��ÿ�����ݿ�ʼǰҪ��hed��cnt��������

inline void add(int u,int v){
	e[++cnt].to = v;
	e[cnt].nxt = hed[u];
	hed[u] = cnt;
}

bool vis[1005];//�ǵ�����

struct node{
	int tp,dis;//tp:��ǰ��ı��;dis:����㵽�����ľ���
};

int ans = -1;//���յĴ�
inline void bfs(int s){
	queue<node> q;
	q.push((node){s,0});//��ʼ״̬
	vis[s] = true;
	while(!q.empty()){
		node fr = q.front();
		q.pop();
		int u = fr.tp,dis = fr.dis;
		ans = max(ans,dis);//�ڱ���ÿ�����ʱ����´�
		for(int i = hed[u];i;i = e[i].nxt){
			int v = e[i].to;
			if(vis[v]) continue;
			q.push((node){v,dis+1});
			vis[v] = true;
		}
	}
}
int main(){
	while(true){
		scanf("%d%d",&n,&m);
		if(n==0 && m==0) break;
		ans = -1;//����
		memset(hed,0,sizeof(hed));
		cnt = 0;
		int u,v;
		for(register int i = 1;i<=m;++i){
			scanf("%d%d",&u,&v);
			add(u,v),add(v,u);//��˫���
		}
		for(register int i = 1;i<=n;++i){//��iΪ������bfs
			memset(vis,false,sizeof(vis));//ÿ��bfs��ʼǰ��������
			bfs(i);
		}
		printf("%d\n",ans*100);
	}
	return 0;
}
