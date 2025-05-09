#include<bits/stdc++.h>
using namespace std;
const int LIMIT = 80001;

int n,m;
int cnt=1;
int Left[LIMIT];
int Right[LIMIT];
long sum[LIMIT];
long add[LIMIT];

void up(int h, int l, int r) {
    sum[h] = sum[l] + sum[r];
}

void lazy(int i, long v, int n) {
    sum[i] += v * n;
    add[i] += v;
}

void down(int i, int ln, int rn) {
    if (add[i] != 0) {
        // �����������·�
        // ����������Ŀռ���Ҫ׼����
        if (Left[i] == 0) {
            Left[i] = ++cnt;
        }
        if (Right[i] == 0) {
            Right[i] = ++cnt;
        }
        lazy(Left[i], add[i], ln);
        lazy(Right[i], add[i], rn);
        add[i] = 0;
    }
}

void Add(int jobl, int jobr, long jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy(i, jobv, r - l + 1);
    } else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) {
            // ���ò�ȥ���Ż�����
            if (Left[i] == 0) {
                Left[i] = ++cnt;
            }
            Add(jobl, jobr, jobv, l, mid, Left[i]);
        }
        if (jobr > mid) {
            // ���ò�ȥ�Ҳ�Ż�����
            if (Right[i] == 0) {
                Right[i] = ++cnt;
            }
            Add(jobl, jobr, jobv, mid + 1, r, Right[i]);
			}
        up(i, Left[i], Right[i]);
    }
}

long query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    long ans = 0;
    if (jobl <= mid) {
        // �������������ռ���б�Ҫȥ��ѯ
        // ���������û��������ռ��ǲ�ѯ�������0
        if (Left[i] != 0) {
            ans += query(jobl, jobr, l, mid, Left[i]);
        }
    }
    if (jobr > mid) {
        // �����Ҳ�������ռ���б�Ҫȥ��ѯ
        // ����Ҳ����û��������ռ��ǲ�ѯ�������0
        if (Right[i] != 0) {
            ans += query(jobl, jobr, mid + 1, r, Right[i]);
        }
    }
    return ans;
}

int main()
{
    cin>>n>>m;
    long k;
    for(int i=1,op,l,r;i<=m;i++){
        cin>>op>>l>>r;
        if(op==1){
            cin>>k;
            Add(l,r,k,1,n,1);
        }else{
            cout<<query(l,r,1,n,1)<<endl;
        }
    }
    return 0;
}
