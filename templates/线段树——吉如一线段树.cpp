#include<bits/stdc++.h>
using namespace std;

const int MAXN = 100001;
// �����ʼ�����е�ֵ������ֱ�LOWEST��С��ֵ
// ������²���ʱjobv����ֵҲ������ֱ�LOWEST��С��ֵ
int LOWEST = -100001;
// ԭʼ����
int arr[MAXN];
// �ۼӺ�
long sum[MAXN << 2];
// ���ֵ(���ǲ�ѯ��ϢҲ����������Ϣ�������Ѿ�������)
int Max[MAXN << 2];
// ���ֵ����
int cnt[MAXN << 2];
// �ϸ�δ�ֵ(second max)
int sem[MAXN << 2];

void up(int i) {
    int l = i << 1;
    int r = i << 1 | 1;
    sum[i] = sum[l] + sum[r];
    Max[i] = max(Max[l], Max[r]);
    if (Max[l] > Max[r]) {
        cnt[i] = cnt[l];
        sem[i] = max(sem[l], Max[r]);
    } else if (Max[l] < Max[r]) {
        cnt[i] = cnt[r];
        sem[i] = max(Max[l], sem[r]);
    } else {
        cnt[i] = cnt[l] + cnt[r];
        sem[i] = max(sem[l], sem[r]);
    }
}

// һ����û�е߸����δ�ֵ����������Ϣ�·���Ҳ����˵��
// ���ֵ��ѹ��v������v > �ϸ�δ�ֵ�������
// sum��max��ô����
void lazy(int i, int v) {
    if (v < Max[i]) {
        sum[i] -= ((long) Max[i] - v) * cnt[i];
        Max[i] = v;
    }
}

void down(int i) {
    lazy(i << 1, Max[i]);
    lazy(i << 1 | 1, Max[i]);
}

void build(int l, int r, int i) {
    if (l == r) {
        sum[i] = Max[i] = arr[l];
        cnt[i] = 1;
        sem[i] = LOWEST;
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
}

void setMin(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobv >= Max[i]) {
        return;
    }
    if (jobl <= l && r <= jobr && sem[i] < jobv) {
        lazy(i, jobv);
    } else {
        // 1) ����û��ȫ��
        // 2) jobv <= sem[i]
        down(i);
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            setMin(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            setMin(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

int queryMax(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return Max[i];
    }
    down(i);
    int mid = (l + r) >> 1;
    int ans = -1e9;
    if (jobl <= mid) {
        ans = max(ans, queryMax(jobl, jobr, l, mid, i << 1));
    }
    if (jobr > mid) {
        ans = max(ans, queryMax(jobl, jobr, mid + 1, r, i << 1 | 1));
    }
    return ans;
}

long querySum(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    down(i);
    int mid = (l + r) >> 1;
    long ans = 0;
    if (jobl <= mid) {
        ans += querySum(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        ans += querySum(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

int main()
{
    int n ;
    int t ;
    cin>>n>>t;
    for(int i=1;i<=n;i++)
        cin>>arr[i];
    build(1, n, 1);
    for (int i = 1, op, a, b, jobl, jobr, jobv; i <= t; i++) {
        cin>>op>>a>>b;
        jobl = min(a, b);
        jobr = max(a, b);
        if (op == 0) {
            cin>>jobv;
            setMin(jobl, jobr, jobv, 1, n, 1);
        } else if (op == 1) {
            int ans1 = queryMax(jobl, jobr, 1, n, 1);
            cout<<ans1<<endl;
        } else {
            long ans1 = querySum(jobl, jobr, 1, n, 1);
            cout<<ans1<<endl;
        }
    }
    return 0;
}
