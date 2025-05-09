// ����ƻ�(������)
// ��n���ڵ㣬����n-1����ʹ�����ӳ�һ������ÿ������������Ȩ
// �����ܶ�����ƻ���ÿ������ƻ�(a,b)��ʾ��aȥ��b
// ÿ������ƻ��Ĵ��۾�����;��Ȩ�ͣ�����ƻ�֮����ȫ��������
// ��ֻ��ѡ��һ���ߣ������Ȩ���0
// ���Ŀ��������������ƻ����۵����ֵ����С
// ������������ƻ����۵����ֵ��С���Ƕ���
// �������� : https://www.luogu.com.cn/problem/P2680
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ����������
//�߲�ֵı���Ϣ�����ɺ��ӽڵ�洢�� 
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 300001;
const int MAXM = 300001;

int n,m;

// num[i] : i�ڵ���丸�ڵ�ıߣ��ж��ٴ���>=limit������ƻ��õ�
int num[MAXN];

// ��ʽǰ���ǽ�ͼ��Ҫ
int headEdge[MAXN];
int edgeNext[MAXN << 1];
int edgeTo[MAXN << 1];
int edgeWeight[MAXN << 1];
int tcnt=1;

// tarjan�㷨��Ҫ
int headQuery[MAXN];
int queryNext[MAXM << 1];
int queryTo[MAXM << 1];
int queryIndex[MAXM << 1];
int qcnt=1;

bool visited[MAXN];
int fa[MAXN];
int quesu[MAXM];
int quesv[MAXM];

// distance[i] : ͷ�ڵ㵽i�ŵ�ľ��룬tarjan�㷨�����и���   �������u��v�Ļ���
int dis[MAXN];
// lca[i] : ��i������ƻ������˵�lca��tarjan�㷨�����и���
int lca[MAXM];
// cost[i] : ��i������ƻ������Ƕ��٣�tarjan�㷨�����и���
int cost[MAXM];
// ��������ƻ��������ۣ�tarjan�㷨�����и���
int maxCost;
// ����Ҫ���ٶ��ٱ�Ȩ  ��ô�����ڿ���ɾ����һ���ߵ�ʱ�� ��Ȩ��������ľͲ��ÿ�����
int atLeast;
// ����Ҫ�������ƻ��м���
int beyond;

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

void addEdge(int u, int v, int w) {
    edgeNext[tcnt] = headEdge[u];
    edgeTo[tcnt] = v;
    edgeWeight[tcnt] = w;
    headEdge[u] = tcnt++;
}

void addQuery(int u, int v, int i) {
    queryNext[qcnt] = headQuery[u];
    queryTo[qcnt] = v;
    queryIndex[qcnt] = i;
    headQuery[u] = qcnt++;
}

int find(int i) {
    if (i != fa[i]) {
        fa[i] = find(fa[i]);
    }
    return fa[i];
}

void tarjan(int u, int f, int w) {
    visited[u] = true;
    dis[u] = dis[f] + w;
    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) {
        v = edgeTo[e];
        if (v != f) {
            tarjan(v, u, edgeWeight[e]);
        }
    }
    for (int e = headQuery[u], v, i; e != 0; e = queryNext[e]) {
        v = queryTo[e];
        if (visited[v]) {
            i = queryIndex[e];
            lca[i] = find(v);
            cost[i] = dis[u] + dis[v] - 2 * dis[lca[i]];
            maxCost = max(maxCost, cost[i]);
        }
    }
    fa[u] = f;
}

//��ʾ����u��f������ȨֵΪw�ı�ɾ���Ƿ������������  
bool dfs(int u, int f, int w) {
    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) {
        v = edgeTo[e];
        if (v != f) {
            if (dfs(v, u, edgeWeight[e])) {
                return true;
            }
        }
    }
    for (int e = headEdge[u], v; e != 0; e = edgeNext[e]) {
        v = edgeTo[e];
        if (v != f) {
            num[u] += num[v];
        }
    }
    return num[u] == beyond && w >= atLeast;
    //��ʱ��num[u]��ʾ��u��fһ������Ӱ���������  ���ж��������õ�
}

// ֻ�ܰ�һ���ߵ�Ȩֵ���0
// ��Ҫ��ÿ������ƻ��Ĵ��۶�Ҫ<=limit
// �����ܲ�������
bool f(int limit) {
	atLeast = maxCost - limit;
	for(int i=1;i<=n;i++){
        num[i]=0;
	}
	beyond = 0;//��ʾ�ж�����·�߻��ѳ�����limit
	for (int i = 1; i <= m; i++) {
		if (cost[i] > limit) {
			num[quesu[i]]++;
			num[quesv[i]]++;
			num[lca[i]] -= 2;
			beyond++;
		}
	}
	return beyond == 0 || dfs(1, 0, 0);
}

int compute() {
    tarjan(1, 0, 0);
    int l = 0, r = maxCost, mid;
    int ans = 0;
    while (l <= r) {
        mid = (l + r) / 2;
        if (f(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

int main()
{
    n=read(),m=read();
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    for(int i=1,u,v,w;i<n;i++){
        u=read(),v=read(),w=read();
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    for(int i=1,u,v;i<=m;i++){
        u=read(),v=read();
        quesu[i]=u;
        quesv[i]=v;
        addQuery(u,v,i);
        addQuery(v,u,i);
    }
    cout<<compute()<<endl;
    return 0;
}
