// ʹ����ͼ������һ����Ч·������С����
// ����һ�� m * n ������ͼ grid �� grid ��ÿ�����Ӷ���һ������
// ��Ӧ�ŴӸø��ӳ�����һ���ߵķ��� grid[i][j] �е����ֿ���Ϊ���¼��������
// 1 ����һ�������ߣ�Ҳ�������� grid[i][j] �ߵ� grid[i][j + 1]
// 2 ����һ�������ߣ�Ҳ�������� grid[i][j] �ߵ� grid[i][j - 1]
// 3 ����һ�������ߣ�Ҳ�������� grid[i][j] �ߵ� grid[i + 1][j]
// 4 ����һ�������ߣ�Ҳ�������� grid[i][j] �ߵ� grid[i - 1][j]
// ע������ͼ�п��ܻ��� ��Ч���� ����Ϊ���ǿ���ָ�� grid ���������
// һ��ʼ�����������Ͻǵĸ��� (0,0) ����
// ���Ƕ���һ�� ��Ч·�� Ϊ�Ӹ��� (0,0) ������ÿһ����˳�����ֶ�Ӧ������
// �����������½ǵĸ��� (m - 1, n - 1) ������·��
// ��Ч·�� ����Ҫ�����·��
// ����Ի���1�Ĵ����޸�һ�������е����֣���ÿ�������е����� ֻ���޸�һ��
// ���㷵��������ͼ������һ����Ч·������С����
// �������� : https://leetcode.cn/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/
#include <iostream>
#include <vector>
#include <deque>
#include <climits>

using namespace std;

int minCost(vector<vector<int>>& grid) {
    // ���ӵ���ֵ :
    // 1 ��
    // 2 ��
    // 3 ��
    // 4 ��
    //                0      1         2          3         4
    vector<vector<int>> move = { {}, { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> distance(m, vector<int>(n, INT_MAX));
    deque<pair<int, int>> q;
    q.push_front({ 0, 0 });
    distance[0][0] = 0;
    while (!q.empty()) {
        auto record = q.front();
        q.pop_front();
        int x = record.first;
        int y = record.second;
        if (x == m - 1 && y == n - 1) {
            return distance[x][y];
        }
        for (int i = 1; i <= 4; i++) {
            int nx = x + move[i][0];
            int ny = y + move[i][1];
            int weight = grid[x][y] != i ? 1 : 0;
            if (nx >= 0 && nx < m && ny >= 0 && ny < n
                && distance[x][y] + weight < distance[nx][ny]) {
                distance[nx][ny] = distance[x][y] + weight;
                if (weight == 0) {
                    q.push_front({ nx, ny });
                } else {
                    q.push_back({ nx, ny });
                }
            }
        }
    }
    return -1;
}

int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> grid(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    cout << minCost(grid) << endl;
    return 0;
}
