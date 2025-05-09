#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 100001;

// ��������ͷ�ڵ���
int head = 0;

// �����˶��ٽڵ���
int cnt = 0;

// key[i]    : ���Ϊi�Ľڵ��key
int key[MAXN];

// father[i] : ���Ϊi�Ľڵ�ĸ��ڵ���
int father[MAXN];

// ls[i]     : ���Ϊi�Ľڵ�����ӱ�ţ�ԭleft��
int ls[MAXN];

// rs[i]     : ���Ϊi�Ľڵ���Һ��ӱ�ţ�ԭright��
int rs[MAXN];

// size[i]   : �Ա��Ϊi�Ľڵ���ͷ��������һ���ж��ٸ��ڵ�
int size[MAXN];

// ���½ڵ�i�Ĵ�С��Ϣ
void up(int i) {
    size[i] = size[ls[i]] + size[rs[i]] + 1;
}

// �жϱ��Ϊi�Ľڵ㣬���丸�׵�ʲô����
// 0��������ӣ��ָ�Ϊls����1�����Ҷ��ӣ��ָ�Ϊrs��
int lr(int i) {
    return rs[father[i]] == i ? 1 : 0;
}

// ���Ϊi�Ľڵ�����һ�����ڽṹ��������
void rotate(int i) {
    int f = father[i], g = father[f], soni = lr(i), sonf = lr(f);
    if (soni == 1) {
        //�Ǹ��׽ڵ���Һ���
        //��ô��ֱ������
        rs[f] = ls[i];//���׽ڵ���Һ��ӱ��i�ڵ������
        if (rs[f] != 0) {//����ʵ����ָ��i�ڵ���Һ��Ӳ��ǿ�
            father[rs[f]] = f;
        }
        ls[i] = f;//i�ڵ����������Ϊ���׽ڵ�  �������
    } else {
        ls[f] = rs[i]; ;
        if (ls[f] != 0) {
            father[ls[f]] = f;
        }
        rs[i] = f;
    }
    if (g != 0) {
        //���үү�ڵ㲻�ǿ�
        if (sonf == 1) {
            //��ô��ǰ���׽ڵ���үү�ڵ��ʲô���� ���i�ڵ����ʲô����
            rs[g] = i;
        } else {
            ls[g] = i;
        }
    }
    father[f] = i;//ԭ�����׽ڵ�ĸ��ױ�Ϊi
    father[i] = g;//i�ĸ��׽ڵ��Ϊԭ����үү
    up(f);//֮���Բ��ý�gҲ����  ����Ϊ����������Сû�з����仯
    up(i);
}

// ���Ϊi�Ľڵ��������ɱ��Ϊgoal�Ľڵ�Ķ���
// ���goal == 0����ʾ�ѱ��Ϊi�Ľڵ�����������ͷ
void splay(int i, int goal) {
    int f = father[i], g = father[f];
    while (f != goal) {
        //���ײ���Ŀ�� ��ô��˵����û���������
        if (g != goal) {
            //үү����Ŀ��  ��ôi�ڵ�����Ҫ����үү�ڵ�����
            //��ôҪô��  ֮����  Ҫô��  һ����
            //�������Ҷ����ж�
            if (lr(i) == lr(f)) {
                rotate(f);
            } else {
                rotate(i);
            }
        }
        rotate(i);//���үү����Ŀ�� ��ô����һ�ξͿ�����
        f = father[i];
        g = father[f];
    }
    if (goal == 0) {
        head = i;
    }
}

// ����һ���ͳ���
int build1(int l, int r) {
    int h = cnt + 1;
    for (int i = l, last = 0; i <= r; i++, last = cnt) {
        key[++cnt] = i;
        father[cnt] = last;
        ls[cnt] = rs[cnt] = 0; // ԭ left[cnt] = right[cnt] = 0;
        size[cnt] = r - i + 1;
        if (last != 0) {
            rs[last] = cnt; // ԭ right[last] = cnt;
        }
    }
    return h;
}

// ����֮���γ���
int build2(int l, int r, int fa) {
    if (l > r) {
        return 0;
    }
    key[++cnt] = l;
    father[cnt] = fa;
    ls[cnt] = rs[cnt] = 0; // ԭ left[cnt] = right[cnt] = 0;
    int h = cnt;
    if (l < r) {
        key[++cnt] = r;
        father[cnt] = h;
        ls[cnt] = rs[cnt] = 0; // ԭ left[cnt] = right[cnt] = 0;
        int c = cnt;
        rs[h] = c; // ԭ right[h] = c;
        ls[c] = build2(l + 1, r - 1, c); // ԭ left[c] = build2(l + 1, r - 1, c);
        up(c);
    }
    up(h);
    return h;
}

// ������iΪͷ�����ĸ߶�
int height(int i) {
    if (i == 0) {
        return 0;
    }
    return max(height(ls[i]), height(rs[i])) + 1; // ԭ max(height(left[i]), height(right[i])) + 1;
}

int main() {
    cout << "����һ���ͳ���" << endl;
    cout << "���·��ڵ�ִ��splay���۲�߶ȱ仯" << endl;
    head = build1(1, 1000);
    cout << "splay֮ǰ�������� : " << height(head) << endl;
    splay(cnt, 0);
    cout << "splay֮��������� : " << height(head) << endl;

    cout << "==================" << endl;

    cout << "����֮���ͳ���" << endl;
    cout << "���·��ڵ�ִ��splay���۲�߶ȱ仯" << endl;
    head = build2(1, 1000, 0);
    cout << "splay֮ǰ�������� : " << height(head) << endl;
    splay(cnt, 0);
    cout << "splay֮��������� : " << height(head) << endl;

    return 0;
}
