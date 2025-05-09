#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN = 1500 + 1;
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

int n, m;
int st_x, st_y;
int vis[MAXN][MAXN][3];//vis[x][y]��ʾ���Ƕ�������λ�ã�ֻҪ��ԭͼ�϶�Ӧ����xy�ģ��ĵ�
//vis[x][y][0]��ʾ�������λ���Ƿ����κ�һ��ֻҪ��ԭͼ�϶�Ӧ����xy�Ľڵ�����
//vis[x][y][1]��ʾ����������� ��һ��������ʵλ��xλ��
bool fl, a[MAXN][MAXN];
char ch;

void dfs(int x, int y, int lx, int ly) {
    //xy�ֱ��Ƕ�Ӧ��ԭʼ����ͼ��λ��
    //lx ly�ֱ��Ӧ����ʵ��Ӧ�õ�λ�ã����������Խ�磬�����ָ����ԭʼ����ͼ�Ľ�
    //Ϊʲô��ô��  ��Ϊ�˷�ֹ�����߻��������µĽ���
    //Ϊʲôһ��Ҫ����lx ly����Ϊxy��Ӧ��vis�ᱻ��η��� �����Դ����ж��Ƿ���Խ�������������
	if(fl) return;
	if(vis[x][y][0] && (vis[x][y][1]!=lx || vis[x][y][2]!=ly)) {
		fl = 1;
		return;
	}
	//����������е����� ��ôһ�������λ��û���κνڵ�����
	vis[x][y][1] = lx, vis[x][y][2] = ly, vis[x][y][0] = 1;
	for(int i=0; i<4; ++i) {
		int xx = (x + dx[i] + n) % n, yy = (y + dy[i] + m) % m;//��Ӧԭͼ��λ��
		int lxx = lx + dx[i], lyy = ly + dy[i];//��ʵ��λ��
		if(!a[xx][yy]) {
            //��ʾ������
			if(vis[xx][yy][1]!=lxx || vis[xx][yy][2]!=lyy || !vis[xx][yy][0])
				dfs(xx, yy, lxx, lyy);//���߻�ͷ·  Ҫô��ǰ��Ӧԭͼ����û�߹�  Ҫô�߹�����������ڵ�
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	while(cin >> n >> m) {
		fl = 0;
		memset(a, 0, sizeof(a));
		memset(vis, 0, sizeof(vis));
		for(int i=0; i<n; ++i)
			for(int j=0; j<m; ++j) {
				cin >> ch;
				if(ch == '#') a[i][j] = 1;
				if(ch == 'S') st_x = i, st_y = j;
			}
		dfs(st_x, st_y, st_x, st_y);
		if(fl) puts("Yes");
		else puts("No");
	}
	return 0;
}
