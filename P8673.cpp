#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
int n, k;
char g[N][N];
int vis[N][N]; // 存储每个格子是否被访问过以及无敌状态剩余步数
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
	vis[1][1] = 0; // 将起点的访问状态设置为0
	q.push({1, 1, 0, 0}); // 将起点入队，并设置其到达该点的步数为0、当前不处于无敌状态
	while (q.size()){
		node t = q.front(); // 取出队头节点
		q.pop();
		if (t.x == n && t.y == n){ // 如果当前节点为终点，则输出最短路长度并结束程序
			cout << t.step;
			return 0;
		}
		for (int i = 0; i < 4; i ++ ){
			int tx = t.x + dx[i];
			int ty = t.y + dy[i];
			if (g[tx][ty] == 'X' && t.magic == 0) // 如果下一步位置是陷阱且当前不处于无敌状态，则跳过该节点
				continue;
			int magic = max(0, t.magic - 1); // 计算当前无敌状态剩余步数
			if (g[tx][ty] == '%') // 如果下一步位置有道具，更新无敌状态剩余步数
				magic = k;
			if (tx >= 1 && tx <= n && ty >= 1 && ty <= n && vis[tx][ty] < magic && g[tx][ty] != '#'){ // 如果下一步位置是合法的可到达位置
				vis[tx][ty] = magic; // 更新访问状态和无敌状态剩余步数
				q.push({tx, ty, t.step + 1, magic}); // 将下一步位置入队，并更新到达该点的步数和无敌状态剩余步数
			}
		}
	}
	cout << -1;
    return 0;
}
