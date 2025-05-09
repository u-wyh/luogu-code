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
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

// �ռ�ʹ�ü���
int cnt = 0;
// ��������ͷ�ڵ���
int head = 0;

// �ڵ��key
int key[MAXN];
// �����߶�  ������Ӻ��Ҷ��ӵĸ߶����ֵ��1
int height[MAXN];

// ��¼���ӵ�key
int ls[MAXN];
// ��¼�Һ��ӵ�key
int rs[MAXN];

// �ڵ�key�ļ���  ֻ�Ǳ�ʾ�ýڵ������  ����������С
int keycount[MAXN];
// ��������������
int size[MAXN];

//���ϵ�ͬһ���ڵ��������Ϣ���������±�ʵ�ֵ�

void up(int i) {
    size[i] = size[ls[i]] + size[rs[i]] + keycount[i];
    //������С��  ������  ����  ������  �Լ��Լ��Ĵ�С
    height[i] = max(height[ls[i]], height[rs[i]]) + 1;
}

// i�ڵ�Ϊͷ��������������������ͷ�ڵ�Ŀռ���
int leftRotate(int i) {
    int r = rs[i];//���Ҷ��ӱ��ͷ
    rs[i] = ls[r];//ԭ��ͷ���Ҷ���  ���  ԭ��ͷ���Ҷ��ӵ������
    ls[r] = i;//ԭ��ͷ���Ҷ��ӵ������ ��� ԭ����ͷ
    //�ɹ�ʵ������

    up(i);
    up(r);
    //��i rΪͷ���������˱仯  ���ϸ�����Ϣ
    return r;
}

// i�ڵ�Ϊͷ��������������������ͷ�ڵ�Ŀռ���  ͬ��
int rightRotate(int i) {
    int l = ls[i];
    ls[i] = rs[l];
    rs[l] = i;
    up(i);
    up(l);
    return l;
}

// ���i�ڵ�Ϊͷ�����Ƿ�Υ��
// ���������ĳ��Υ��������ͽ�����Ӧ����
// ��������ͷ�ڵ�Ŀռ���
int maintain(int i) {
    int lh = height[ls[i]];
    int rh = height[rs[i]];
    //�ռ���������
    if (lh - rh > 1) {
        //������������1����
        if (height[ls[ls[i]]] >= height[rs[ls[i]]]) {
            //LL��  ��������
            i = rightRotate(i);
        } else {
            //LR��  ��������һ��  Ȼ����������
            ls[i] = leftRotate(ls[i]);
            i = rightRotate(i);
        }
    } else if (rh - lh > 1) {
        if (height[rs[rs[i]]] >= height[ls[rs[i]]]) {
            //RR��
            i = leftRotate(i);
        } else {
            //RL
            rs[i] = rightRotate(rs[i]);
            i = leftRotate(i);
        }
    }
    return i;
}

// ��ǰ����i�Žڵ㣬num�������һ���������iΪͷ����  ���򲻻ᵽ��һ��
// ���ṹ�п��ܱ仯������ͷ�ڵ���
int add(int i, int num) {
    if (i == 0) {
        //�����ʾ��δ���ֹ�  �����±��
        key[++cnt] = num;
        keycount[cnt] = size[cnt] = height[cnt] = 1;
        //��ʼ����Ϣ
        return cnt;
    }
    if (key[i] == num) {
        //��������Ϣ�ʹ�Ƶ++  ������ݴ�С��������ת��
        keycount[i]++;
    } else if (key[i] > num) {
        ls[i] = add(ls[i], num);
    } else {
        rs[i] = add(rs[i], num);
    }
    up(i);
    //��iΪͷ������Ϣ�����˱仯   ���ϸ�����Ϣ
    return maintain(i);
    //����ɼ���һ�����ֵ���һ������   ÿ��һ���ڵ㶼��ȥ�ж�һ���Ƿ�Υ��
    //���Υ��Ļ�  �ͻ�������  ����ͷ���ı�
}

// ��������num���ظ�����������Ƶ
void add(int num) {
    head = add(head, num);
}

// ��iΪͷ�����ϣ���numС�������м���
int small(int i, int num) {
    if (i == 0) {
        return 0;
    }
    if (key[i] >= num) {
        //�����ǰֵ��Ҫ��ѯ�����ִ�  ��ôȥ�����
        return small(ls[i], num);
    } else {
        //�������  �������Ĵ�С  ����  ��ǰ�ڵ�Ĵ�Ƶ  Ȼ��ȥ������
        return size[ls[i]] + keycount[i] + small(rs[i], num);
    }
}

// ��ѯnum����������numС�����ָ���+1������num������
int getrank(int num) {
    return small(head, num) + 1;
}

// ��i�Žڵ�Ϊͷ�����ϣ�����ڵ�ı��һ����mostLeft  ���mostleft��֮ǰ������������
// ɾ������ڵ㣬����֤����ƽ���ԣ�����ͷ�ڵ�ı��
int removeMostLeft(int i, int mostLeft) {
    if (i == mostLeft) {
        return rs[i];
    } else {
        ls[i] = removeMostLeft(ls[i], mostLeft);
        //���������·��  ��������
        up(i);
        return maintain(i);
        //��ɾ��һ�����ֵĹ�����  ÿ���ڵ㶼����Ҫ�ж��Ƿ�Υ��
    }
}

// ��ǰ����i�Žڵ㣬��iΪͷ����һ�������1��num
// ���ṹ�п��ܱ仯������ͷ�ڵ���
int remove(int i, int num) {
    if (key[i] < num) {
        rs[i] = remove(rs[i], num);
    } else if (key[i] > num) {
        ls[i] = remove(ls[i], num);
    } else {
        //����֮ǰ ������Ѱ�Ҹ�����
        //�����ҵ�������
        if (keycount[i] > 1) {
            //��Ƶ�㹻  �����������ڵ�
            //������˵�������ڵ���ǲ���ʹ����������  ��ʹ�������key��Ӧ�ļ��ٴλָ�  ���ǻ����һ���µĽڵ���
            keycount[i]--;
        } else {
            if (ls[i] == 0 && rs[i] == 0) {
                //Ҷ�ڵ�
                return 0;
            } else if (ls[i] != 0 && rs[i] == 0) {
                i = ls[i];//ֻ�����ӻ����Һ���  Ҳֱ�Ӹı�ͺ�
            } else if (ls[i] == 0 && rs[i] != 0) {
                i = rs[i];
            } else {
                //�������߶��к���
                int mostLeft = rs[i];
                while (ls[mostLeft] != 0) {
                    mostLeft = ls[mostLeft];
                }
                //��ʱmostleft��������Լ�ֵ����num�Ľڵ�����ϴ���num����Сֵ���ڱ��
                rs[i] = removeMostLeft(rs[i], mostLeft);//�൱�ڽ�����ڵ��rs[i]���������  Ȼ������ڵ�ȥ����i����ڵ��λ��
                ls[mostLeft] = ls[i];
                rs[mostLeft] = rs[i];
                i = mostLeft;
            }
        }
    }
    up(i);
    //���ϸ�������
    return maintain(i);
}

// ɾ������num������ж����ֻɾ��һ��
void remove(int num) {
    if (getrank(num) != getrank(num + 1)) {
        //˵��numһ������
        //getrank������ͳ���ж��ٸ�����С��num  Ȼ���һ
        //����������������Ƿ����
        //��ô���һ�����ֵ�num��num+1������ͬ ˵���������һ������
        head = remove(head, num);
    }
}

int index(int i, int x) {
    if (size[ls[i]] >= x) {
        return index(ls[i], x);
    } else if (size[ls[i]] + keycount[i] < x) {
        return index(rs[i], x - size[ls[i]] - keycount[i]);
    }
    return key[i];
}

//����λ�ڵ� x λ������
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

//��ѯ x ��ǰ����ǰ������ΪС�� x������������
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

//��ѯ x �ĺ�̣���̶���Ϊ���� x������С������
int post(int num) {
    return post(head, num);
}

void clear() {
    memset(key + 1, 0, cnt * sizeof(int));
    memset(height + 1, 0, cnt * sizeof(int));
    memset(ls + 1, 0, cnt * sizeof(int));
    memset(rs + 1, 0, cnt * sizeof(int));
    memset(keycount + 1, 0, cnt * sizeof(int));
    memset(size + 1, 0, cnt * sizeof(int));
    cnt = 0;
    head = 0;
}

int main()
{
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
            cout << getrank(x) << endl;
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
