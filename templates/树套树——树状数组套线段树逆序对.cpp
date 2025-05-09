// �Ŷӣ�C++��
// ����һ������Ϊn������arr���±�1~n
// �����i < j������arr[i] > arr[j]����ô(i,j)�ͽ���һ�������
// ���ȴ�ӡԭʼarr���ж�������ԣ�Ȼ������������͵Ĳ�����һ������m��
// ���� a b : ����arr��aλ�õ�����bλ�õ�������ӡ����������Ե�����
// 1 <= n <= 2 * 10^4
// 1 <= m <= 2 * 10^3
// 1 <= arr[i] <= 10^9
// �������� : https://www.luogu.com.cn/problem/P1975
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 20001;
const int MAXT = MAXN * 80;
//��������������Сֵ  ����Խ��  ���� x-1 x+1
const int INF = 1000000001;

int n, m, s;
int arr[MAXN];
int sorted[MAXN + 2];
int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int sum[MAXT];
int cnt = 0;
int ans = 0;

int kth(int num) {
    int l = 1, r = s, mid;
    while (l <= r) {
        mid = (l + r) / 2;
        if (sorted[mid] == num) return mid;
        else if (sorted[mid] < num) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

int lowbit(int i) {
    return i & -i;
}

// �߶��������޸ģ�jobi������ִ�Ƶ����jobv
int innerAdd(int jobi, int jobv, int l, int r, int i) {
    if (i == 0)
        i = ++cnt;
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

// ��ѯ�����ַ�Χ[jobl...jobr]���߶��������ַ�Χ[l..r]���ڵ���i
// �����ж��ٴ�Ƶ
int innerQuery(int jobl, int jobr, int l, int r, int i) {
    if (i == 0) return 0;
    if (jobl <= l && r <= jobr)
        return sum[i];
    int mid = (l + r) / 2;
    int ans = 0;
    if (jobl <= mid) {
    	ans += innerQuery(jobl, jobr, l, mid, ls[i]);
    }
    if (jobr > mid) {
    	ans += innerQuery(jobl, jobr, mid + 1, r, rs[i]);
    }
    return ans;
}

// arr��iλ�õ����֣���Ƶ����v
void add(int i, int v) {
    for (int j = i; j <= n; j += lowbit(j)) {
        root[j] = innerAdd(arr[i], v, 1, s, root[j]);
    }
}

// arr[al..ar]��Χ�ϣ��ж���������[numl..numr]��Χ��
int query(int al, int ar, int numl, int numr) {
    int ans = 0;
    for (int i = ar; i > 0; i -= lowbit(i)) {
        ans += innerQuery(numl, numr, 1, s, root[i]);
    }
    for (int i = al - 1; i > 0; i -= lowbit(i)) {
        ans -= innerQuery(numl, numr, 1, s, root[i]);
    }
    return ans;
}

// ����a��bλ�õ����֣���֤a��ǰ��b�ں�
// ����������Ե�����ans
void compute(int a, int b) {
    //���µ����в���������Լ򻯳����� ����Ҫע��Ķ���̫���� ��������
    ans -= query(a + 1, b - 1, 1, arr[a] - 1);
    ans += query(a + 1, b - 1, arr[a] + 1, s);
    ans -= query(a + 1, b - 1, arr[b] + 1, s);
    ans += query(a + 1, b - 1, 1, arr[b] - 1);
    if (arr[a] < arr[b])
        ans++;
    else if (arr[a] > arr[b])
        ans--;
    add(a, -1);
    add(b, -1);
    swap(arr[a], arr[b]);
    add(a, 1);
    add(b, 1);
}

void prepare() {
    s = 0;
    for (int i = 1; i <= n; i++) sorted[++s] = arr[i];
    sorted[++s] = -INF;
    sorted[++s] = INF;
    //�����Сֵ �� ���ֵ ��ֹ���
    sort(sorted + 1, sorted + s + 1);
    int len = 1;
    for (int i = 2; i <= s; i++) {
        if (sorted[len] != sorted[i])
            sorted[++len] = sorted[i];
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
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    prepare();
    for (int i = 2; i <= n; i++){
        //ÿ��λ�õ�Ԫ�ز�ѯ���Լ�֮ǰ�ж��ٴ����Լ���
        ans += query(1, i - 1, arr[i] + 1, s);
    }
    cout << ans << '\n';
    cin >> m;
    for (int i = 1, a, b; i <= m; i++) {
        cin >> a >> b;
        if (a > b)
            swap(a, b);
        compute(a, b);
        cout << ans << '\n';
    }
    return 0;
}
