//��������и��²������������ֵ
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

long arr[MAXN];
long sum[MAXN << 2];
long Max[MAXN<<2];
int n,m;

//�Ƚ������������ֵ
void up(int i) {
    sum[i] = sum[i << 1]+sum[i << 1 | 1];
    Max[i] = max(Max[i << 1] ,Max[i << 1 | 1]);
}

void build(int l, int r, int i) {
    if (l == r) {
        sum[i] = arr[l];
        Max[i] = arr[l];
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
}

// sqrt����������ĵ�
// ע��ͳ����߶�����һ��������û�������£�Ҳ�Ͳ���Ҫ��down����
// ֻ�и��ݷ�Χ���ֵ��Ϣ�ļ�֦
// ʱ�临�Ӷȵķ������ǿ��Ͻ������ܷ���
// ���þ��ᵥ�ε��õĸ��Ӷ�
// ���µ����ٶ��sqrt�������ܵ�ʱ�临�Ӷ�Ҳ����O(n * 6 * logn)
void Sqrt(int jobl, int jobr, int l, int r, int i) {
    if (l == r) {
        long sqrt1 = (long) sqrt(Max[i]);
        sum[i] = sqrt1;
        Max[i] = sqrt1;
    } else {
        int mid = (l + r) >> 1;
        if (jobl <= mid && Max[i << 1] > 1) {
            Sqrt(jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid && Max[i << 1 | 1] > 1) {
            Sqrt(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

long query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    long ans = 0;
    if (jobl <= mid) {
        ans +=query(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid) {
        ans +=query(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>arr[i];
    build(1,n,1);
    cin>>m;
    long jobv;
    for (int i = 1, op, jobl, jobr; i <= m; i++) {
        cin>>op;
        cin>>jobl;
        cin>>jobr;
        if(jobl>jobr){
            int tmp=jobl;
            jobl=jobr;
            jobr=tmp;
        }
        if (op == 0) {
            Sqrt(jobl, jobr, 1, n, 1);
        } else {
            cout<<query(jobl, jobr, 1, n, 1)<<endl;
        }
    }
    return 0;
}

