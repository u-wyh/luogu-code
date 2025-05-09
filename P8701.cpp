#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, m;
vector<int> tree[N << 2]; // �߶�����ÿ���ڵ�洢һ�� vector

// �ϲ����� vector��������ǰ 8 �����Ԫ��
vector<int> operator+(const vector<int>& a, const vector<int>& b) {
    vector<int> c = a;
    for (int val : b) c.push_back(val);
    sort(c.begin(), c.end(), greater<int>());
    if (c.size() > 8) c.resize(8);
    return c;
}

// �����߶����Ľڵ�
void pushup(int node) {
    tree[node] = tree[node << 1] + tree[node << 1 | 1];
}

// �������
void update(int node, int l, int r, int k, int val) {
    if (l == r) {
        tree[node].clear();
        tree[node].push_back(val);
        return;
    }
    int mid = (l + r) >> 1;
    if (k <= mid) update(node << 1, l, mid, k, val);
    else update(node << 1 | 1, mid + 1, r, k, val);
    pushup(node);
}

// �����ѯ
vector<int> query(int node, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tree[node];
    int mid = (l + r) >> 1;
    vector<int> result;
    if (L <= mid) result = result + query(node << 1, l, mid, L, R);
    if (mid < R) result = result + query(node << 1 | 1, mid + 1, r, L, R);
    return result;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        char opt;
        int x, y;
        cin >> opt >> x >> y;
        if (opt == 'C') {
            update(1, 1, n, x, y); // �������
        } else {
            vector<int> result = query(1, 1, n, x, y); // �����ѯ
            if (result.size() == 8) {
                cout << result.back() << "\n"; // ����� 8 ���ֵ
            } else {
                cout << 0 << "\n"; // ���� 8 ��Ԫ��ʱ��� 0
            }
        }
    }
    return 0;
}
