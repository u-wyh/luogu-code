// Ѱ������ʹν�
// ����һ������Ϊn������arr���±�1 ~ n��Χ���������ظ�ֵ
// ���ڽ��Ķ��壬����Ķ�������:
// ��iλ�õ�����x��˵��ֻ��ע�Ҳ�����֣���x�Ĳ�ֵ����ֵԽС��Խ��
// ����Ϊ��ֵ����ֵ���������һ������ֵԽС��Խ��
// ��ֵ : 3 5 7 1
// �±� : 1 2 3 4
// ��1λ�õ�����3��˵����һ����4λ�õ�1������Ϊ2���ڶ�����2λ�õ�5������Ϊ2
// ÿ��λ�õ����ֶ����һ����λ�ü�����롢�ڶ�����λ�ü������
// �ֱ���to1��dist1��to2��dist2�����ʾ��0��ʾ������
// ������ʵ�� + �����ִ�˫�������ʵ��
// ��������֤
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
#include <iomanip>

using namespace std;

const int MAXN = 10001;

int arr[MAXN];
int n;
int to1[MAXN];
int dist1[MAXN];
int to2[MAXN];
int dist2[MAXN];

pair<int, int> Rank[MAXN];
int pre[MAXN];
int nex[MAXN];

void update(int i, int j, int dist) {
    if (j == 0) return;
    if (to1[i] == 0 || dist < dist1[i] || (dist == dist1[i] && arr[j] < arr[to1[i]])) {
        to2[i] = to1[i];
        dist2[i] = dist1[i];
        to1[i] = j;
        dist1[i] = dist;
    } else if (to2[i] == 0 || dist < dist2[i] || (dist == dist2[i] && arr[j] < arr[to2[i]])) {
        to2[i] = j;
        dist2[i] = dist;
    }
}

void near1() {
    set<pair<int, int>, greater<pair<int, int>>> set;
    for (int i = n; i >= 1; --i) {
        to1[i] = to2[i] = 0;
        dist1[i] = dist2[i] = INT_MAX;
        auto cur = make_pair(arr[i], i);
        auto it = set.lower_bound(cur);
        if (it != set.begin()) {
            --it;
            update(i, it->second, abs(arr[i] - it->first));
        }
        auto it2 = set.upper_bound(cur);
        if (it2 != set.end()) {
            update(i, it2->second, abs(arr[i] - it2->first));
        }
        set.insert(cur);
    }
}

void near2() {
    for (int i = 1; i <= n; ++i) {
        Rank[i] = make_pair(arr[i], i);
    }
    sort(Rank + 1, Rank + n + 1);
    for (int i = 1; i <= n; ++i) {
        pre[Rank[i].second] = (i > 1) ? Rank[i - 1].second : 0;
        nex[Rank[i].second] = (i < n) ? Rank[i + 1].second : 0;
    }
    for (int i = 1; i <= n; ++i) {
        update(i, pre[i], abs(arr[i] - arr[pre[i]]));
        if (pre[pre[i]] != 0) {
            update(i, pre[pre[i]], abs(arr[i] - arr[pre[pre[i]]]));
        }
        update(i, nex[i], abs(arr[i] - arr[nex[i]]));
        if (nex[nex[i]] != 0) {
            update(i, nex[nex[i]], abs(arr[i] - arr[nex[nex[i]]]));
        }
    }
}

void randomFill(int v) {
    unordered_set<int> set;
    while (set.size() < n) {
        int cur = rand() % (2 * v) - v + 1;
        set.insert(cur);
    }
    auto it = set.begin();
    for (int i = 1; i <= n; ++i) {
        arr[i] = *it++;
    }
}

bool check() {
    near1();
    vector<int> a(MAXN), b(MAXN), c(MAXN), d(MAXN);
    for (int i = 1; i <= n; ++i) {
        a[i] = to1[i];
        b[i] = dist1[i];
        c[i] = to2[i];
        d[i] = dist2[i];
    }
    near2();
    for (int i = 1; i <= n; ++i) {
        if (a[i] != to1[i] || b[i] != dist1[i]) {
            return false;
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (c[i] != to2[i] || d[i] != dist2[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    srand(time(0));
    n = 100;
    int v = 500;
    int testTime = 100;
    cout << "���Կ�ʼ" << endl;
    for (int i = 1; i <= testTime; ++i) {
        randomFill(v);
        if (!check()) {
            cout << "������!" << endl;
        } else {
            cout << "��" << setw(3) << i << "�������ȷ" << endl;
        }
        // system("pause"); // ע�͵������Լӿ�����ٶ�
    }
    cout << "���Խ���" << endl;
    return 0;
}
