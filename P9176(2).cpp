#include <bits/stdc++.h>
#define N 200001
#define int long long//ʮ�� OI һ����
using namespace std;
int n,sum;
int v[N],a[N],b[N],c[N];
//��״����
void add(int x,int k){
    for (int i=x;i<=n;i+=i&(-i)){
        c[i]+=k;
    }
}
int qry(int x){
    int cnt=0;
    for (int i=x;i;i-=i&(-i)){
        cnt+=c[i];
    }
    return cnt;
}
int bin(){
    int l=1,r=n;
    while (l<=r){
        int mid=(l+r)>>1;
        if (qry(mid)>=(sum+1)/2){
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    return l;
}
signed main(){
    cin>>n;
    for (int i=1;i<=n;i++){
        cin>>v[i]>>a[i];
        b[i]=v[i];
    }
    sort(b+1,b+n+1);
    for (int i=1;i<=n;i++){
        v[i]=lower_bound(b+1,b+n+1,v[i])-b;//��ɢ��
        sum+=a[i];//���µ�ǰ����
        add(v[i],a[i]);//ά��ǰ׺��
        cout<<b[bin()]<<endl;//ע����ֵĴ�����ɢ����ģ���Ҫ��ԭ
    }
    return 0;
}
