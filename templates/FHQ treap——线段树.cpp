// ����ƽ������FHQ-Treapʵ�ַ�Χ��ת��C++�汾
// ����Ϊn�����У��±��1��ʼ��һ��ʼ����Ϊ1, 2, ..., n
// ����������k��������ÿ����������l��r����ʾ��l��r��Χ�ϵ��������ַ�ת
// ����k�β����󣬴����Ҵ�ӡ��������
// 1 <= n, k <= 10^5
// �������� : https://www.luogu.com.cn/problem/P3391
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;

int head = 0;
int cnt = 0;
int key[MAXN];
int ls[MAXN];
int rs[MAXN];
int size[MAXN];
double priority[MAXN];
bool rev[MAXN];
int ans[MAXN];
int ansi;

void up(int i) {
    size[i] = size[ls[i]] + size[rs[i]] + 1;
}

//�����µ��·�
void down(int i) {
    if (rev[i]) {
        swap(ls[i], rs[i]);
        rev[ls[i]] ^= 1;
        rev[rs[i]] ^= 1;
        rev[i] = false;
    }
}

//�����Ҳ�Ǹ�����������
//��������õ�Ҳ��λ����Ϣ ����ʹ������
//ʹ����������õ���
void split(int l, int r, int i, int rank) {
    if (i == 0) {
        rs[l] = ls[r] = 0;
    } else {
        down(i);
        if (size[ls[i]] + 1 <= rank) {
            rs[l] = i;
            split(i, r, rs[i], rank - size[ls[i]] - 1);
        } else {
            ls[r] = i;
            split(l, i, ls[i], rank);
        }
        up(i);
    }
}

int merge(int l, int r) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        down(l);//�·�����Ϣ
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        down(r);
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

void inorder(int i) {
    if (i != 0) {
        down(i);
        inorder(ls[i]);
        ans[++ansi] = key[i];
        inorder(rs[i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        key[++cnt] = i;
        size[cnt] = 1;
        priority[cnt] = (double)rand() / RAND_MAX;
        head = merge(head, cnt);
    }
    for (int i = 1, x, y, l, m, lm, r; i <= k; i++) {
        cin >> x >> y;
        split(0, 0, head, y);
        lm = rs[0];//��ʾ<=y������ͷ���
        r = ls[0];//��ʾ>y������ͷ���
        split(0, 0, lm, x - 1);
        l = rs[0];//��ʾ<=x-1������ͷ���
        m = ls[0];//��ʾ>x������ͷ���
        rev[m] ^= 1;
        head = merge(merge(l, m), r);
    }
    ansi = 0;
    inorder(head);
    for (int i = 1; i <= ansi; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
