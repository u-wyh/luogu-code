#include<bits/stdc++.h>
using namespace std;
#define int long long

long long a[100010],c[100010],top,n,t;

//int fun(long long num){
//    int l = 1, r = top, ans = 0; // �� ans ��ʼ��Ϊ 0����ʾ����Ҳ�����Ӧ�ò����λ��
//    while(l <= r){
//        int mid = l + (r - l) / 2; // �����������
//        if(c[mid] >= num){
//            ans = mid; // ���� ans Ϊ��ǰ mid����Ϊ c[mid] >= num
//            r = mid - 1; // ��������벿�ֲ���
//        } else {
//            l = mid + 1; // ���Ұ벿�ֲ���
//        }
//    }
//    return ans;
//}

int fun(long long num){
    int l=1,r=top,ans=0;
    while(l<=r){
        //cout<<666<<endl;
        int mid=l+(r-l)/2;
        if(c[mid]>num){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

signed main()
{
    long long p,v;
    cin>>n>>t;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld",&p,&v);
        a[i]=p+v*t;
    }
    for(int i=n;i>=1;i--)
    {
        if(!top||a[i]>=c[top])
            c[++top]=a[i];
        else{
            int t=fun(a[i]);
            //system("pause");
            c[t]=a[i];
        }
    }
    printf("%lld\n",top);
}
