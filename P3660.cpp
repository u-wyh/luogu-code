//P3660
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 50005;

struct node{
    int a,b,l;
}arr[MAXN];
int tree[MAXN<<1];
int n;

int lowbit(int i){
    return i&-i;
}

void add(int i,int v){
    while(i<=2*n){
        tree[i]+=v;
        i+=lowbit(i);
    }
}

int sum(int i){
    int ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
    }
    return ans;
}

bool cmp(node a,node b){
    return a.l>b.l;
}

int main()
{
    cin>>n;
    for(int i=1;i<=2*n;i++){
        int u;
        cin>>u;
        if(arr[u].a){
            arr[u].b=i;
        }
        else{
            arr[u].a=i;
        }
    }
    for(int i=1;i<=n;i++){
        arr[i].l=arr[i].b-arr[i].a;//根据区间长度排序
    }
    sort(arr+1,arr+n+1,cmp);
    //区间长度大的在前  那么后来的区间如果和之前的有联系 那么要么是完全被之前的区间包含 要么是包含了以前区间的一个端点
    long long ans=0;
    for(int i=1;i<=n;i++){
        ans+=sum(arr[i].b)-sum(arr[i].a);
        add(arr[i].a,1);
        add(arr[i].b,1);
    }
    cout<<ans<<endl;
    return 0;
}
