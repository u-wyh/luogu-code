// �ı��༭����FHQ-Treapʵ�������ƶ���C++�汾
// һ��ʼ�ı�Ϊ�գ�������ı���ͷ��Ҳ����1λ�ã���ʵ������6�ֲ���
// Move k     : ������ƶ�����k���ַ�֮�󣬲�����֤��겻�ᵽ�Ƿ�λ��
// Insert n s : �ڹ�괦���볤��Ϊn���ַ���s�����λ�ò���
// Delete n   : ɾ�������n���ַ������λ�ò��䣬������֤���㹻�ַ�
// Get n      : ��������n���ַ������λ�ò��䣬������֤���㹻�ַ�
// Prev       : ���ǰ��һ���ַ���������֤��겻�ᵽ�Ƿ�λ��
// Next       : ������һ���ַ���������֤��겻�ᵽ�Ƿ�λ��
// Insert����ʱ���ַ���s��ASCII����[32,126]��Χ�ϵ��ַ�һ����n���������ַ�����˵�
// �������� : https://www.luogu.com.cn/problem/P4008
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2000001;

int head = 0;
int cnt = 0;
char key[MAXN];
int ls[MAXN];
int rs[MAXN];
int size[MAXN];
double priority[MAXN];
char ans[MAXN];
int ansi;

void up(int i) {
    size[i] = size[ls[i]] + size[rs[i]] + 1;
}

//�������ⶼ�ǰ��մ�С  ��������ǰ���λ��
//������������
void split(int l, int r, int i, int rank) {
    if (i == 0) {
        rs[l] = ls[r] = 0;
    } else {
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
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

//������� ��¼��
void inorder(int i) {
    if (i != 0) {
        inorder(ls[i]);
        ans[++ansi] = key[i];
        inorder(rs[i]);
    }
}

int main() {
    srand(time(0));
    int pos = 0, len, l, m, lm, r;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        char op[10];
        cin >> op;
        if (op[0] == 'P') {
            pos--;
        } else if (op[0] == 'N') {
            pos++;
        } else if (op[0] == 'M') {
            cin >> pos;
        } else if (op[0] == 'I') {
            cin >> len;
            split(0, 0, head, pos);
            l = rs[0];
            r = ls[0];
            for (int j = 1; j <= len; j++) {
                char ch = getchar();
                while (ch < 32 || ch > 126) {
                    ch = getchar();
                }
                key[++cnt] = ch;
                size[cnt] = 1;
                priority[cnt] = (double)rand() / RAND_MAX;
                l = merge(l, cnt);
            }
            head = merge(l, r);
        } else if (op[0] == 'D') {
            cin >> len;
            split(0, 0, head, pos + len);
            lm = rs[0];
            r = ls[0];
            split(0, 0, lm, pos);
            l = rs[0];
            head = merge(l, r);
        } else {
            cin >> len;
            split(0, 0, head, pos + len);
            lm = rs[0];
            r = ls[0];
            split(0, 0, lm, pos);
            l = rs[0];
            m = ls[0];
            ansi = 0;
            inorder(m);
            head = merge(merge(l, m), r);
            for (int j = 1; j <= ansi; j++) {
                cout << ans[j];
            }
            cout << '\n';
        }
    }
    return 0;
}
