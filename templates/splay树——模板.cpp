// Splay����ʵ�֣����ô�Ƶѹ����C++��
// ʵ��һ�ֽṹ��֧�����²�����Ҫ�󵥴ε��õ�ʱ�临�Ӷ�O(log n)
// 1������x���ظ�����������Ƶ
// 2��ɾ��x������ж����ֻɾ��һ��
// 3����ѯx��������x������Ϊ����xС�����ĸ���+1
// 4����ѯ����������Ϊx����
// 5����ѯx��ǰ����x��ǰ��Ϊ��С��x�������������������ڷ���������Сֵ
// 6����ѯx�ĺ�̣�x�ĺ��Ϊ������x��������С�����������ڷ����������ֵ
// ���в����Ĵ��� <= 10^5
// -10^7 <= x <= +10^7
// �������� : https://www.luogu.com.cn/problem/P3369
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;

int head = 0;
int cnt = 0;
int key[MAXN];
int fa[MAXN];
int ls[MAXN];
int rs[MAXN];
int size[MAXN];

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

//�������ı�������ȷ��  ֻ��ʹ������ƽ��  �������Ƕ�ÿ����ѯ�����������splay
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

// ���������ҵ���������Ϊrank�Ľڵ㣬���ؽڵ���
// �������������ĿҪ��Ĳ�ѯ��������Ϊ�ڲ�����ʹ��
// Ϊʲô�÷������������������
// ��Ϊremove����ʹ�ø÷���ʱ��Ҫ��find���������
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

void add(int num) {
    key[++cnt] = num;
    size[cnt] = 1;//�����ڵ�
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
        fa[cnt] = f;//����������Ϣ
        splay(cnt, 0);
    }
}

int getRank(int num) {
    int i = head, last = head;
    int ans = 0;
    while (i != 0) {
        last = i;
        if (key[i] >= num) {
            i = ls[i];
        } else {
            ans += size[ls[i]] + 1;
            i = rs[i];
        }
    }
    splay(last, 0);
    return ans + 1;
}

int index(int x) {
    int i = find(x);
    splay(i, 0);
    return key[i];
}

int pre(int num) {
    int i = head, last = head;
    int ans = INT_MIN;
    while (i != 0) {
        last = i;
        if (key[i] >= num) {
            i = ls[i];
        } else {
            ans = max(ans, key[i]);
            i = rs[i];
        }
    }
    splay(last, 0);
    return ans;
}

int post(int num) {
    int i = head, last = head;
    int ans = INT_MAX;
    while (i != 0) {
        last = i;
        if (key[i] <= num) {
            i = rs[i];
        } else {
            ans = min(ans, key[i]);
            i = ls[i];
        }
    }
    splay(last, 0);
    return ans;
}

void remove(int num) {
    int kth = getRank(num);
    if (kth != getRank(num + 1)) {
        //��ʾ�ýڵ����
        int i = find(kth);
        splay(i, 0);//���ֲ����е����������Ϊ�˷�ֹ���ݱ��һ������  ���ײ�ѯ
        if (ls[i] == 0) {
            head = rs[i];
        } else if (rs[i] == 0) {
            head = ls[i];
        } else {
            //���������  �����Ҷ���
            int j = find(kth + 1);
            splay(j, i);//��j�ᵽi������
            ls[j] = ls[i];
            fa[ls[j]] = j;
            up(j);
            head = j;
        }
        if (head != 0) {
            fa[head] = 0;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 0, op, x; i < n; i++) {
        cin >> op >> x;
        if (op == 1) {
            add(x);
        } else if (op == 2) {
            remove(x);
        } else if (op == 3) {
            cout << getRank(x) << endl;
        } else if (op == 4) {
            cout << index(x) << endl;
        } else if (op == 5) {
            cout << pre(x) << endl;
        } else {
            cout << post(x) << endl;
        }
    }
    return 0;
}
