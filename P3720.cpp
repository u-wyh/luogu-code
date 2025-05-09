#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 100010, INF = 1e9;

struct edge {
	int to, cost;
};
std::vector<edge> G[MAXN], G1[MAXN], G2[MAXN];

int n, m, d1[MAXN], d2[MAXN], d[MAXN];
bool exist[MAXN];
queue<int> q;

void spfa1(int s) { //��һ��GPSϵͳ
	fill(d1+1, d1+1+n, INF);
	memset(exist, false, sizeof(exist));//��ʼ��Ī������
	d1[s] = 0;
	q.push(s);
	exist[s] = true;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		exist[v] = false;
		for (int i=0; i<G1[v].size(); i++) {
			edge e = G1[v][i];
			if (d1[v] + e.cost < d1[e.to]) {
				d1[e.to] = d1[v] + e.cost;
				if (!exist[e.to]) {
					q.push(e.to);
					exist[e.to] = true;
				}
			} 
		}
	}
}

void spfa2(int s) { //�ڶ���GPSϵͳ
	fill(d2+1, d2+1+n, INF);
	memset(exist, false, sizeof(exist));//��ʼ��Ī������
	d2[s] = 0;
	q.push(s);
	exist[s] = true;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		exist[v] = false;
		for (int i=0; i<G2[v].size(); i++) {
			edge e = G2[v][i];
			if (d2[v] + e.cost < d2[e.to]) {
				d2[e.to] = d2[v] + e.cost;
				if (!exist[e.to]) {
					q.push(e.to);
					exist[e.to] = true;
				}
			} 
		}
	}
}

void spfa(int s) { //���㱧Թֵ
	fill(d+1, d+1+n, INF);
	memset(exist, false, sizeof(exist));//��ʼ��Ī������
	d[s] = 0;
	q.push(s);
	exist[s] = true;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		exist[v] = false;
		for (int i=0; i<G[v].size(); i++) {
			edge e = G[v][i];
			if (d[v] + e.cost < d[e.to]) {
				d[e.to] = d[v] + e.cost;
				if (!exist[e.to]) {
					q.push(e.to);
					exist[e.to] = true;
				}
			} 
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i=1; i<=m; i++) {
		int u, v, c1, c2;
		cin >> u >> v >> c1 >> c2;
		G1[v].push_back((edge){u, c1});
		G2[v].push_back((edge){u, c2});//ע�⣡��Ϊ������ͼ�������ڽ�����ͼʱ��Ҫע�ⷽ��
	}//������ͼ
	spfa1(n);
	spfa2(n);
	for (int i=1; i<=n; i++)
		for (int j=0; j<G1[i].size(); j++) {
			edge e1 = G1[i][j], e2 = G2[i][j];
			int cnt = 0;
			if (d1[e1.to] - d1[i] != e1.cost) cnt++;
			if (d2[e2.to] - d2[i] != e2.cost) cnt++; //ע�⣡���ﲻ��д��d2[i] - d2[e.to]����Ϊ��֮ǰ�����Ƿ���ͼ������Ӧ����e2.to��Ȩֵ����һ��ͬ��
			G[e1.to].push_back((edge){i, cnt}); //ע�⣡��Ϊ���һ����SPFAʱ���Ǵ�1�Žڵ�����ģ����Խ�ͼʱҪ������ͼ��
		}
	spfa(1);
	cout << d[n]  << endl;
	return 0;//���������
}