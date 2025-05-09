//https://codeforces.com/problemset/problem/896/C
//1 l r x ����[l,r]��������������x
//2 l r x ����[l,r]�����������ĳ�x
//3 l r x �������[l,r] �����С���������ĵ�x�����ǵĶ���
//4 l r x y �����[l,r] ����ÿ�����ֵ�x�η��ĺ�ģy��ֵ
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define IT set<Node>::iterator

// ��������ڵ�ṹ��
struct Node {
    int l, r;       // ��������Ҷ˵�
    mutable int v;  // �����ֵ��mutable ������ const �������޸�
    Node(int L, int R = -1, int V = 0) : l(L), r(R), v(V) {}
    // ���� < ����������� set ����
    bool operator<(const Node &o) const {
        return l < o.l;
    }
};

set<Node> s; // ʹ�� set �洢����ڵ�

// �������� pos ���ָ���طָ��������������
IT split(int pos) {
    IT it = s.lower_bound(Node(pos)); // �ҵ���һ����˵� >= pos ������
    if (it != s.end() && it->l == pos)
        return it; // ��� pos ������ĳ���������㣬ֱ�ӷ���
    --it; // �����ҵ����� pos ������
    int L = it->l, R = it->r, V = it->v;
    s.erase(it); // ɾ��ԭ����
    s.insert(Node(L, pos - 1, V)); // ������벿��
    return s.insert(Node(pos, R, V)).first; // �����Ұ벿�ֲ����ص�����
    // ����һ��pair�����е�һ��Ԫ����һ����������ָ������Ԫ�أ����Ѿ����ڵ�Ԫ�أ���
    // �ڶ���Ԫ����һ������ֵ����ʾ�����Ƿ�ɹ���
}

// ���丳ֵ����
void assign(int l, int r, int val) {
    IT itr = split(r + 1), itl = split(l); // �ָ����� [l, r]
    s.erase(itl, itr); // ɾ�� [l, r] �ڵ��������� ɾ����itl��itr֮�������Ԫ�أ�������itr��
    s.insert(Node(l, r, val)); // �����µ�����
}

// ����ӷ�����
void add(int l, int r, int val) {
    IT itr = split(r + 1), itl = split(l); // �ָ����� [l, r]
    for (; itl != itr; ++itl)
        itl->v += val; // ��ÿ�������ڵ�ֵ���� val
}

// ��ѯ����� k С����
int kth(int l, int r, int k) {
    vector<pair<int, int>> v; // �洢�����ڵ�ֵ�ͳ���
    IT itr = split(r + 1), itl = split(l); // �ָ����� [l, r]
    for (; itl != itr; ++itl)
        v.push_back(make_pair(itl->v, itl->r - itl->l + 1)); // �ռ�������Ϣ
    sort(v.begin(), v.end()); // ��ֵ����
    for (auto p : v) {
        k -= p.second; // ��ȥ��ǰֵ�ĸ���
        if (k <= 0) return p.first; // ��� k <= 0�����ص�ǰֵ
    }
    return -1; // δ�ҵ�
}

// �����ݺ��������� a^b % mod
int powmod(int a, int b, int mod) {
    int res = 1;
    a %= mod;
    for (; b; b >>= 1) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}

// �������� [l, r] ��ÿ������ x �η��ĺͣ�ģ mod
int sum(int l, int r, int x, int mod) {
    int res = 0;
    IT itr = split(r + 1), itl = split(l); // �ָ����� [l, r]
    for (; itl != itr; ++itl)
        res = (res + (itl->r - itl->l + 1) * powmod(itl->v, x, mod)) % mod; // �ۼ�ÿ������Ĺ���
    return res;
}

signed main() {
    int n, m, seed, vmax;
    cin >> n >> m >> seed >> vmax;

    // �����������
    auto rnd = [&]() {
        int ret = seed;
        seed = (seed * 7 + 13) % 1000000007;
        return ret;
    };

    // ��ʼ������
    for (int i = 1; i <= n; ++i) {
        int a = rnd() % vmax + 1; // ���������
        s.insert(Node(i, i, a)); // ��������ڵ�
    }

    // ���� m ������
    for (int i = 1; i <= m; ++i) {
        int op = rnd() % 4 + 1; // ������ɲ�������
        int l = rnd() % n + 1; // �������������˵�
        int r = rnd() % n + 1; // ������������Ҷ˵�
        if (l > r)
            swap(l, r); // ȷ�� l <= r

        int x, y;
        if (op == 3) {
            x = rnd() % (r - l + 1) + 1; // ������ɵ� k С�� k
        } else {
            x = rnd() % vmax + 1; // ������� x
        }

        if (op == 4) {
            y = rnd() % vmax + 1; // �������ģ�� y
        }

        // ���ݲ������͵�����Ӧ����
        if (op == 1) {
            add(l, r, x); // �����
        } else if (op == 2) {
            assign(l, r, x); // ���丳ֵ
        } else if (op == 3) {
            cout << kth(l, r, x) << endl; // ����� k С
        } else if (op == 4) {
            cout << sum(l, r, x, y) << endl; // ���� x �η���
        }
    }

    return 0;
}
