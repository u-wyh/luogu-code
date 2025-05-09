#include <queue>
#include <cstdio>
#include <vector>

using namespace std;

vector<int> web[100005]; //�ڽӱ�
int a[100005]; //A
int ind[100005]; //���
int f[100005][15];
/*
f[i][j] �����xxx�ڵ㵽i�ڵ㣬ĩβΪj������½������г���
*/

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d", a + i);
	}
	for(int i=1;i<=m;i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		web[u].push_back(v); //��ͼ
		ind[v]++; //���++
	}
	queue<int> q; //��������
	for(int i=1;i<=n;i++)
	{
		if(ind[i] == 0) //���Ϊ0������
		{
			q.push(i);
		}
		f[i][a[i]] = 1; //f��ʼ
	}
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int v : web[u])
		{
			if(!--ind[v]) q.push(v); //��ȱ�Ϊ0
			for(int i=1;i<=a[v];i++)
			{
				if(f[u][i] + 1 > f[v][a[v]]) f[v][a[v]] = f[u][i] + 1; //��һ��ת��
			}
			for(int i=1;i<=10;i++)
			{
				if(f[u][i] > f[v][i]) f[v][i] = f[u][i]; //�ڶ���ת��
			}
		}
	}
	int maxn = 0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=10;j++)
		{
			if(f[i][j] > maxn) maxn = f[i][j]; //ȡ���
		}
	}
	printf("%d\n", maxn);
	return 0;
}
