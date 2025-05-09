//P10193
// �����Ŀ�ܴ��� �����DJ�㷨�����̶�
// ����Դ�㲻�ٽ���ֻ��һ����  �����кܶ��
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int MAXM = 2e5+5;

int n,m,c,r,k;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt = 1;

struct node{
	int id,dis,pre;
	//��ʾ��ǰ�����Ľڵ���  pre��ʾ����Ŀǰ������·�������Ǹ�Դ�����������  dis��ʾ��preԴ������ĵ�id��������̾���
};
struct Compare {
    bool operator()(const node& a, const node& b) {
        return a.dis > b.dis;
    }
};
priority_queue<node, vector<node>, Compare> heap;
map<int,bool>vis[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dijkstra(){
	for(int i=1;i<=c;i++){
		heap.push({i,0,i});
	}
	while(!heap.empty()){
		node now=heap.top();
		heap.pop();
		int u=now.id;
		int dis=now.dis;
		int pre=now.pre;

		if (vis[u].size() >= k || vis[u].count(pre)) {
            //��ʾ����ڵ��Ѿ��Ƿ���Ҫ�����  ����  ��ǰ���Ѿ�����˴�pre���Դ����������·
            continue;
        }
		vis[u][pre] = true;
        for(int i=head[u];i;i=nxt[i]){
			int v=to[i];
			int w=weight[i];
			int d=w+dis;
			if(d>r||vis[v].size()>=k||vis[v].count(pre)){
				continue;
			}
			heap.push({v,d,pre});
		}
	}
}

int main()
{
	n=read(),m=read(),c=read(),r=read(),k=read();
	for(int i=1;i<=m;i++){
		int u,v,w;
		u=read(),v=read(),w=read();
		addedge(u,v,w);
		addedge(v,u,w);
	}
	dijkstra();
	vector<int> vec;
    for (int i = c + 1; i <= n; i++) {
        if (vis[i].size() >= k) {
            vec.push_back(i);
        }
    }
    
    cout << vec.size() << '\n';
    for (int to : vec) {
        cout << to << '\n';
    }
	return 0;
}