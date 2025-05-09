#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

long arr[MAXN];
long sum[MAXN << 2];
long add[MAXN << 2];
int n,m;

// �ۼӺ���Ϣ�Ļ���
void up(int i) {
    // ����Χ���ۼӺ� = ��Χ�ۼӺ� + �ҷ�Χ�ۼӺ�
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
}

// ����
void build(int l, int r, int i) {
    if (l == r) {
        sum[i] = arr[l];
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    add[i] = 0;
}

// ��ǰ����l~r��Χ����Ӧ����Ϣ�±���i����Χ�����ֵĸ�����n = r-l+1
// �����յ�һ������������ : l~r��Χ��ÿ����������v
// ��������������п���������Χ�ѵ�ǰ�߶�����Χȫ���ǵ��µ�
// Ҳ�п����Ǹ���Χ������Ϣ�·�������
// ��֮���߶�����ǰ��Χ��sum�����add���������
// �Ͳ��ټ��������·��ˣ���ס��
void lazy(int i, long v, int n) {
    sum[i] += v * n;
    add[i] += v;
}

// ����Ϣ���·�
void down(int i, int ln, int rn) {
    if (add[i] != 0) {
        // ����
        lazy(i << 1, add[i], ln);
        // ����
        lazy(i << 1 | 1, add[i], rn);
        // ����Χ����Ϣ���
        add[i] = 0;
    }
}

// ��Χ�޸�
// jobl ~ jobr��Χ��ÿ����������jobv
void Add(int jobl, int jobr, long jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy(i, jobv, r - l + 1);
    } else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) {
            Add(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            Add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);//�����޸�����
    }
}

// ��ѯ�ۼӺ�
long query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    long ans = 0;
    if (jobl <= mid) {
        ans += query(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        ans += query(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>arr[i];
    build(1,n,1);
    long jobv;
    for (int i = 1, op, jobl, jobr; i <= m; i++) {
        cin>>op;
        if (op == 1) {
            cin>>jobl;
            cin>>jobr;
            cin>>jobv;
            Add(jobl, jobr, jobv, 1, n, 1);
        } else {
            cin>>jobl;
            cin>>jobr;
            cout<<query(jobl, jobr, 1, n, 1)<<endl;
        }
    }
    return 0;
}
