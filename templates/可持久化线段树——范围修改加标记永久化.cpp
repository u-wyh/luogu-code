// ��Χ�޸ĵĿɳ־û��߶�����������û����ٿռ�ռ�ã�C++��
// ����һ������Ϊn������arr���±�1~n��ʱ���t=0��arr��Ϊ��0�汾������
// һ����m����ѯ��ÿ����ѯΪ�������������е�һ��
// C x y z : ��ǰʱ���t�汾�����飬[x..y]��Χÿ����������z���õ�t+1�汾���飬����t++
// Q x y   : ��ǰʱ���t�汾�����飬��ӡ[x..y]��Χ�ۼӺ�
// H x y z : z�汾�����飬��ӡ[x..y]��Χ���ۼӺ�
// B x     : ��ǰʱ���t���ó�x
// 1 <= n��m <= 10^5
// -10^9 <= arr[i] <= +10^9
// �������� : https://acm.hdu.edu.cn/showproblem.php?pid=4348
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100001;
const int MAXT = MAXN * 25;
int n, m, t = 0;
long long arr[MAXN];
int root[MAXN];
int ls[MAXT];
int rs[MAXT];
long long sum[MAXT];
long long addTag[MAXT];
int cnt = 0;

int build(int l, int r) {
    int rt = ++cnt;
    addTag[rt] = 0;
    if (l == r) {
        sum[rt] = arr[l];
    } else {
        int mid = (l + r) / 2;
        ls[rt] = build(l, mid);
        rs[rt] = build(mid + 1, r);
        sum[rt] = sum[ls[rt]] + sum[rs[rt]];
    }
    return rt;
}

int add(int jobl, int jobr, long long jobv, int l, int r, int i) {
    int rt = ++cnt, a = max(jobl, l), b = min(jobr, r);
    ls[rt] = ls[i];
    rs[rt] = rs[i];
    sum[rt] = sum[i] + jobv * (b - a + 1);
    addTag[rt] = addTag[i];
    if (jobl <= l && r <= jobr) {
        addTag[rt] += jobv;
    } else {
        int mid = (l + r) / 2;
        if (jobl <= mid) {
            ls[rt] = add(jobl, jobr, jobv, l, mid, ls[rt]);
        }
        if (jobr > mid) {
            rs[rt] = add(jobl, jobr, jobv, mid + 1, r, rs[rt]);
        }
    }
    return rt;
}

long long query(int jobl, int jobr, long long addHistory, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i] + addHistory * (r - l + 1);
    }
    int mid = (l + r) / 2;
    long long ans = 0;
    if (jobl <= mid) {
        ans += query(jobl, jobr, addHistory + addTag[i], l, mid, ls[i]);
    }
    if (jobr > mid) {
        ans += query(jobl, jobr, addHistory + addTag[i], mid + 1, r, rs[i]);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    root[0] = build(1, n);
    char op;
    int x, y;
    long long z;
    for (int i = 1; i <= m; i++) {
        cin >> op;
        if (op == 'C') {
            cin >> x >> y >> z;
            root[t + 1] = add(x, y, z, 1, n, root[t]);
            t++;
        } else if (op == 'Q') {
            cin >> x >> y;
            cout << query(x, y, 0, 1, n, root[t]) << "\n";
        } else if (op == 'H') {
            cin >> x >> y >> z;
            cout << query(x, y, 0, 1, n, root[z]) << "\n";
        } else {
            cin >> x;
            t = x;
        }
    }
    return 0;
}
