#include<bits/stdc++.h>
using namespace std;
#define MAX 105

int n, x1, Y1, ans = 0;
int nums[MAX][MAX], vis[MAX][MAX];

void dfs(int x, int y, int k) {
    if (x < 1 || x > n || y < 1 || y > n || nums[x][y] == 1 || vis[x][y] == 1) {
        // �����߽硢�����ϰ�����ѷ��ʹ���λ�ã�ֱ�ӷ���
        return;
    }

    vis[x][y] = 1; // ��ǵ�ǰλ��Ϊ�ѷ���
    ans = max(ans, k); // ����������

    // �����ĸ��������Ծ
    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    for (auto& dir : directions) {
        int nx = x + dir.first, ny = y + dir.second;
        // ע�⣺���ﲻ��Ҫ�ж� nx �� ny �Ƿ��Ѿ����ʹ�����Ϊһ���������������nx �� ny �����µġ�δ�����ʵ�λ��
        // ��� nx �� ny �������������糬���߽硢�����ϰ����������� dfs ���ò������
        dfs(nx, ny, k + 1);
    }

    vis[x][y] = 0; // ���ݣ���ǵ�ǰλ��Ϊδ���ʣ������Ҫ�ٴη��ʵĻ����ⲽ����ʡ�ԣ�
}

int main() {
    memset(vis, 0, sizeof(vis)); // ��ʼ��Ϊ0����ʾ����λ�ö�δ����
    cin >> n >> x1 >> Y1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> nums[i][j];
        }
    }

    dfs(x1, Y1, 0); // ����㿪ʼ�����������
    printf("%d\n", ans);
    return 0;
}
