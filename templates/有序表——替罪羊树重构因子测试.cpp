// ƽ������Ӱ������������ʵ��
// һ����max(�����ڵ����������ڵ���) > ƽ������ * �����ڵ������ͻᷢ���ع�
// ƽ�����ӷ�Χ��(0.5, 1.0)������������
// ƽ�����ӵ���0.5ʱ�����ߺ�С����ѯЧ�ʸߣ������ع�������Ƶ��
// ƽ�����ӵ���1.0ʱ���ع���ȫ���������������ߺܴ󣬲�ѯЧ�ʵ�
// ��֤��ѯЧ�ʡ�ͬʱ��֤�ع��Ľڵ��������࣬0.7Ϊ��õ�ƽ������
// �Ᵽ֤�˲�ѯЧ�ʣ���Ϊ���߼�����O(log n)
// ͬʱ�ع�������ʱ�����ʣ����ε����ľ�̯����ΪO(log n)
#include <bits/stdc++.h>
using namespace std;

// ȫ�ֱ���
double ALPHA = 0.7;
int maxx = 10000;
int cost = 0;
int head = 0;
int cnt = 0;
const int MAXN = 100001;
int key[MAXN];
int occurrence[MAXN]; // �޸�Ϊ occurrence
int ls[MAXN];
int rs[MAXN];
int size[MAXN];
int diff[MAXN];
int collect[MAXN];
int ci = 0;
int top = 0;
int father = 0;
int side = 0;

// ͳ������
int deep(int i) {
    if (i == 0) {
        return 0;
    }
    return max(deep(ls[i]), deep(rs[i])) + 1;
}

// ��ʼ���ڵ�
int init(int num) {
    key[++cnt] = num;
    ls[cnt] = rs[cnt] = 0;
    occurrence[cnt] = size[cnt] = diff[cnt] = 1; // �޸�Ϊ occurrence
    return cnt;
}

// ���½ڵ���Ϣ
void up(int i) {
    size[i] = size[ls[i]] + size[rs[i]] + occurrence[i]; // �޸�Ϊ occurrence
    diff[i] = diff[ls[i]] + diff[rs[i]] + (occurrence[i] > 0 ? 1 : 0); // �޸�Ϊ occurrence
}

// �������
void inorder(int i) {
    if (i != 0) {
        inorder(ls[i]);
        if (occurrence[i] > 0) { // �޸�Ϊ occurrence
            collect[++ci] = i;
        }
        inorder(rs[i]);
    }
}

// ������
int build(int l, int r) {
    if (l > r) {
        return 0;
    }
    int m = (l + r) / 2;
    int h = collect[m];
    ls[h] = build(l, m - 1);
    rs[h] = build(m + 1, r);
    up(h);
    return h;
}

// �ؽ���
void rebuild() {
    if (top != 0) {
        ci = 0;
        inorder(top);
        if (ci > 0) {
            cost += ci; // ͳ���ع��ڵ���
            if (father == 0) {
                head = build(1, ci);
            } else if (side == 1) {
                ls[father] = build(1, ci);
            } else {
                rs[father] = build(1, ci);
            }
        }
    }
}

// �ж��Ƿ�ƽ��
bool balance(int i) {
    return ALPHA * diff[i] >= max(diff[ls[i]], diff[rs[i]]);
}

// ����ڵ�
void add(int i, int f, int s, int num) {
    if (i == 0) {
        if (f == 0) {
            head = init(num);
        } else if (s == 1) {
            ls[f] = init(num);
        } else {
            rs[f] = init(num);
        }
    } else {
        if (key[i] == num) {
            occurrence[i]++; // �޸�Ϊ occurrence
        } else if (key[i] > num) {
            add(ls[i], i, 1, num);
        } else {
            add(rs[i], i, 2, num);
        }
        up(i);
        if (!balance(i)) {
            top = i;
            father = f;
            side = s;
        }
    }
}

// ��������
void add(int num) {
    top = father = side = 0;
    add(head, 0, 0, num);
    rebuild();
}

// ����С�ڵ��ڸ���ֵ�Ľڵ�����
int small(int i, int num) {
    if (i == 0) {
        return 0;
    }
    if (key[i] >= num) {
        return small(ls[i], num);
    } else {
        return size[ls[i]] + occurrence[i] + small(rs[i], num); // �޸�Ϊ occurrence
    }
}

// ��ȡ����
int getRank(int num) { // �޸�Ϊ getRank
    return small(head, num) + 1;
}

// ��ȡ��xС��ֵ
int index(int i, int x) {
    if (size[ls[i]] >= x) {
        return index(ls[i], x);
    } else if (size[ls[i]] + occurrence[i] < x) { // �޸�Ϊ occurrence
        return index(rs[i], x - size[ls[i]] - occurrence[i]); // �޸�Ϊ occurrence
    }
    return key[i];
}

// ��ȡ��xС��ֵ���ⲿ���ã�
int index(int x) {
    return index(head, x);
}

// ��ȡǰ��
int pre(int num) {
    int kth = getRank(num); // �޸�Ϊ getRank
    if (kth == 1) {
        return INT_MIN;
    } else {
        return index(kth - 1);
    }
}

// ��ȡ���
int post(int num) {
    int kth = getRank(num + 1); // �޸�Ϊ getRank
    if (kth == size[head] + 1) {
        return INT_MAX;
    } else {
        return index(kth);
    }
}

// ɾ���ڵ�
void remove(int i, int f, int s, int num) {
    if (key[i] == num) {
        occurrence[i]--; // �޸�Ϊ occurrence
    } else if (key[i] > num) {
        remove(ls[i], i, 1, num);
    } else {
        remove(rs[i], i, 2, num);
    }
    up(i);
    if (!balance(i)) {
        top = i;
        father = f;
        side = s;
    }
}

// ɾ������
void remove(int num) {
    if (getRank(num) != getRank(num + 1)) { // �޸�Ϊ getRank
        top = father = side = 0;
        remove(head, 0, 0, num);
        rebuild();
    }
}

// �����
void clear() {
    fill(key + 1, key + cnt + 1, 0);
    fill(occurrence + 1, occurrence + cnt + 1, 0); // �޸�Ϊ occurrence
    fill(ls + 1, ls + cnt + 1, 0);
    fill(rs + 1, rs + cnt + 1, 0);
    fill(size + 1, size + cnt + 1, 0);
    fill(diff + 1, diff + cnt + 1, 0);
    cnt = 0;
    head = 0;
}

int main() {
    ALPHA = 0.72; // ����ƽ������
    int max_value = 10000; // �޸ı�����Ϊ max_value �Ա����� max ������ͻ
    cout << "���Կ�ʼ" << endl;
    cost = 0; // ����ع��ڵ����
    for (int num = 1; num <= max_value; num++) {
        add(num);
    }
    cout << "�������� : " << "1~" << max_value << endl;
    cout << "ƽ������ : " << ALPHA << endl;
    cout << "���ĸ߶� : " << deep(head) << endl;
    cout << "�ع��ڵ� : " << cost << endl;
    cout << "���Խ���" << endl;
    clear();
    return 0;
}
