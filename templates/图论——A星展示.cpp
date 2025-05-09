#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// �����ƶ��������飬0:�ϣ�1:�ң�2:�£�3:��
const int mov[5] = { -1, 0, 1, 0, -1 };

// Dijkstra�㷨
// grid[i][j] == 0 �����ϰ�
// grid[i][j] == 1 �����·
// ֻ�����ϡ��¡����ң�������б�߷���
// ���ش�(startX, startY)��(targetX, targetY)����̾���
int minDistance1(vector<vector<int>>& grid, int startX, int startY, int targetX, int targetY) {
    if (grid[startX][startY] == 0 || grid[targetX][targetY] == 0) {
        return -1;
    }
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> distance(n, vector<int>(m, INT_MAX));
    distance[startX][startY] = 1;
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> heap;
    heap.emplace(1, make_pair(startX, startY));
    while (!heap.empty()) {
        auto cur = heap.top();
        heap.pop();
        int d = cur.first;
        int x = cur.second.first;
        int y = cur.second.second;
        if (visited[x][y]) {
            continue;
        }
        visited[x][y] = true;
        if (x == targetX && y == targetY) {
            return distance[x][y];
        }
        for (int i = 0; i < 4; ++i) {
            int nx = x + mov[i];
            int ny = y + mov[i + 1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 1 && !visited[nx][ny] && d + 1 < distance[nx][ny]) {
                distance[nx][ny] = d + 1;
                heap.emplace(d + 1, make_pair(nx, ny));
            }
        }
    }
    return -1;
}


// �����پ���
int f1(int x, int y, int targetX, int targetY) {
    return abs(targetX - x) + abs(targetY - y);
}

// �Խ��߾���
int f2(int x, int y, int targetX, int targetY) {
    return max(abs(targetX - x), abs(targetY - y));
}

// ŷʽ����
double f3(int x, int y, int targetX, int targetY) {
    return sqrt(pow(targetX - x, 2) + pow(targetY - y, 2));
}

// A*�㷨
// grid[i][j] == 0 �����ϰ�
// grid[i][j] == 1 �����·
// ֻ�����ϡ��¡����ң�������б�߷���
// ���ش�(startX, startY)��(targetX, targetY)����̾���
int minDistance2(vector<vector<int>>& grid, int startX, int startY, int targetX, int targetY) {
    if (grid[startX][startY] == 0 || grid[targetX][targetY] == 0) {
        return -1;
    }
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> distance(n, vector<int>(m, INT_MAX));
    distance[startX][startY] = 1;
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    auto compare = [](const pair<int, pair<int, int>>& a, const pair<int, pair<int, int>>& b) {
        return a.first > b.first;
    };
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, decltype(compare)> heap(compare);
    heap.emplace(1 + f1(startX, startY, targetX, targetY), make_pair(startX, startY));
    while (!heap.empty()) {
        auto cur = heap.top();
        heap.pop();
        int d = cur.first - f1(cur.second.first, cur.second.second, targetX, targetY); // ʵ�ʾ���
        int x = cur.second.first;
        int y = cur.second.second;
        if (visited[x][y]) {
            continue;
        }
        visited[x][y] = true;
        if (x == targetX && y == targetY) {
            return distance[x][y];
        }
        for (int i = 0; i < 4; ++i) {
            int nx = x + mov[i];
            int ny = y + mov[i + 1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 1 && !visited[nx][ny] && distance[x][y] + 1 < distance[nx][ny]) {
                distance[nx][ny] = distance[x][y] + 1;
                heap.emplace(distance[nx][ny] + 1 + f1(nx, ny, targetX, targetY), make_pair(nx, ny));
            }
        }
    }
    return -1;
}

// Ϊ�˲���
vector<vector<int>> randomGrid(int n) {
    vector<vector<int>> grid(n, vector<int>(n));
    srand(time(0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            grid[i][j] = rand() % 10 < 3 ? 0 : 1; // ÿ��������30%������0
        }
    }
    return grid;
}

// Ϊ�˲���
int main() {
    int len = 100;
    int testTime = 1000;
    cout << "���ܲ��Կ�ʼ" << endl;
    for (int i = 0; i < testTime; ++i) {
        int n = rand() % len + 2;
        vector<vector<int>> grid = randomGrid(n);
        int startX = rand() % n;
        int startY = rand() % n;
        int targetX = rand() % n;
        int targetY = rand() % n;
        int ans1 = minDistance1(grid, startX, startY, targetX, targetY);
        int ans2 = minDistance2(grid, startX, startY, targetX, targetY);
        if (ans1 != ans2) {
            cout << "������!" << endl;
        }else {
            cout << "��" << setw(5) << i << "�������ȷ��" << endl;
        }
    }
    cout << "���ܲ��Խ���" << endl;

    cout << "���ܲ��Կ�ʼ" << endl;
    vector<vector<int>> grid_large = randomGrid(2000);
    int startX = 0;
    int startY = 0;
    int targetX = 1999;
    int targetY = 1999;
    clock_t start, end;
    start = clock();
    int ans1 = minDistance1(grid_large, startX, startY, targetX, targetY);
    end = clock();
    cout << "����Dijkstra�㷨���: " << ans1 << ", ����ʱ��(����) : " << double(end - start) / CLOCKS_PER_SEC * 1000 << endl;
    start = clock();
    int ans2 = minDistance2(grid_large, startX, startY, targetX, targetY);
    end = clock();
    cout << "����A*�㷨���: " << ans2 << ", ����ʱ��(����) : " << double(end - start) / CLOCKS_PER_SEC * 1000 << endl;
    cout << "���ܲ��Խ���" << endl;
    return 0;
}
