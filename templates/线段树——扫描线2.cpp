// �����ܳ���(��Ȳ���)
// �������� : https://www.luogu.com.cn/problem/P1856
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20001;

int rec[MAXN][4];
struct Line{
    int a1,a2,a3,a4;
}line[MAXN];
int vsort[MAXN];
// �߶���ĳ��Χ�ܳ���
int length[MAXN << 2];
// �߶���ĳ��Χ���ǳ���
int cover[MAXN << 2];
// �߶���ĳ��Χ���Ǵ���
int times[MAXN << 2];

int prepare(int n) {
    sort(vsort+1,vsort+ n + 1);
    int m = 1;
    for (int i = 2; i <= n; i++) {
        if (vsort[m] != vsort[i]) {
            vsort[++m] = vsort[i];
        }
    }
    vsort[m + 1] = vsort[m];
    return m;
}

int Rank(int n, int num) {
    int ans = 0;
    int l = 1, r = n, mid;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (vsort[mid] >= num) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

void build(int l, int r, int i) {
    if (l < r) {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
    }
    length[i] = vsort[r + 1] - vsort[l];
    times[i] = 0;
    cover[i] = 0;
}

void up(int i) {
    if (times[i] > 0) {
        cover[i] = length[i];
    } else {
        cover[i] = cover[i << 1] + cover[i << 1 | 1];
    }
}

void add(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        times[i] += jobv;
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            add(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
    }
    up(i);
}

bool cmp(Line a,Line b){
    return a.a1<b.a1;
}

long scan(int n) {
    int m = prepare(n);
    build(1, m, 1);
    // �����и���
    // ������ʱ�����ͬһ��λ�õ�ɨ�����ж�����Ҳ����a[0] == b[0]ʱ
    // Ӧ���ȴ������串��+1��ɨ���ߣ�Ȼ���ٴ������串��-1��ɨ����
    // ��ȻͶӰ���Ȼ�Ƶ���仯�����´𰸴���
    // �����������ݲ�û�а����ⷽ��Ĳ���
    sort(line+ 1,line+ n + 1, cmp);
    long ans = 0;
    for (int i = 1, pre; i <= n; i++) {
        pre = cover[1];
        add(Rank(m, line[i].a2), Rank(m, line[i].a3) - 1, line[i].a4, 1, m, 1);
        ans += abs(cover[1] - pre);//ÿ���ۼӱ仯�ľ���ֵ
    }
    return ans;
}

long scanY(int n) {
    for (int i = 1, j = 1 + n, x1, y1, x2, y2; i <= n; i++, j++) {
        x1 = rec[i][0]; y1 = rec[i][1]; x2 = rec[i][2]; y2 = rec[i][3];
        vsort[i] = y1; vsort[j] = y2;
        line[i].a1 = x1; line[i].a2 = y1; line[i].a3 = y2; line[i].a4 = 1;
        line[j].a1 = x2; line[j].a2 = y1; line[j].a3 = y2; line[j].a4 = -1;
    }
    return scan(n << 1);
}

long scanX(int n) {
    for (int i = 1, j = 1 + n, x1, y1, x2, y2; i <= n; i++, j++) {
        x1 = rec[i][0]; y1 = rec[i][1]; x2 = rec[i][2]; y2 = rec[i][3];
        vsort[i] = x1; vsort[j] = x2;
        line[i].a1 = y1; line[i].a2 = x1; line[i].a3 = x2; line[i].a4 = 1;
        line[j].a1 = y2; line[j].a2 = x1; line[j].a3 = x2; line[j].a4 = -1;
    }
    return scan(n << 1);
}


long compute(int n) {
    return scanY(n) + scanX(n);//ɨ����
}

int main()
{
    int n ;
    cin>>n;
    for (int i = 1; i <= n; i++) {
        // ���½��±�
        cin>>rec[i][0];
        cin>>rec[i][1];
        // ���Ͻ��±�
        cin>>rec[i][2];
        cin>>rec[i][3];
    }
    cout<<compute(n)<<endl;
}


