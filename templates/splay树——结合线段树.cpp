// ά������(C++��)
// ��ʼʱ����һ�����У�ʵ���������ֲ���
// INSERT posi tot ...  : �ڵ�posi������֮�󣬲��볤��Ϊtot�����飬��...����
// DELETE posi tot      : �ӵ�posi�����ֿ�ʼ��ɾ������Ϊtot�Ĳ���
// MAKE-SAME posi tot c : �ӵ�posi�����ֿ�ʼ������Ϊtot�Ĳ��֣�ֵ�����ó�c
// REVERSE posi tot     : �ӵ�posi�����ֿ�ʼ����ת����Ϊtot�Ĳ���
// GET-SUM posi tot     : �ӵ�posi�����ֿ�ʼ����ѯ����Ϊtot�Ĳ��ֵ��ۼӺ�
// MAX-SUM              : ��ѯ���������У��ǿ������������ۼӺ�
// �κ�ʱ�����뱣֤������һ�������������У��������в������Ϸ�
// �������������ܶ࣬�����κ�ʱ�������������5 * 10^5������ʹ���ܿռ�Ҫ�͸������й�
// �������� : https://www.luogu.com.cn/problem/P2042
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
const int INF = 1000000001;

int head = 0;
int arr[MAXN];
int num[MAXN];
int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
int size[MAXN];
// ����������ÿռ���
int space[MAXN], si;
// ά�������ۼӺ���Ϣ
int sum[MAXN];
// ά����������������ۼӺ���Ϣ��Ҫ����Ϊ��
int all[MAXN];
// ά������ǰ׺����ۼӺ���Ϣ�����Կ�
int pre[MAXN];
// ά�������׺����ۼӺ���Ϣ�����Կ�
int suf[MAXN];
// ��������Ϣ�������Ƿ���������ֵ
bool update[MAXN];
// ��������Ϣ�����������������ֵ�����ó���ʲô
int change[MAXN];
// ��������Ϣ�������Ƿ����˷�ת
bool rev[MAXN];

void up(int i) {
    int l = ls[i], r = rs[i];
    size[i] = size[l] + size[r] + 1;
    sum[i] = sum[l] + sum[r] + num[i];
    all[i] = max(max(all[l], all[r]), suf[l] + num[i] + pre[r]);
    pre[i] = max(pre[l], sum[l] + num[i] + pre[r]);
    suf[i] = max(suf[r], suf[l] + num[i] + sum[r]);
}

int lr(int i) {
    return rs[fa[i]] == i ? 1 : 0;
}

void rotate(int i) {
    int f = fa[i], g = fa[f], soni = lr(i), sonf = lr(f);
    if (soni == 1) {
        rs[f] = ls[i];
        if (rs[f] != 0) {
            fa[rs[f]] = f;
        }
        ls[i] = f;
    } else {
        ls[f] = rs[i];
        if (ls[f] != 0) {
            fa[ls[f]] = f;
        }
        rs[i] = f;
    }
    if (g != 0) {
        if (sonf == 1) {
            rs[g] = i;
        } else {
            ls[g] = i;
        }
    }
    fa[f] = i;
    fa[i] = g;
    up(f);
    up(i);
}

void splay(int i, int goal) {
    while (fa[i] != goal) {
        int f = fa[i], g = fa[f];
        if (g != goal) {
            if (lr(i) == lr(f)) {
                rotate(f);
            } else {
                rotate(i);
            }
        }
        rotate(i);
    }
    if (goal == 0) {
        head = i;
    }
}

void setValue(int i, int val) {
    if (i != 0) {
        update[i] = true;
        change[i] = val;
        num[i] = val;
        sum[i] = size[i] * val;
        all[i] = max(sum[i], val);
        pre[i] = max(sum[i], 0);
        suf[i] = max(sum[i], 0);
    }
}

void setReverse(int i) {
    if (i != 0) {
        swap(pre[i], suf[i]);
        rev[i] ^= 1;
    }
}

void down(int i) {
    if (update[i]) {
        setValue(ls[i], change[i]);
        setValue(rs[i], change[i]);
        update[i] = false;
    }
    if (rev[i]) {
        swap(ls[i], rs[i]);
        setReverse(ls[i]);
        setReverse(rs[i]);
        rev[i] = false;
    }
}

int init(int val) {
    int i = space[si--];
    size[i] = 1;
    num[i] = sum[i] = all[i] = val;
    pre[i] = suf[i] = max(val, 0);
    fa[i] = ls[i] = rs[i] = 0;
    update[i] = rev[i] = false;
    return i;
}

int build(int l, int r) {
    int mid = (l + r) / 2;
    int root = init(arr[mid]);
    if (l < mid) {
        ls[root] = build(l, mid - 1);
        fa[ls[root]] = root;
    }
    if (mid < r) {
        rs[root] = build(mid + 1, r);
        fa[rs[root]] = root;
    }
    up(root);
    return root;
}

int find(int rank) {
    int i = head;
    while (i != 0) {
        down(i);
        if (size[ls[i]] + 1 == rank) {
            return i;
        } else if (size[ls[i]] >= rank) {
            i = ls[i];
        } else {
            rank -= size[ls[i]] + 1;
            i = rs[i];
        }
    }
    return 0;
}

void insert(int rank, int n) {
    if (rank == 0) {
        head = build(1, n);
    } else {
        int l = find(rank);
        int r = find(rank + 1);
        splay(l, 0);
        splay(r, l);
        ls[r] = build(1, n);
        fa[ls[r]] = r;
        up(r);
        up(l);
    }
}

void recycle(int i) {
    if (i != 0) {
        space[++si] = i;
        recycle(ls[i]);
        recycle(rs[i]);
    }
}

void remove(int rank, int n) {
    int l = find(rank - 1);
    int r = find(rank + n);
    splay(l, 0);
    splay(r, l);
    recycle(ls[r]);
    ls[r] = 0;
    up(r);
    up(l);
}

void reset(int rank, int n, int val) {
    int l = find(rank - 1);
    int r = find(rank + n);
    splay(l, 0);
    splay(r, l);
    setValue(ls[r], val);
    up(r);
    up(l);
}

void reverse(int rank, int n) {
    int l = find(rank - 1);
    int r = find(rank + n);
    splay(l, 0);
    splay(r, l);
    setReverse(ls[r]);
    up(r);
    up(l);
}

int querySum(int rank, int n) {
    int l = find(rank - 1);
    int r = find(rank + n);
    splay(l, 0);
    splay(r, l);
    return sum[ls[r]];
}

int queryMax() {
    return all[head];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    si = MAXN - 1;
    for (int i = 1; i <= si; i++) {
        space[i] = i;
    }
    arr[1] = arr[n + 2] = all[0] = -INF;
    for (int i = 1, j = 2; i <= n; i++, j++) {
        cin >> arr[j];
    }
    insert(0, n + 2);
    string op;
    for (int i = 0; i < m; i++) {
        cin >> op;
        if (op == "MAX-SUM") {
            cout << queryMax() << endl;
        } else {
            int pos, len, c;
            cin >> pos >> len;
            pos++;
            if (op == "INSERT") {
                for (int j = 1; j <= len; j++) {
                    cin >> arr[j];
                }
                insert(pos, len);
            } else if (op == "DELETE") {
                remove(pos, len);
            } else if (op == "MAKE-SAME") {
                cin >> c;
                reset(pos, len, c);
            } else if (op == "REVERSE") {
                reverse(pos, len);
            } else if (op == "GET-SUM") {
                cout << querySum(pos, len) << endl;
            }
        }
    }
    return 0;
}
