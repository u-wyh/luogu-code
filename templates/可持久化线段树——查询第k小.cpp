// �����޸ĵĿɳ־û��߶���ģ����2��C++��
// ����һ������Ϊn������arr���±�1~n��һ����m����ѯ
// ÿ����ѯ l r k : ��ӡarr[l..r]�е�kС������
// 1 <= n��m <= 2 * 10^5
// 0 <= arr[i] <= 10^9
// �������� : https://www.luogu.com.cn/problem/P3834
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200001;
const int MAXT = MAXN * 22;

int n, m, s;

// ԭʼ����
int arr[MAXN];

// �ռ�Ȩֵ������ȥ������ɢ��
int sorted[MAXN];

// �ɳ־û��߶�����Ҫ
// root[i] : ����arr[i]֮���γ��°汾���߶�������¼ͷ�ڵ���
// 0�Ű汾���߶�������һ������Ҳû��ʱ��ÿ�����ε����ֳ��ֵĴ���
// i�Ű汾���߶�������arr[1..i]��Χ�ڣ�ÿ�����ε����ֳ��ֵĴ���
int root[MAXN];
int ls[MAXT];
int rs[MAXT];

// ������Χ���ռ��˶��ٸ�����
int size[MAXT];
int cnt;

// ����num������ֵ����������
int kth(int num) {
    int left = 1, right = s, mid, ans = 0;
    while (left <= right) {
        mid = (left + right) / 2;
        if (sorted[mid] <= num) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return ans;
}

// ������Χl~r�������߶���������ͷ�ڵ���
int build(int l, int r) {
    int rt = ++cnt;
    size[rt] = 0;
    if (l < r) {
        int mid = (l + r) / 2;
        ls[rt] = build(l, mid);
        rs[rt] = build(mid + 1, r);
    }
    return rt;
}

// ������Χl~r����Ϣ��i�Žڵ㣬����һ������Ϊjobi������
// �����µ�ͷ�ڵ���
int insert(int jobi, int l, int r, int i) {
    int rt = ++cnt;
    ls[rt] = ls[i];
    rs[rt] = rs[i];
    size[rt] = size[i] + 1;//�¼�һ��Ԫ��  ��С��һ
    if (l < r) {
        int mid = (l + r) / 2;
        if (jobi <= mid) {
            ls[rt] = insert(jobi, l, mid, ls[rt]);
        } else {
            rs[rt] = insert(jobi, mid + 1, r, rs[rt]);
        }
    }
    return rt;
}

// ������Χl~r���ϰ汾��Ϣ��u�Žڵ㣬�°汾��Ϣ��v�Žڵ�
// ���أ���jobkС�����֣���������
int query(int jobk, int l, int r, int u, int v) {
    if (l == r) {
        return l;
    }
    int lsize = size[ls[v]] - size[ls[u]];
    int mid = (l + r) / 2;
    if (lsize >= jobk) {
        //������������㹻 ��ô����������
        return query(jobk, l, mid, ls[u], ls[v]);
    } else {
        return query(jobk - lsize, mid + 1, r, rs[u], rs[v]);
    }
}

// Ȩֵ����ɢ������ȥ�� + ���ɸ��汾���߶���
void prepare() {
    cnt = 0;
    for (int i = 1; i <= n; i++) {
        sorted[i] = arr[i];
    }
    sort(sorted + 1, sorted + n + 1);
    s = 1;
    for (int i = 2; i <= n; i++) {
        if (sorted[s] != sorted[i]) {
            sorted[++s] = sorted[i];
        }
    }
    root[0] = build(1, s);//������һ����
    for (int i = 1, x; i <= n; i++) {
        x = kth(arr[i]);
        root[i] = insert(x, 1, s, root[i - 1]);
        //ÿ�λ�����һ��������һ��Ԫ��  ��������
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    prepare();
    for (int i = 1, l, r, k, rank; i <= m; i++) {
        cin >> l >> r >> k;
        rank = query(k, 1, s, root[l - 1], root[r]);
        cout << sorted[rank] << '\n';
    }
    return 0;
}
