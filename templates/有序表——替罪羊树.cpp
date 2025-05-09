// ����������ʵ��(C++��)
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
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <cstring>

using namespace std;

const double ALPHA = 0.7;
const int MAXN = 100001;
int head = 0;
int cnt = 0;//��������¼ӽڵ���
int key[MAXN];
int key_count[MAXN];//����ͳ�Ƹýڵ�ĳ��ִ���
int ls[MAXN];//��¼���ӵı��
int rs[MAXN];//��¼�Һ��ӵı��
int size[MAXN];//��¼�Ըýڵ�Ϊͷ�����ڵ�������С
int diff[MAXN];//��¼�Ըýڵ�Ϊͷ�����ϲ�ͬ�������������
int collect[MAXN];//�����������
int ci;//�����������������ı��
int top;// ���Ϸ��Ĳ�ƽ��ڵ�
int father;// top�ĸ��ڵ�  ͳ��������׽ڵ�����Ϊ���ؽ���
int side;// top�Ǹ��ڵ��ʲô���ӣ�1�������ӣ�2�����Һ���

//����һ���ڵ�  ��ʼ���ýڵ���Ϣ  ���ظý����
int init(int num) {
    key[++cnt] = num;
    ls[cnt] = rs[cnt] = 0;
    key_count[cnt] = size[cnt] = diff[cnt] = 1;
    return cnt;
}

//�����Һ��ӵĽڵ����ϻ���
void up(int i) {
    size[i] = size[ls[i]] + size[rs[i]] + key_count[i];
    diff[i] = diff[ls[i]] + diff[rs[i]] + (key_count[i] > 0 ? 1 : 0);
}

//��¼��������ı��
void inorder(int i) {
    //�������������  ����  �����
    if (i != 0) {
        inorder(ls[i]);
        if (key_count[i] > 0) {
            //ֻҪ��ǰ�ڵ���ִ�����ֹһ��
            //��Ϊ������ɾ��������ʱ��  ����ڵ������Ϊ0��  ���ع�����ʱ��Ż�ɾ��
            collect[++ci] = i;
        }
        inorder(rs[i]);
    }
}

//������  ��ʾ����������õ�����������ı��ȫ��������һ�úϷ�ƽ�����
//ͷ���һ����collect������һ��λ�õĽڵ�
//���ص�ǰ����������ͷ���
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

//�ؽ���
//ÿ�����ӻ���ɾ��������  �������ǲ�ƽ���
//��ôÿ�ζ�����Ҫ����ͽڵ����ϼ��
void rebuild() {
    if (top != 0) {
        //�ҵ���������ĵ�
        ci = 0;
        inorder(top);
        //������� ֻҪci=0  ˵���Ϸ�  ��ô�Ͳ���Ҫ�ع���
        if (ci > 0) {
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

//�ж�һ�����Ƿ�ƽ��  �����ж�ƽ��ƽ���Ǹ��ݽ�����  ���ǽڵ��Ƶ����
bool balance(int i) {
    return ALPHA * diff[i] >= max(diff[ls[i]], diff[rs[i]]);
}

//��ʾҪ����һ������num  �Ѿ������˽ڵ�i
//����ڵ�i�Ǵ�f�ڵ�ת������  Ҳ���Ǹ��ڵ�ת������
//s��ʾ�ǴӸ��ڵ�����ұ�ת������
void add(int i, int f, int s, int num) {
    if (i == 0) {
        //��ʾ���num ��ǰ������  ��ô����һ���ڵ�
        if (f == 0) {
            //���������ǵ�һ���� ��ô�൱�ڽ���ͷ�ڵ�
            head = init(num);
        } else if (s == 1) {
            //������������ڸ��׽ڵ����ұ�  �����ϸ��׽ڵ�ĺ�����Ϣ
            ls[f] = init(num);
        } else {
            rs[f] = init(num);
        }
    } else {
        //���ڻ������ж��Ƿ����
        if (key[i] == num) {
            //˵�����������ǰ���ֹ�  ���Ӵ�Ƶ
            key_count[i]++;
        } else if (key[i] > num) {
            add(ls[i], i, 1, num);
        } else {
            add(rs[i], i, 2, num);
        }
        up(i);
        //ͳ�Ƶ�ǰͷ�����Ϣ
        if (!balance(i)) {
            top = i;
            father = f;
            side = s;
        }
    }
}

//����һ������num
void add(int num) {
    top = father = side = 0;//�������ú���Щֵ
    add(head, 0, 0, num);
    rebuild();
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

int pre(int num) {
    int kth = getRank(num);
    if (kth == 1) {
        return INT_MIN;
    } else {
        return index(kth - 1);
    }
}

int post(int num) {
    int kth = getRank(num + 1);
    if (kth == size[head] + 1) {
        return INT_MAX;
    } else {
        return index(kth);
    }
}

void remove(int i, int f, int s, int num) {
    if (key[i] == num) {
        key_count[i]--;
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

void remove(int num) {
    if (getRank(num) != getRank(num + 1)) {
        top = father = side = 0;
        remove(head, 0, 0, num);
        rebuild();
    }
}

void clear() {
    memset(key, 0, sizeof(key));
    memset(key_count, 0, sizeof(key_count));
    memset(ls, 0, sizeof(ls));
    memset(rs, 0, sizeof(rs));
    memset(size, 0, sizeof(size));
    memset(diff, 0, sizeof(diff));
    cnt = 0;
    head = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {
            add(x);
        } else if (op == 2) {
            remove(x);
        } else if (op == 3) {
            cout << getRank(x) << "\n";
        } else if (op == 4) {
            cout << index(x) << "\n";
        } else if (op == 5) {
            cout << pre(x) << "\n";
        } else {
            cout << post(x) << "\n";
        }
    }
    clear();
    return 0;
}
