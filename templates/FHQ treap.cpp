// FHQ-Treap��ʹ�ô�Ƶѹ����C++��
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
int key_count[MAXN];
int ls[MAXN];
int rs[MAXN];
int size[MAXN];
double priority[MAXN];

void up(int i) {
    size[i] = size[ls[i]] + size[rs[i]] + key_count[i];
}

//����ֵ������
//���ﵱǰ������i�ڵ�  <=num��Ŀǰ����Ľڵ���l  >num��Ŀǰ����Ľڵ���r
//���ѹ�������������ͷ�����ʵ������Ҫ  ��Ҫ���ǵ�ǰ�����Ľڵ�
void split(int l, int r, int i, int num) {
    if (i == 0) {
        //��ʾ�Ѿ���·������
        rs[l] = ls[r] = 0;
        //��ʾ�������Ѿ����
    } else {
        if (key[i] <= num) {
            //��ǰֵС��num  ʹ���ҽڵ�
            //<=num�������������Ľڵ���  ֮ǰ�ڵ���ҽڵ�
            //����Ҫ���ڵ�i����Ϊ l���ҽڵ�
            //����ǰ����һ���ڵ������
            //<=num��Ŀǰ����Ľڵ�  ����Ϊi  >num�Ĳ���  �����Ľڵ���i���ҽڵ�
            rs[l] = i;
            split(i, r, rs[i], num);
        } else {
            ls[r] = i;
            split(l, i, ls[i], num);
        }
        up(i);
    }
}

//�ϲ�������
//l��ʾ������ǰ������ͷ��� r��ʾ������ǰ������ͷ���
//���ص�����l��rΪͷ���������ϲ����ͷ���
int merge(int l, int r) {
    if (l == 0 || r == 0) {
        //ֻҪ��һ���ڵ���0  ��ô�Ͳ���Ҫ��������
        //ֱ�ӷ���l+r  ��Ϊ�϶���һ����0  �൱�ڷ��صľ���l����r
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        //���������ǰ�ڵ�����ȼ���  ��ô������ǰͷ������ұ߻�
        //��ʱ�������ҽڵ�Ӧ����  ��ԭ�����ҽڵ�Ϊͷ������  ��   ��������ǰ�ڵ�Ϊͷ������  �ϲ����ͷ���
        //����һ������֪��l��r�ϲ����ͷ�����l
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

//������iΪ�׵�������  Ȩֵ��num�Ľڵ���  û���ҵ�����0
int find(int i, int num) {
    if (i == 0) {
        return 0;
    }
    if (key[i] == num) {
        return i;
    } else if (key[i] > num) {
        return find(ls[i], num);
    } else {
        return find(rs[i], num);
    }
}

//�ı��Ƶ  ����change
void changeCount(int i, int num, int change) {
    if (key[i] == num) {
        key_count[i] += change;
    } else if (key[i] > num) {
        changeCount(ls[i], num, change);
    } else {
        changeCount(rs[i], num, change);
    }
    up(i);
}

void add(int num) {
    if (find(head, num) != 0) {
        changeCount(head, num, 1);
    } else {
        split(0, 0, head, num);
        //���Ƚ�������num��Ϊ <=num  �� >num��
        //right[0] ��<num  ͷ���  ��Ϊû��num
        //left[0]  ��>num  ͷ���
        key[++cnt] = num;
        key_count[cnt] = size[cnt] = 1;
        priority[cnt] = (double)rand() / RAND_MAX;
        //����һ���½ڵ�  ���ýڵ���<num�����ϲ�  Ȼ���>num�����ϲ�
        head = merge(merge(rs[0], cnt), ls[0]);
    }
}

void remove(int num) {
    int i = find(head, num);
    if (i != 0) {
        if (key_count[i] > 1) {
            changeCount(head, num, -1);
        } else {
            //����Ҫɾ���ڵ�
            split(0, 0, head, num);
            //��������num����  �õ������������ڵ�
            //��<=num��������  num-1  ����   һ������� <=num-1  �� num
            //��ʱ��  <=num-1  �� >num �����ϲ�����
            int lm = rs[0];
            int r = ls[0];
            split(0, 0, lm, num - 1);
            int l = rs[0];
            head = merge(l, r);
        }
    }
}

int small(int i, int num) {
    if (i == 0) {
        return 0;
    }
    if (key[i] >= num) {
        return small(ls[i], num);
    } else {
        return size[ls[i]] + key_count[i] + small(rs[i], num);
    }
}

int getRank(int num) {
    return small(head, num) + 1;
}

int index(int i, int x) {
    if (size[ls[i]] >= x) {
        return index(ls[i], x);
    } else if (size[ls[i]] + key_count[i] < x) {
        return index(rs[i], x - size[ls[i]] - key_count[i]);
    }
    return key[i];
}

int index(int x) {
    return index(head, x);
}

int pre(int i, int num) {
    if (i == 0) {
        return INT_MIN;
    }
    if (key[i] >= num) {
        return pre(ls[i], num);
    } else {
        return max(key[i], pre(rs[i], num));
    }
}

int pre(int num) {
    return pre(head, num);
}

int post(int i, int num) {
    if (i == 0) {
        return INT_MAX;
    }
    if (key[i] <= num) {
        return post(rs[i], num);
    } else {
        return min(key[i], post(ls[i], num));
    }
}

int post(int num) {
    return post(head, num);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    int n;
    cin >> n;
    for (int i = 1, op, x; i <= n; i++) {
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
