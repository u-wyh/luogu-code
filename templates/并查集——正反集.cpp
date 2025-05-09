// ��Ѻ�ﷸ
// һ����n�����ˣ����1 ~ n��һ������������������Ծ���ÿ������ȥ�ĸ�����
// ����m����¼��ÿ����¼ l r v����ʾl�ŷ��˺�r�ŷ��˵ĳ��ֵ
// ÿ�������ı���ֵ = �ü����г������ķ���֮��ĳ��ֵ
// ��ͻֵ = max(��һ�������ı���ֵ���ڶ��������ı���ֵ)
// ���˵ķ��䷽����Ҫ�������ͻֵ��С��������С���Ƕ���
// 1 <= n <= 20000    1 <= m <= 100000    1 <= ���ֵ <= 10^9
// �������� : https://www.luogu.com.cn/problem/P1525
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
//��ʵ��������ʹ������������
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility> // for std::pair

using namespace std;

const int MAXN = 20002;
const int MAXM = 100001;

int n, m;
int father[MAXN];
int enemy[MAXN];
vector<pair<int, pair<int, int>>> arr(MAXM + 1); // vector of pairs to store the input

void prepare() {
    for (int i = 1; i <= n; i++) {
        father[i] = i;
        enemy[i] = 0;
    }
}

int find(int i) {
    if (father[i] != i) {
        father[i] = find(father[i]); // Path compression
    }
    return father[i];
}

void unionSets(int l, int r) {
    father[find(l)] = find(r);
}

bool sameSet(int l, int r) {
    return find(l) == find(r);
}

int compute() {
    // Sort based on the third element of the pair in descending order
    sort(arr.begin() + 1, arr.end(), [](const pair<int, pair<int, int>>& a, const pair<int, pair<int, int>>& b) {
        return a.second.second > b.second.second;
    });

    int ans = 0;
    for (int i = 1; i <= m; i++) {
        int l = arr[i].second.first;
        int r = arr[i].first;
        int v = arr[i].second.second;
        if (sameSet(l, r)) {
            ans = v;
            break;
        } else {
            if (enemy[l] == 0) {
                enemy[l] = r;
            } else {
                unionSets(enemy[l], r);
            }
            if (enemy[r] == 0) {
                enemy[r] = l;
            } else {
                unionSets(l, enemy[r]);
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    prepare();
    for (int i = 1; i <= m; i++) {
        int l, r, v;
        cin >> l >> r >> v;
        arr[i] = make_pair(r, make_pair(l, v)); // Store in the format {r, {l, v}}
    }

    cout << compute() << endl;

    return 0;
}
