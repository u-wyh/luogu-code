// P���Ͱ
// һ����n��Ͱ���ų�һ�ţ����1~n��ÿ��Ͱ����װ�����������
// ��Ч��ʵ��������������
// ���� 1 k v : ������v����k��Ͱ��
// ���� 2 l r : ���Դ�l..r��Ͱ�����������֣������������Ľ��
// 1 <= n��m <= 5 * 10^4
// 0 <= v <= 2^31 - 1
// �������� : https://www.luogu.com.cn/problem/P4839
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50001;
const int BIT = 30;

// �߶�����ÿ����Χ��ά�����Ի�
int treeBasis[MAXN << 2][BIT + 1];
int basis[BIT + 1];

bool insert(int *basis, int num) {
    for (int i = BIT; i >= 0; i--) {
        if (num >> i & 1) {
            if (basis[i] == 0) {
                basis[i] = num;
                return true;
            }
            num ^= basis[i];
        }
    }
    return false;
}
//�����һ����ͨ�����Ի�  �����������Ի�

//�߶����Ļ�������
void add(int jobi, int jobv, int l, int r, int i) {
    insert(treeBasis[i], jobv);
    if (l < r) {
        int mid = (l + r) >> 1;
        if (jobi <= mid) {
            add(jobi, jobv, l, mid, i << 1);
        } else {
            add(jobi, jobv, mid + 1, r, i << 1 | 1);
        }
    }
}

void merge(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        for (int j = BIT; j >= 0; j--) {
            if (treeBasis[i][j] != 0) {
                insert(basis, treeBasis[i][j]);
            }
        }
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            merge(jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid) {
            merge(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
    }
}

int query(int jobl, int jobr, int m) {
    for(int i=0;i<=BIT;i++){
        basis[i]=0;
    }
    merge(jobl, jobr, 1, m, 1);
    int ans = 0;
    for (int j = BIT; j >= 0; j--) {
        ans = max(ans, ans ^ basis[j]);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int jobi, jobv;
            cin >> jobi >> jobv;
            add(jobi, jobv, 1, m, 1);
        } else {
            int jobl, jobr;
            cin >> jobl >> jobr;
            cout << query(jobl, jobr, m) << endl;
        }
    }

    return 0;
}
