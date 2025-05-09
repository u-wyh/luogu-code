#include <bits/stdc++.h>
using namespace std;

// 0:�ϣ�1:�ң�2:�£�3:��
const int mov[5] = { -1, 0, 1, 0, -1 };

// Dijkstra�㷨
int minDistance1(const std::vector<std::vector<int>>& grid, int startX, int startY, int targetX, int targetY) {
    if (grid[startX][startY] == 0 || grid[targetX][targetY] == 0) {
        return -1;
    }
    int n = grid.size();
    int m = grid[0].size();
    std::vector<std::vector<int>> distance(n, std::vector<int>(m, INT_MAX));
    distance[startX][startY] = 1;
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));

    // ��С�ѣ����վ�������
    auto cmp = [](const std::tuple<int, int, int>& a, const std::tuple<int, int, int>& b) {
        return std::get<2>(a) > std::get<2>(b);
    };
    std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, decltype(cmp)> heap(cmp);
    heap.emplace(startX, startY, 1);

    while (!heap.empty()) {
        auto cur = heap.top();
        heap.pop();
        int x = std::get<0>(cur);
        int y = std::get<1>(cur);
        if (visited[x][y]) {
            continue;
        }
        visited[x][y] = true;
        if (x == targetX && y == targetY) {
            return distance[x][y];
        }
        for (int i = 0, nx, ny; i < 4; ++i) {
            nx = x + mov[i];
            ny = y + mov[i + 1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 1 && !visited[nx][ny] && distance[x][y] + 1 < distance[nx][ny]) {
                distance[nx][ny] = distance[x][y] + 1;
                heap.emplace(nx, ny, distance[nx][ny]);
            }
        }
    }
    return -1;
}

// �����پ���
int f1(int x, int y, int targetX, int targetY) {
    return std::abs(targetX - x) + std::abs(targetY - y);
}

// A*�㷨
int minDistance2(const std::vector<std::vector<int>>& grid, int startX, int startY, int targetX, int targetY) {
    if (grid[startX][startY] == 0 || grid[targetX][targetY] == 0) {
        return -1;
    }
    int n = grid.size();
    int m = grid[0].size();
    std::vector<std::vector<int>> distance(n, std::vector<int>(m, INT_MAX));
    distance[startX][startY] = 1;
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));

    // ��С�ѣ������ܴ��ۣ�ʵ�ʴ���+Ԥ�����ۣ�����
    auto cmp = [](const std::tuple<int, int, int>& a, const std::tuple<int, int, int>& b) {
        return std::get<2>(a) > std::get<2>(b);
    };
    std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, decltype(cmp)> heap(cmp);
    heap.emplace(startX, startY, 1 + f1(startX, startY, targetX, targetY));

    while (!heap.empty()) {
        auto cur = heap.top();
        heap.pop();
        int x = std::get<0>(cur);
        int y = std::get<1>(cur);
        if (visited[x][y]) {
            continue;
        }
        visited[x][y] = true;
        if (x == targetX && y == targetY) {
            return distance[x][y];
        }
        for (int i = 0, nx, ny; i < 4; ++i) {
            nx = x + mov[i];
            ny = y + mov[i + 1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 1 && !visited[nx][ny] && distance[x][y] + 1 < distance[nx][ny]) {
                distance[nx][ny] = distance[x][y] + 1;
                heap.emplace(nx, ny, distance[nx][ny] + f1(nx, ny, targetX, targetY));
            }
        }
    }
    return -1;
}

// �Խ��߾���
int f2(int x, int y, int targetX, int targetY) {
    return std::max(std::abs(targetX - x), std::abs(targetY - y));
}

// ŷʽ����
double f3(int x, int y, int targetX, int targetY) {
    return std::sqrt(std::pow(targetX - x, 2) + std::pow(targetY - y, 2));
}

// Ϊ�˲���
std::vector<std::vector<int>> randomGrid(int n) {
    std::vector<std::vector<int>> grid(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            grid[i][j] = (rand() % 10 < 2) ? 0 : 1; // ÿ��������30%������0
        }
    }
    return grid;
}

// Ϊ�˲���
int main() {
    srand(time(0));
    int len = 100;
    int testTime = 1000;
    cout << "���ܲ��Կ�ʼ" << endl;
    for (int i = 0; i < testTime; ++i) {
        int n = rand() % len + 2;
        std::vector<std::vector<int>> grid = randomGrid(n);
        int startX = rand() % n;
        int startY = rand() % n;
        int targetX = rand() % n;
        int targetY = rand() % n;
        int ans1 = minDistance1(grid, startX, startY, targetX, targetY);
        int ans2 = minDistance2(grid, startX, startY, targetX, targetY);
        if (ans1 != ans2) {
            cout << "������!" << endl;
        } else {
            cout << "��" << setw(5) << i << "�������ȷ��" << endl;
        }
    }
    cout << "���ܲ��Խ���" << endl;

    cout << "���ܲ��Կ�ʼ" << endl;
    std::vector<std::vector<int>> grid = randomGrid(4000);
    int startX = 0;
    int startY = 0;
    int targetX = 3900;
    int targetY = 3900;

    // ʹ�� chrono ����и߾���ʱ�����
    auto start1 = chrono::high_resolution_clock::now();
    int ans1 = minDistance1(grid, startX, startY, targetX, targetY);
    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> elapsed1 = end1 - start1;
    cout << "����Dijkstra�㷨���: " << ans1 << ", ����ʱ��(����) : "
          << elapsed1.count() << endl;

    auto start2 = chrono::high_resolution_clock::now();
    int ans2 = minDistance2(grid, startX, startY, targetX, targetY);
    auto end2 = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> elapsed2 = end2 - start2;
    cout << "����A*�㷨���: " << ans2 << ", ����ʱ��(����) : "
          << elapsed2.count() << endl;

    return 0;
}
