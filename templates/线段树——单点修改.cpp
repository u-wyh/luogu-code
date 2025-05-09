#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int bombStarts[MAXN<<2],bombEnds[MAXN<<2];
int n,m;

void up(int i){
    bombStarts[i] = bombStarts[i << 1] + bombStarts[i << 1 | 1];
    bombEnds[i] = bombEnds[i << 1] + bombEnds[i << 1 | 1];
}

void build(int l, int r, int i) {
    if(l<r){
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
    }
}

void add(int jobt, int jobi, int l, int r, int i) {
    if (l == r) {
        if (jobt == 0) {
            bombStarts[i]++;
        } else {
            bombEnds[i]++;
        }
    } else {
        int mid = (l + r) >> 1;
        if (jobi <= mid) {
            add(jobt, jobi, l, mid, i << 1);
        } else {
            add(jobt, jobi, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

// jobt==0��ʾ�ڲ�ѯ[jobl ~ jobr]��Χ���ж��ٵ��׷�Χ�Ŀ�ͷ
// jobt==1��ʾ�ڲ�ѯ[jobl ~ jobr]��Χ���ж��ٵ��׷�Χ�Ľ�β
int query(int jobt, int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return jobt == 0 ? bombStarts[i] : bombEnds[i];
    } else {
        int mid = (l + r) >> 1;
        int ans = 0;
        if (jobl <= mid) {
            ans += query(jobt, jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid) {
            ans += query(jobt, jobl, jobr, mid + 1, r, i << 1 | 1);
        }
        return ans;
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int op,l,r;
        cin>>op>>l>>r;
        if(op==1){
            add(0,l,1,n,1);
            add(1,r,1,n,1);
        }else{
            cout<<query(0,1,r,1,n,1)-(l==1?0:query(1,1,l-1,1,n,1))<<endl;
        }
    }
    return 0;
}
