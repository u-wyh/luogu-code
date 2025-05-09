#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
int n, k;
char g[N][N];
int vis[N][N]; // �洢ÿ�������Ƿ񱻷��ʹ��Լ��޵�״̬ʣ�ಽ��
struct node{
	int x, y, step, magic;
};

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int main(){
	cin >> n >> k;
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j <= n; j ++ )
			cin >> g[i][j];
	memset(vis, -1, sizeof vis);
	queue<node> q;
	vis[1][1] = 0; // �����ķ���״̬����Ϊ0
	q.push({1, 1, 0, 0}); // �������ӣ��������䵽��õ�Ĳ���Ϊ0����ǰ�������޵�״̬
	while (q.size()){
		node t = q.front(); // ȡ����ͷ�ڵ�
		q.pop();
		if (t.x == n && t.y == n){ // �����ǰ�ڵ�Ϊ�յ㣬��������·���Ȳ���������
			cout << t.step;
			return 0;
		}
		for (int i = 0; i < 4; i ++ ){
			int tx = t.x + dx[i];
			int ty = t.y + dy[i];
			if (g[tx][ty] == 'X' && t.magic == 0) // �����һ��λ���������ҵ�ǰ�������޵�״̬���������ýڵ�
				continue;
			int magic = max(0, t.magic - 1); // ���㵱ǰ�޵�״̬ʣ�ಽ��
			if (g[tx][ty] == '%') // �����һ��λ���е��ߣ������޵�״̬ʣ�ಽ��
				magic = k;
			if (tx >= 1 && tx <= n && ty >= 1 && ty <= n && vis[tx][ty] < magic && g[tx][ty] != '#'){ // �����һ��λ���ǺϷ��Ŀɵ���λ��
				vis[tx][ty] = magic; // ���·���״̬���޵�״̬ʣ�ಽ��
				q.push({tx, ty, t.step + 1, magic}); // ����һ��λ����ӣ������µ���õ�Ĳ������޵�״̬ʣ�ಽ��
			}
		}
	}
	cout << -1;
    return 0;
}
