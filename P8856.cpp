#include<bits/stdc++.h>
using namespace std;
const int MAXN = 60001;

int arr[MAXN];
int Min[MAXN << 2];
int add[MAXN << 2];
int n,m,s;

void up(int i) {
    Min[i] = min(Min[i << 1] ,Min[i << 1 | 1]);
}

void lazy(int i, int v) {
    Min[i] += v;
    add[i] += v;//��������ʾ�Ƿ�����Ϣ�������´���
}

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
        Min[i] = arr[l];
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    add[i]=0;
}

void Add(int jobl, int jobr, int jobv, int l, int r, int i) {
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

int query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return Min[i];
    }
    int mid = (l + r) >> 1;
    down(i);
    int ans = 0;
    if (jobl <= mid) {
        ans =min(ans, query(jobl, jobr, l, mid, i << 1));
    }
    if (jobr > mid) {
        ans =min(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));
    }
    return ans;
}

int main()
{
    cin>>n>>s>>m;
    for(int i=1;i<=n;i++)
        arr[i]=s;
    build(1,n,1);
    for (int i = 1, jobl, jobr, jobv; i <= m; i++) {
        cin>>jobl>>jobr>>jobv;
        if(jobv>query(jobl,jobr,1,n,1)){
            cout<<'N'<<endl;
        }else{
            cout<<'T'<<endl;
            Add(jobl,jobr,-jobv,1,n,1);
        }
    }
    return 0;
}


