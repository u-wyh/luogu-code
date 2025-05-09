#include <bits/stdc++.h>
#define ll long long
#define setp setprecision
#define mem(a, m) memset(a, m, sizeof(a));
using namespace std;

int n, k;
int ans = 0x3f3f3f;
int a[305][305];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
bool vis[305][305];
struct node {
	int x, y;//����
	int Time;//ʱ��
	int size;//С����С
};
bool check(int x, int y, int size)
{
	if(vis[x][y])	return false;
	for(int i=x-size;i<=x+size;i++)
		for(int j=y-size;j<=y+size;j++)
			if(i < 1 || i > n || j < 1 || j > n || a[i][j])
				return false;
	return true;
}
int work(int Time)
{
	if(Time < k)	return 2;
	else if(Time < 2 * k)	return 1;
	else	return 0;
}
void bfs()
{
	queue <node> q;
	vis[3][3] = 1;
	q.push((node){3, 3, 0, 2});
	while(!q.empty())
	{
		node t = q.front();
		q.pop();
		if(t.x == n - 2 && t.y == n - 2)//�����յ㣬ֹͣ����
		{
			cout << t.Time;
			return ;
		}
		if(t.size != 0)	q.push((node){t.x, t.y, t.Time+1, work(t.Time+1)});//վ�Ų���
		for(int i=0;i<4;i++)
		{
			int X = t.x + dx[i];
			int Y = t.y + dy[i];
			if(check(X, Y, t.size))//�ж�
			{
				vis[X][Y] = 1;
				q.push((node){X, Y, t.Time+1, work(t.Time+1)});
			}
		}
	}
}
int main()
{
	cin >> n >> k;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			char c;
			cin >> c;
			if(c == '*')	a[i][j] = 1;
			else	a[i][j] = 0;
		}
	}
	bfs();
	return 0;
}
