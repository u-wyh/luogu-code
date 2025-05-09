// k������ѯ��C++��
// ��ʼʱ��n���ռ��ϣ����1~n��ʵ�������������͵Ĳ���������һ������m��
// ���� 1 l r v : ����v�����ŷ�Χ[l,r]��ÿһ��������
// ���� 2 l r k : ��ŷ�Χ[l,r]�����м��ϣ�������ɲ�ȥ�صĲ��������ص�k�������
// 1 <= n��m <= 5 * 10^4
// -n <= v <= +n
// 1 <= k < 2^63����Ŀ��֤��k�������һ������
// �������� : https://www.luogu.com.cn/problem/P3332
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
//��������������ִ�д����1 2 3 �ڲ��Ӧ����arr
//�����Ŀ�Ǹ������ֵ�����ȷ�������
//�������jobl��jobr�����м���һ������Ϊjobv������
//��ô��㷶Χ�а���jobv������Ҫ��jobl��jobr�ļ�����Ԫ�ظ�����һ
//�ڲ����Ǹ��ݼ��ϵı�Ż���
#include <bits/stdc++.h>
using namespace std;
// �ⲿ�߶����ķ�Χ��һ��ֻ��m�����������������m������
const int MAXM = 50001;
// �ڲ��߶����Ľڵ�������
const int MAXT = MAXM * 230;

int n, m, s;
// ���в����ռ���������Ϊǣ����������ɢ��
int ques[MAXM][4];
// ���п��ܵ����֣��ռ�����ȥ�أ�����õ���������
int sorted[MAXM];

// �ⲿ(a~b) + �ڲ�(c~d)��ʾ������������Χa~b�����Ϸ�Χc~d�����ֵĸ���
// �ⲿ�߶������±��ʾ���ֵ�����
// �ⲿ(a~b)�������Ӧ�Ľڵ���Ϊi����ôroot[i]�����ڲ��߶�����ͷ�ڵ���
int root[MAXM << 2];

// �ڲ��߶����ǿ����߶�����������Ҫcnt����ýڵ����
// �ڲ��߶������±��ʾ���ϵı��
// �ڲ�(c~d)�������Ӧ�Ľڵ���Ϊi
// sum[i]��ʾ���Ϸ�Χc~d��һ���ռ��˶�������
// lazy[i]��������Ϣ�����Ϸ�Χc~d�������˼������֣��ȴ������µ��·�
int ls[MAXT];
int rs[MAXT];
long long sum[MAXT];
int lazy[MAXT];
int cnt;

int kth(int num) {
    int l = 1, r = s;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (sorted[mid] == num) {
            return mid;
        } else if (sorted[mid] < num) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return -1;
}

void up(int i) {
    sum[i] = sum[ls[i]] + sum[rs[i]];
}

void down(int i, int ln, int rn) {
    if (lazy[i]) {
        if (!ls[i]) ls[i] = ++cnt;
        if (!rs[i]) rs[i] = ++cnt;
        sum[ls[i]] += 1LL * lazy[i] * ln;
        lazy[ls[i]] += lazy[i];
        sum[rs[i]] += 1LL * lazy[i] * rn;
        lazy[rs[i]] += lazy[i];
        lazy[i] = 0;
    }
}

//���ڲ�����jobl~jobr�м���һ������
int innerAdd(int jobl, int jobr, int l, int r, int i) {
    if (!i) i = ++cnt;
    if (jobl <= l && r <= jobr) {
        sum[i] += (long long)(r - l + 1);
        lazy[i]++;
    } else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) ls[i] = innerAdd(jobl, jobr, l, mid, ls[i]);
        if (jobr > mid) rs[i] = innerAdd(jobl, jobr, mid + 1, r, rs[i]);
        up(i);
    }
    return i;
}

//��ѯ�ڲ�������jobl��jobr�����ж��ٸ�Ԫ��
long long innerQuery(int jobl, int jobr, int l, int r, int i) {
    if (!i) return 0;
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    long long ans = 0;
    if (jobl <= mid) ans += innerQuery(jobl, jobr, l, mid, ls[i]);
    if (jobr > mid) ans += innerQuery(jobl, jobr, mid + 1, r, rs[i]);
    return ans;
}

//���ⲿ�м���һ����СΪjobv�����ֵ�jobl~jobr�ļ���  ������������������
//�൱�ڸ��ݼ������Ԫ�ص�ֵ  �����ϲ�ֿ�
void outerAdd(int jobl, int jobr, int jobv, int l, int r, int i) {
    root[i] = innerAdd(jobl, jobr, 1, n, root[i]);
    if (l < r) {
        int mid = (l + r) >> 1;
        if (jobv <= mid) {
            outerAdd(jobl, jobr, jobv, l, mid, i << 1);
        } else {
            outerAdd(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
    }
}

//��ѯ��jobl��jobr������  ��jobk���������ʲô  ��ʵ���Ϸ��ص���������ֵ�������
//���jobl��jobrʵ�������ڲ����ϵķ�Χ  l r���ⲿ��Χ
int outerQuery(int jobl, int jobr, long long jobk, int l, int r, int i) {
    if (l == r) {
        return l;
    }
    int mid = (l + r) >> 1;
    long long rightsum = innerQuery(jobl, jobr, 1, n, root[i << 1 | 1]);
    if (jobk > rightsum) {
        return outerQuery(jobl, jobr, jobk - rightsum, l, mid, i << 1);
    } else {
        return outerQuery(jobl, jobr, jobk, mid + 1, r, i << 1 | 1);
    }
}

void prepare() {
    s = 0;
    for (int i = 1; i <= m; i++) {
        if (ques[i][0] == 1) {
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
    for (int i = 1; i <= m; i++) {
        if (ques[i][0] == 1) {
            ques[i][3] = kth(ques[i][3]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> ques[i][0] >> ques[i][1] >> ques[i][2] >> ques[i][3];
    }
    prepare();
    for (int i = 1; i <= m; i++) {
        if (ques[i][0] == 1) {
            outerAdd(ques[i][1], ques[i][2], ques[i][3], 1, s, 1);
            //����һ����СΪ ques[i][3]������ques[i][1]~ques[i][2]
        } else {
            int idx = outerQuery(ques[i][1], ques[i][2], ques[i][3], 1, s, 1);
            cout << sorted[idx] << "\n";
        }
    }
    return 0;
}
