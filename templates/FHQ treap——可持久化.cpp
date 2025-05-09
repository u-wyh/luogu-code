// �ɳ־û�ƽ������FHQ-Treapʵ�֣����ô�Ƶѹ����C++��
// ��Ϊһ��ʼ��0�汾������Ϊ������ʵ�����²���������һ������n��
// v 1 x : ����v�汾����������һ��x�������°汾����
// v 2 x : ����v�汾������ɾ��һ��x�������°汾����
// v 3 x : ����v�汾��������ѯx�������������°汾����״��=v�汾״��
// v 4 x : ����v�汾��������ѯ����������Ϊx�����������°汾����״��=v�汾״��
// v 5 x : ����v�汾��������ѯx��ǰ���������°汾����״��=v�汾״��
// v 6 x : ����v�汾��������ѯx�ĺ�̣������°汾����״��=v�汾״��
// ����ʲô������������ĳ��v�汾��������ɺ�õ��°汾��������v�汾����仯
// ���x��ǰ�������ڣ�����-2^31 + 1�����x�ĺ�̲����ڣ�����+2^31 - 1
// 1 <= n <= 5 * 10^5
// -10^9 <= x <= +10^9
// �������� : https://www.luogu.com.cn/problem/P3835
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500001;
const int MAXM = MAXN * 50;//�����������Ҫ��100��

int cnt = 0;
int head[MAXN];//���ڼ�¼ÿһ���汾��ͷ�����ʲô
int key[MAXM];
int ls[MAXM];
int rs[MAXM];
int size[MAXM];
double priority[MAXM];

int copy(int i) {
    ++cnt;
    key[cnt] = key[i];
    ls[cnt] = ls[i];
    rs[cnt] = rs[i];
    size[cnt] = size[i];
    priority[cnt] = priority[i];
    return cnt;
}

void up(int i) {
    size[i] = size[ls[i]] + size[rs[i]] + 1;
}

void split(int l, int r, int i, int num) {
    if (i == 0) {
        rs[l] = ls[r] = 0;
    } else {
        i = copy(i);//ÿ�ο�ʼʱ��Ҫ�½�һ���ڵ�
        if (key[i] <= num) {
            rs[l] = i;
            split(i, r, rs[i], num);
        } else {
            ls[r] = i;
            split(l, i, ls[i], num);
        }
        up(i);
    }
}

int merge(int l, int r) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        l = copy(l);
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        r = copy(r);
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

void add(int v, int i, int num) {
    split(0, 0, i, num);
    int l = rs[0];
    int r = ls[0];
    ls[0] = rs[0] = 0;//ÿ����merge֮ǰҪ��� ���������
    ++cnt;
    key[cnt] = num;
    size[cnt] = 1;
    priority[cnt] = (double)rand() / RAND_MAX;
    //Ϊ�½��Ľڵ���
    head[v] = merge(merge(l, cnt), r);//��¼�ð汾��ͷ���

}

void remove(int v, int i, int num) {
    split(0, 0, i, num);
    int lm = rs[0];
    int r = ls[0];
    split(0, 0, lm, num - 1);
    int l = rs[0];
    int m = ls[0];
    ls[0] = rs[0] = 0;//ÿ��Ҫ��� ���������
    head[v] = merge(merge(l, merge(ls[m], rs[m])), r);//��¼�ð汾��ͷ���
}

int small(int i, int num) {
    if (i == 0) {
        return 0;
    }
    if (key[i] >= num) {
        return small(ls[i], num);
    } else {
        return size[ls[i]] + 1 + small(rs[i], num);
    }
}

int index(int i, int x) {
    if (size[ls[i]] >= x) {
        return index(ls[i], x);
    } else if (size[ls[i]] + 1 < x) {
        return index(rs[i], x - size[ls[i]] - 1);
    } else {
        return key[i];
    }
}

int pre(int i, int num) {
    if (i == 0) {
        return INT_MIN + 1;
    }
    if (key[i] >= num) {
        return pre(ls[i], num);
    } else {
        return max(key[i], pre(rs[i], num));
    }
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int version, op, x;
        cin >> version >> op >> x;
        if (op == 1) {
            add(i, head[version], x);
        } else if (op == 2) {
            remove(i, head[version], x);
        } else {
            //һ�²������ǲ�ѯ����  ����ı����ݽṹ
            //���ǻ���Ҫ��¼һ��ͷ���ı��
            head[i] = head[version];
            if (op == 3) {
                cout << small(head[i], x) + 1 << "\n";
            } else if (op == 4) {
                cout << index(head[i], x) << "\n";
            } else if (op == 5) {
                cout << pre(head[i], x) << "\n";
            } else {
                cout << post(head[i], x) << "\n";
            }
        }
    }
    return 0;
}
