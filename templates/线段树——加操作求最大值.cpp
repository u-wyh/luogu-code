//��������и��²������������ֵ
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

long arr[MAXN];
long Max[MAXN << 2];
long add[MAXN << 2];
int n,m;

//�Ƚ������������ֵ
void up(int i) {
    Max[i] = max(Max[i << 1] ,Max[i << 1 | 1]);
}

// ��ǰ�������Ӧ����Ϣ�±���i
// �����յ�һ������������ : ������䷶Χ��ÿ�����ֱ�Ϊv
// ��������������п���������Χ�ѵ�ǰ�߶�����Χȫ���ǵ��µ�
// Ҳ�п����Ǹ���Χ������Ϣ�·�������
// ��֮���߶�����ǰ��Χ��Max�����change   update���������
// �Ͳ��ټ��������·��ˣ���ס��
void lazy(int i, long v) {
    Max[i] += v;
    add[i] += v;//��������ʾ�Ƿ�����Ϣ�������´���
}

// ����Ϣ���·�
void down(int i) {
    if (add[i] != 0) {
        // ����
        lazy(i << 1, add[i]);
        // ����
        lazy(i << 1 | 1, add[i]);
        // ����Χ����Ϣ���
        add[i] = 0;
    }
}

void build(int l, int r, int i) {
    if (l == r) {
        Max[i] = arr[l];
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    add[i]=0;//��ʼ��ÿһ��λ�ö�û�����´��ݵ���Ϣ
}

// ��Χ�޸�
// jobl ~ jobr��Χ��ÿ�����ֱ�Ϊjobv
void Add(int jobl, int jobr, long jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy(i, jobv);
    } else {
        int mid = (l + r) >> 1;
        down(i);
        if (jobl <= mid) {
            Add(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid) {
            Add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);//�����޸�����
    }
}

long query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return Max[i];
    }
    int mid = (l + r) >> 1;
    down(i);
    long ans = 0;
    if (jobl <= mid) {
        ans =max(ans, query(jobl, jobr, l, mid, i << 1));
    }
    if (jobr > mid) {
        ans =max(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));
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