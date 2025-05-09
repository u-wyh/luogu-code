// ���������Ҫ�Ƴ��ϰ������С��Ŀ
// ����һ���±�� 0 ��ʼ�Ķ�ά�������� grid �������СΪ m x n
// ÿ����Ԫ��������ֵ֮һ��
// 0 ��ʾһ�� �� ��Ԫ��
// 1 ��ʾһ�������Ƴ��� �ϰ���
// ��������ϡ��¡������ƶ�����һ���յ�Ԫ���ƶ�����һ���յ�Ԫ��
// ��������Ҫ�����Ͻ� (0, 0) �ƶ������½� (m - 1, n - 1)
// ������Ҫ�Ƴ����ϰ������С��Ŀ
// �������� : https://leetcode.cn/problems/minimum-obstacle-removal-to-reach-corner/
#include<bits/stdc++.h>
using namespace std;

int minimumObstacles(vector<vector<int>>& grid) {
    int move[5] = {-1, 0, 1, 0, -1}; // �������飺�ϡ��ҡ��¡���
    int m = grid.size();
    int n = grid[0].size();

    // ��ʼ����������
    vector<vector<int>> distance(m, vector<int>(n, INT_MAX));
    distance[0][0] = 0;

    // ˫�˶��У��洢��ǰ������Ľڵ�
    deque<pair<int, int>> dq; // �� deque ��Ϊ dq
    dq.push_front({0, 0});

    while (!dq.empty()) {
        auto record = dq.front();
        dq.pop_front();
        int x = record.first;
        int y = record.second;

        // ��������յ㣬���ص�ǰ����
        if (x == m - 1 && y == n - 1) {
            return distance[x][y];
        }

        // �����ĸ�����
        for (int i = 0; i < 4; i++) {
            int nx = x + move[i];
            int ny = y + move[i + 1];

            // ����������Ƿ�������Χ��
            if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                // ����¾����С�����¾���
                if (distance[x][y] + grid[nx][ny] < distance[nx][ny]) {
                    distance[nx][ny] = distance[x][y] + grid[nx][ny];
                    // ����ǿյأ�0�����������ǰ�ˣ����������к��
                    if (grid[nx][ny] == 0) {
                        dq.push_front({nx, ny});
                    } else {
                        dq.push_back({nx, ny});
                    }
                }
            }
        }
    }

    // ����޷������յ㣬���� -1
    return -1;
}

int main() {
    // ���������С
    int m, n;
    cin >> m >> n;

    // ������������
    vector<vector<int>> grid(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    // ���㲢������
    int result = minimumObstacles(grid);
    cout << result << endl;

    return 0;
}
