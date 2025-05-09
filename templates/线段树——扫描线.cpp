// ���������
// �������� : https://www.luogu.com.cn/problem/P5490
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 300001;

int rec[MAXN][4];
struct Line{
    int a1,a2,a3,a4;
}line[MAXN];
//y��������Ҫ��ɢ��
int ysort[MAXN];
// �߶���ĳ��Χ�ܳ���
int length[MAXN << 2];
// �߶���ĳ��Χ���ǳ���
int cover[MAXN << 2];
// �߶���ĳ��Χ���Ǵ���
int times[MAXN << 2];

int prepare(int n) {
    sort(ysort+1,ysort+ n + 1);
    int m = 1;
    for (int i = 2; i <= n; i++) {
        if (ysort[m] != ysort[i]) {
            ysort[++m] = ysort[i];
        }
    }
    ysort[m + 1] = ysort[m];//��һ�����ݷ�ֹԽ��
    return m;
}
//ʵ��Ԫ�ص�ȥ��

int Rank(int n, int num) {
    int ans = 0;
    int l = 1, r = n, mid;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (ysort[mid] >= num) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}
//���ַ������Ӧ�±�

void build(int l, int r, int i) {
    if (l < r) {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
    }
    length[i] = ysort[r + 1] - ysort[l];
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

// ����������������
// 1) ��ѯ������Զ�����������Χ��������С��Χ�Ĳ�ѯ��ÿ�ζ�����cover[1]
// 2) ���Ӳ���֮�󣬺���һ�����еȹ�ģ�ļ��ٲ���
// ���������������������Ҫ�����»���
// ���ȵ�һ���޸���ɴ������Ϸ���ʱ��up�����ܱ�֤���Ϸ���cover[1]���޸���ȷ��
// ͬʱ�κ�һ�����Ӳ������漰���߶�����Χ������һ���ܱ��ȹ�ģ�ļ��ٲ���ȡ����
// �����ص�ͼ�����������
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

long compute(int n) {
    for (int i = 1, j = 1 + n, x1, y1, x2, y2; i <= n; i++, j++) {
        x1 = rec[i][0]; y1 = rec[i][1]; x2 = rec[i][2]; y2 = rec[i][3];
        ysort[i] = y1; ysort[j] = y2;
        line[i].a1 = x1; line[i].a2 = y1; line[i].a3 = y2; line[i].a4 = 1;//��ʼλ�� ��ֹλ�� Ч��
        line[j].a1 = x2; line[j].a2 = y1; line[j].a3 = y2; line[j].a4 = -1;
        //һ������������
    }
    n <<= 1;
    int m = prepare(n);
    build(1, m, 1);
    sort(line+1,line+ n + 1,cmp);
    long ans = 0;
    for (int i = 1, pre = 0; i <= n; i++) {
        ans += (long) cover[1] * (line[i].a1 - pre);
        //ÿһ�����仯��ʱ�򶼼���һ����һ�����򣨿����Ƕ�����Σ������������  �����˿�
        //���������  ��ʾ�����Χ�ж��ٱ�����
        //pre����һ�ε����
        //���cover[1]�Ǵ�ʱ�ܵĸ��ǳ���
        pre = line[i].a1;
        add(Rank(m, line[i].a2), Rank(m, line[i].a3) - 1, line[i].a4, 1, m, 1);
        // ����ļӲ���
    }
    return ans;
}

int main()
{
    int n;
    cin>>n;
    for (int i = 1; i <= n; i++) {
        // ���½��±�
        cin>>rec[i][0];
        cin>>rec[i][1];
        // ���Ͻ��±�
        cin>>rec[i][2];
        cin>>rec[i][3];
    }
    cout<<compute(n);
    return 0;
}
