// ��״�������߶�����C++��
// ����һ������Ϊn������arr���±�1~n��ÿ��������������5�������е�һ�֣�һ������m�β���
// ���� 1 x y z : ��ѯ����z��arr[x..y]�е�����
// ���� 2 x y z : ��ѯarr[x..y]���ŵ�z��������
// ���� 3 x y   : arr��xλ�õ����ָĳ�y
// ���� 4 x y z : ��ѯ����z��arr[x..y]�е�ǰ���������ڷ���-2147483647
// ���� 5 x y z : ��ѯ����z��arr[x..y]�еĺ�̣������ڷ���+2147483647
// 1 <= n��m <= 5 * 10^4
// �����е�ֵ��Զ��[0, 10^8]��Χ��
// �������� : https://www.luogu.com.cn/problem/P3380
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50001;
//�����߶����ڵ����
const int MAXT = MAXN * 160;
const int INF = INT_MAX;

//�ⲿ����״�����Ǹ���arr���±���֯
//�ڲ����߶����ǰ�����ɢ������������֯

int n, m, s;
int arr[MAXN];
//�ռ�����  ������ɢ��
int ques[MAXN][4];
int sorted[MAXN * 2];

//�߶���
int root[MAXN];
int sum[MAXT];
int ls[MAXT];
int rs[MAXT];
int cntt = 0;

//�Ӽ���Ӫ
int addTree[MAXN];
int minusTree[MAXN];
int cntadd;
int cntminus;

int kth(int num) {
    int left = 1, right = s, mid;
    while (left <= right) {
        mid = (left + right) / 2;
        if (sorted[mid] == num) {
            return mid;
        } else if (sorted[mid] < num) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int lowbit(int i) {
    return i & -i;
}

// ��jobiС�����֣�����jobv�ļ��������ַ�Χl~r���ڵ���i������ͷ�ڵ���
int innerAdd(int jobi, int jobv, int l, int r, int i) {
    if (i == 0) {
        i = ++cntt;
    }
    if (l == r) {
        sum[i] += jobv;
    } else {
        int mid = (l + r) / 2;
        if (jobi <= mid) {
        	ls[i] = innerAdd(jobi, jobv, l, mid, ls[i]);
        } else {
        	rs[i] = innerAdd(jobi, jobv, mid + 1, r, rs[i]);
        }
        sum[i] = sum[ls[i]] + sum[rs[i]];
    }
    return i;
}

// ��ѯ��jobkС�����֣����ַ�Χl~r
// ����Ҫͷ�ڵ��ţ���Ϊ�ж���������е�ͷ�ڵ��¼��addTree��minusTree
int innerQuery(int jobk, int l, int r) {
    if (l == r) {
        return l;
    }
    int mid = (l + r) / 2;
    int leftsum = 0;
    for (int i = 1; i <= cntadd; i++) {
        leftsum += sum[ls[addTree[i]]];
    }
    for (int i = 1; i <= cntminus; i++) {
        leftsum -= sum[ls[minusTree[i]]];
    }
    if (jobk <= leftsum) {
        for (int i = 1; i <= cntadd; i++) {
            addTree[i] = ls[addTree[i]];
        }
        for (int i = 1; i <= cntminus; i++) {
            minusTree[i] = ls[minusTree[i]];
        }
        return innerQuery(jobk, l, mid);
    } else {
        for (int i = 1; i <= cntadd; i++) {
            addTree[i] = rs[addTree[i]];
        }
        for (int i = 1; i <= cntminus; i++) {
            minusTree[i] = rs[minusTree[i]];
        }
        return innerQuery(jobk - leftsum, mid + 1, r);
    }
}

// ��ѯ��jobiС�����ָ��������ַ�Χl~r
// ����Ҫͷ�ڵ��ţ���Ϊ�ж���������е�ͷ�ڵ��¼��addTree��minusTree
int innerSmall(int jobi, int l, int r) {
    if (l == r) {
        return 0;
    }
    int mid = (l + r) / 2;
    if (jobi <= mid) {
        //�����Ӽ���Ӫ�����ڵ�
        for (int i = 1; i <= cntadd; i++) {
            addTree[i] = ls[addTree[i]];
        }
        for (int i = 1; i <= cntminus; i++) {
            minusTree[i] = ls[minusTree[i]];
        }
        return innerSmall(jobi, l, mid);
    } else {
        int leftsum = 0;
        //����ͳ�����С��jobi�����ָ��� Ȼ���ѯ�ұ�С�ڵĸ���
        //�������Ӽ���Ӫ�����ڵ�
        for (int i = 1; i <= cntadd; i++) {
            leftsum += sum[ls[addTree[i]]];
            addTree[i] = rs[addTree[i]];
        }
        for (int i = 1; i <= cntminus; i++) {
            leftsum -= sum[ls[minusTree[i]]];
            minusTree[i] = rs[minusTree[i]];
        }
        return leftsum + innerSmall(jobi, mid + 1, r);
    }
}

// arr��i�±�����֣�����cnt�ļ���  �仯��λ����arr[i]  arr[i]ʵ����������
void add(int i, int cnt) {
    for (int j = i; j <= n; j += lowbit(j)) {
        //��ʾ��״�����п��԰���i��������  arr[i]�Ĵ�Ƶ����cnt
        root[j] = innerAdd(arr[i], cnt, 1, s, root[j]);
    }
}

// arr��i�±�����֣��ĳ�v
void update(int i, int v) {
    add(i, -1);
    arr[i] = kth(v);
    add(i, 1);
}

// arr[l..r]��Χ�ϣ���vС�����ָ���
int small(int l, int r, int v) {
    cntadd = cntminus = 0;
    for (int i = r; i > 0; i -= lowbit(i)) {
        addTree[++cntadd] = root[i];//����Ӫ��Ԫ��
    }
    for (int i = l - 1; i > 0; i -= lowbit(i)) {
        minusTree[++cntminus] = root[i];//����Ӫ��Ԫ��
    }
    return innerSmall(v, 1, s);
}

// arr[l..r]��Χ�ϣ���ѯ��kС��������ʲô
int number(int l, int r, int k) {
    cntadd = cntminus = 0;
    //����ɼӼ���Ӫ�������
    for (int i = r; i > 0; i -= lowbit(i)) {
        addTree[++cntadd] = root[i];
    }
    for (int i = l - 1; i > 0; i -= lowbit(i)) {
        minusTree[++cntminus] = root[i];
    }
    return sorted[innerQuery(k, 1, s)];
}

// arr[l..r]��Χ�ϣ���ѯv��ǰ��
int pre(int l, int r, int v) {
    int rank = small(l, r, v) + 1;
    if (rank == 1) {
        return -INF;
    }
    return number(l, r, rank - 1);
}

// arr[l..r]��Χ�ϣ���ѯv�ĺ��
int post(int l, int r, int v) {
    if (v == s) {
        return INF;
    }
    int sml = small(l, r, v + 1);
    if (sml == r - l + 1) {
        //����������������ֶ�����С  ˵��û�к��
        return INF;
    }
    return number(l, r, sml + 1);
}

//�����ɢ��  ����ԭʼ������뵽��״������
void prepare() {
    s = 0;
    for (int i = 1; i <= n; i++) {
        sorted[++s] = arr[i];
    }
    for (int i = 1; i <= m; i++) {
        if (ques[i][0] == 3) {
            sorted[++s] = ques[i][2];
        } else if (ques[i][0] != 2) {
            sorted[++s] = ques[i][3];
        }
    }
    sort(sorted + 1, sorted + s + 1);
    int len = 1;
    for (int i = 2; i <= s; i++) {
        if (sorted[len] != sorted[i]) {
            sorted[++len] = sorted[i];
        }
    }
    s = len;
    for (int i = 1; i <= n; i++) {
        arr[i] = kth(arr[i]);
        add(i, 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    cin >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> ques[i][0];
        cin >> ques[i][1];
        cin >> ques[i][2];
        if (ques[i][0] != 3) {
            cin >> ques[i][3];
        }
    }
    prepare();
    for (int i = 1, op, x, y, z; i <= m; i++) {
        op = ques[i][0];
        x = ques[i][1];
        y = ques[i][2];
        if (op == 3) {
            update(x, y);
        } else {
            z = ques[i][3];
            if (op == 1) {
                cout << small(x, y, kth(z)) + 1 << "\n";
            } else if (op == 2) {
                cout << number(x, y, z) << "\n";
            } else if (op == 4) {
                cout << pre(x, y, kth(z)) << "\n";
            } else {
                cout << post(x, y, kth(z)) << "\n";
            }
        }
    }
    return 0;
}
