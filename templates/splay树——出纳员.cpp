// ���Ƶĳ���Ա(C++��)
// ���нˮΪlimit��һ��Ա��нˮ����limit��Ա������ְ��ʵ���������ֲ���
// I x : ����Ա����ʼнˮ��x�����x����limit����Ա��������ְ��ȻҲ������ְ
// A x : ����Ա����нˮ������x
// S x : ����Ա����нˮ����ȥx��һ����Ա������limit��ô�ͻ���ְ
// F x : ��ѯ��x��Ĺ��ʣ����x���ڵ�ǰԱ����������ӡ-1
// ���в�����ɺ󣬴�ӡ�ж���Ա���ڲ����ڼ��뿪�˹�˾
// �������� : https://www.luogu.com.cn/problem/P1486
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300001;

int head = 0;
int cnt = 0;
int key[MAXN];
int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
int size[MAXN];
int limit;
int change = 0;//ȫ�ֱ��� ��¼Ӱ��
int enter = 0;

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

void add(int num) {
    key[++cnt] = num;
    size[cnt] = 1;
    if (head == 0) {
        head = cnt;
    } else {
        int f = 0, i = head, son = 0;
        while (i != 0) {
            f = i;
            if (key[i] <= num) {
                son = 1;
                i = rs[i];
            } else {
                son = 0;
                i = ls[i];
            }
        }
        if (son == 1) {
            rs[f] = cnt;
        } else {
            ls[f] = cnt;
        }
        fa[cnt] = f;
        splay(cnt, 0);
    }
}

int index(int x) {
    int i = head, last = head;
    while (i != 0) {
        last = i;
        if (size[ls[i]] >= x) {
            i = ls[i];
        } else if (size[ls[i]] + 1 < x) {
            x -= size[ls[i]] + 1;
            i = rs[i];
        } else {
            i = 0;
        }
    }
    splay(last, 0);
    return key[last];
}

void departure() {
    int num = limit - change - 1;
    int i = head, ans = 0;
    while (i != 0) {
        if (key[i] > num) {
            ans = i;
            i = ls[i];
        } else {
            i = rs[i];
        }
    }
    if (ans == 0) {
        head = 0;
    } else {
        splay(ans, 0);
        ls[head] = 0;
        up(head);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, x;
    char op;
    cin >> n >> limit;
    for (int i = 1; i <= n; i++) {
        cin >> op >> x;
        if (op == 'I') {
            if (x >= limit) {
                enter++;
                add(x - change);
            }
        } else if (op == 'A') {
            change += x;
        } else if (op == 'S') {
            change -= x;
            departure();
        } else if (op == 'F') {
            if (x > size[head]) {
                cout << -1 << endl;
            } else {
                cout << index(size[head] - x + 1) + change << endl;
            }
        }
    }
    cout << enter - size[head] << endl;
    return 0;
}
