// AVL����ʵ��(java��)
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
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>
using namespace std;
const int MAXN = 100001;

int cnt = 0;//���ڸ���ڵ���
int head = 0;//��������ͷ���  ����ڵ��ǿ��Ա仯��  �����������̬����
int key[MAXN];//�ڵ��Ȩֵ
int height[MAXN];//�ڵ������  ���Һ������ߵ����ֵ����һ
int ls[MAXN];
int rs[MAXN];//���Һ��ӽڵ���  ע�����Ҳ������ֵ֮��ͱ��ֲ����   �����������̬������Ӧ�仯
int key_count[MAXN];//ͳ������ڵ��ϵ����ֳ����˶��ٴ�  ��Ƶͳ��
int sz[MAXN];//�Ըýڵ�Ϊ�׵��������������ֵĴ�Ƶ֮��

void up(int i) {
    sz[i] = sz[ls[i]] + sz[rs[i]] + key_count[i];
    height[i] = max(height[ls[i]], height[rs[i]]) + 1;
}

//������ Ŀ�İ���̬������AVL��������AVL��
//�����������ǽ���iΪ�׵�����������  ��������������ͷ���
int leftRotate(int i) {
    int r = rs[i];
    rs[i] = ls[r];
    ls[r] = i;
    up(i);
    up(r);
    return r;
}

int rightRotate(int i) {
    int l = ls[i];
    ls[i] = rs[l];
    rs[l] = i;
    up(i);
    up(l);
    return l;
}

//������ڵ�Ϊ�׵���������  ʹ֮��Υ��AVL���Ķ���  �����Һ������߲�����һ
//�����ص����ú��ͷ���
int maintain(int i) {
    int lh = height[ls[i]];
    int rh = height[rs[i]];
    if (lh - rh > 1) {
        if (height[ls[ls[i]]] >= height[rs[ls[i]]]) {
            i = rightRotate(i);
        } else {
            ls[i] = leftRotate(ls[i]);
            i = rightRotate(i);
        }
    } else if (rh - lh > 1) {
        if (height[rs[rs[i]]] >= height[ls[rs[i]]]) {
            i = leftRotate(i);
        } else {
            rs[i] = rightRotate(rs[i]);
            i = leftRotate(i);
        }
    }
    return i;
}

//����i�ڵ�Ϊ�׵������ϼ���һ��num  �����ص��������ͷ���
int add(int i, int num) {
    if (i == 0) {
        //��ʾ���ǵ�һ�γ���
        key[++cnt] = num;
        key_count[cnt] = sz[cnt] = height[cnt] = 1;
        //�½�һ���ڵ�
        return cnt;
    }
    if (key[i] == num) {
        key_count[i]++;
    } else if (key[i] > num) {
        ls[i] = add(ls[i], num);
    } else {
        rs[i] = add(rs[i], num);
    }
    up(i);
    //ÿ�ζ�Ҫ���ϻ���  ȷ��������ȷ
    return maintain(i);
    //�������Ľṹ  ʹ֮ƽ��
}

//����һ��ֵΪnum������
void add(int num) {
    head = add(head, num);
}

//��ѯ��i�ڵ�Ϊ�׵�������С��num�����ֵ�����
int getRank(int i, int num) {
    if (i == 0) {
        return 0;
    }
    if (key[i] >= num) {
        return getRank(ls[i], num);
    } else {
        return sz[ls[i]] + key_count[i] + getRank(rs[i], num);
    }
}

//��ѯnum�����������  Ҳ�������б���С������������һ
int getRank(int num) {
    return getRank(head, num) + 1;
}

int removeMostLeft(int i, int mostLeft) {
    if (i == mostLeft) {
        return rs[i];
    } else {
        ls[i] = removeMostLeft(ls[i], mostLeft);
        up(i);
        return maintain(i);
    }
}

//��ѯ��i�ڵ�Ϊ�׵�������ɾȥһ��num
int remove(int i, int num) {
    if (key[i] < num) {
        rs[i] = remove(rs[i], num);
    } else if (key[i] > num) {
        ls[i] = remove(ls[i], num);
    } else {
        if (key_count[i] > 1) {
            key_count[i]--;
        } else {
            if (ls[i] == 0 && rs[i] == 0) {
                return 0;
            } else if (ls[i] != 0 && rs[i] == 0) {
                i = ls[i];
            } else if (ls[i] == 0 && rs[i] != 0) {
                i = rs[i];
            } else {
                int mostLeft = rs[i];
                while (ls[mostLeft] != 0) {
                    mostLeft = ls[mostLeft];
                }
                rs[i] = removeMostLeft(rs[i], mostLeft);
                ls[mostLeft] = ls[i];
                rs[mostLeft] = rs[i];
                i = mostLeft;
            }
        }
    }
    up(i);
    return maintain(i);
}

//������ɾ������num
void remove(int num) {
    if (getRank(num) != getRank(num + 1)) {
        //��ʾ������ִ���
        head = remove(head, num);
    }
}

int index(int i, int x) {
    if (sz[ls[i]] >= x) {
        return index(ls[i], x);
    } else if (sz[ls[i]] + key_count[i] < x) {
        return index(rs[i], x - sz[ls[i]] - key_count[i]);
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

void clear() {
    memset(key + 1, 0, cnt * sizeof(int));
    memset(height + 1, 0, cnt * sizeof(int));
    memset(ls + 1, 0, cnt * sizeof(int));
    memset(rs + 1, 0, cnt * sizeof(int));
    memset(key_count + 1, 0, cnt * sizeof(int));
    memset(sz + 1, 0, cnt * sizeof(int));
    cnt = 0;
    head = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
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
    clear();
    return 0;
}