// ���(C++��)
// ����һ������Ϊn�����У�������1��2��3...n��ɣ�ʵ���������ֲ���
// Top s      : ����s�ƶ��������
// Bottom s   : ����s�ƶ������ұ�
// Insert s t : ����sλ�ü���Ϊrank�������ƶ���rank+tλ��
// Ask s      : ��ѯ����s����ж�������
// Query s    : ��ѯ�������ҵ�sλ������
// ���в�����֤���ǺϷ���
// �������� : https://www.luogu.com.cn/problem/P2596
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 80005;

int head = 0;
int cnt = 0;
int num[MAXN];
int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
int size[MAXN];
int pos[MAXN];

void up(int i) {
    size[i] = size[ls[i]] + size[rs[i]] + 1;
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
    int f = fa[i], g = fa[f];
    while (f != goal) {
        if (g != goal) {
            if (lr(i) == lr(f)) {
                rotate(f);
            } else {
                rotate(i);
            }
        }
        rotate(i);
        f = fa[i];
        g = fa[f];
    }
    if (goal == 0) {
        head = i;
    }
}

int find(int rank) {
    int i = head;
    while (i != 0) {
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

void add(int s) {
    num[++cnt] = s;
    pos[s] = cnt;
    size[cnt] = 1;
    fa[cnt] = head;
    rs[head] = cnt;
    splay(cnt, 0);
}

int ask(int s) {
    int i = pos[s];
    splay(i, 0);
    return size[ls[i]];
}

int query(int s) {
    int i = find(s);
    splay(i, 0);
    return num[i];
}

// ��������Ϊa�Ľڵ㣬�ƶ�����������Ϊb��λ��
// ע��a������1��nλ�ã�bҲ���
// ��Ϊ1λ�ú�nλ����ǰ������Ԥ��ֵ����Զ�����޸�
void move(int a, int b) {
    int l = find(a - 1);
    int r = find(a + 1);
    splay(l, 0);
    splay(r, l);
    int i = ls[r];
    ls[r] = 0;
    up(r);
    up(l);
    l = find(b - 1);
    r = find(b);
    splay(l, 0);
    splay(r, l);
    ls[r] = i;
    fa[i] = r;
    up(r);
    up(l);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    add(0);//��ͷ��һ��
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        add(x);
    }
    add(n + 1);//��β��һ��
    n = n + 2;
    for (int i = 1, s, t, rank; i <= m; i++) {
        string op;
        cin >> op >> s;
        rank = ask(s) + 1;
        if (op == "Top") {
            // ��Ϊ��������׼��ֵ�����Կ�ͷ����������2��λ��
            move(rank, 2);
        } else if (op == "Bottom") {
            // ��Ϊ�����Ҳ��׼��ֵ�����Խ�β����������n-1��λ��
            move(rank, n - 1);
        } else if (op == "Insert") {
            cin >> t;
            move(rank, rank + t);
        } else if (op == "Ask") {
            // rank����ǰ���ֵ���������Ϊ��������׼��ֵ
            // ����������ʵ��rank-1����ĿҪ����С�ڵ�������������rank - 2
            cout << rank - 2 << endl;
        } else {
            // ��Ϊ��������׼��ֵ�����Բ�s+1��������
            cout << query(s + 1) << endl;
        }
    }
    return 0;
}
