// ��ǲ��C++��
// һ����n�����ߣ�ÿ���������ϼ���š����ʡ���������������
// ���뱣֤���κ����ߵ��ϼ���� < �������ߵı�ţ�1��������������������ͷ
// ��һ����m��Ԥ�㣬������������������ѡһ��������Ȼ���������������ѡ����
// ��ѡ��ĳ������֮�󣬲�һ��Ҫѡ����ͷ�����ߣ�ֻҪ������m��Ԥ�㣬��������ѡ�������ϵ�����
// �������� = ��Ӷ���� * ����ͷ���ߵ�������������ȡ�õ���������Ƕ���
// 1 <= n <= 10^5           1 <= m <= 10^9
// 1 <= ÿ�����߹��� <= m     1 <= ÿ�������쵼�� <= 10^9
// �������� : https://www.luogu.com.cn/problem/P1552
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;
int n, m;
int leader[MAXN];
long long cost[MAXN];
long long ability[MAXN];
int ls[MAXN];
int rs[MAXN];
int dist[MAXN];
int fa[MAXN];
int siz[MAXN];
long long sum[MAXN];

int find(int i) {
    return fa[i] = (fa[i] == i ? i : find(fa[i]));
}

int merge(int i, int j) {
    if (i == 0 || j == 0) {
        return i + j;
    }
    int tmp;
    if (cost[i] < cost[j]) {
        tmp = i;
        i = j;
        j = tmp;
    }
    rs[i] = merge(rs[i], j);
    if (dist[ls[i]] < dist[rs[i]]) {
        tmp = ls[i];
        ls[i] = rs[i];
        rs[i] = tmp;
    }
    dist[i] = dist[rs[i]] + 1;
    fa[ls[i]] = fa[rs[i]] = i;
    return i;
}

int pop(int i) {
    fa[ls[i]] = ls[i];
    fa[rs[i]] = rs[i];
    fa[i] = merge(ls[i], rs[i]);
    ls[i] = rs[i] = dist[i] = 0;
    return fa[i];
}

void prepare() {
    dist[0] = -1;
    for (int i = 1; i <= n; i++) {
        ls[i] = rs[i] = dist[i] = 0;
        siz[i] = 1;
        sum[i] = cost[i];
        fa[i] = i;
    }
}

long long compute() {
    long long ans = 0;
    int p, psize, h, hsize;
    long long hsum, psum;
    for (int i = n; i >= 1; i--) {
        h = find(i);
        hsize = siz[h];
        hsum = sum[h];
        while (hsum > m) {
            //����Ԥ��  ��ô�͵������ĸ���
            //������Ǵ����  ��Ϊ���������������й�  ���������Ԥ����  �Ͱ�������ɾ��
            pop(h);
            hsize--;
            hsum -= cost[h];
            h = find(i);
        }
        ans = max(ans, (long long)hsize * ability[i]);
        if (i > 1) {
            //���Լ�����Ϣ���ݸ��Լ��ĸ��׽ڵ�
            p = find(leader[i]);//һ��ʼ��û���ֵ��ýڵ��ʱ�� ��ʵ���岢����һ������
            psize = siz[p];
            psum = sum[p];
            fa[p] = fa[h] = merge(p, h);
            siz[fa[p]] = psize + hsize;
            sum[fa[p]] = psum + hsum;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> leader[i] >> cost[i] >> ability[i];
    }
    prepare();
    cout << compute() << endl;
    return 0;
}
