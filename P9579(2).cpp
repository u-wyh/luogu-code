#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;

int n,cnt=0;
struct node{
    int a,b;
}nums[MAXN];

bool cmp(node a,node b){
    return a.b==b.b?a.a<b.a:a.b<b.b;
}

signed main()
{
    cin>>n;
    int maxn=0;
    for(int i=1;i<=n;i++){
        int a,b;
        cin>>a>>b;
        maxn=max(maxn,max(a,b));
        if(a>b){
            nums[++cnt].a=a;
            nums[cnt].b=b;
        }
    }
    sort(nums+1,nums+cnt+1,cmp);
    int ans=LLONG_MAX,sum=0,lasa=0;
    for(int i=1;i<=cnt;i++){
        ans=min(ans,sum+maxn-nums[i].b);
        //�൱��ÿ�ε���i i�Ժ��ȫ���ǵڶ��ַ���  ���ȵ����Ȼ�����
        //ans��¼������i֮ǰ  ��С�Ļ����Ƕ���
		sum+=2*(max(0ll,nums[i].a-max(lasa,nums[i].b)));
		//���� ��5,1����7,3��  Ӧ���Ǳ�Ϊ��7,1������5,1��+��7��5��  ��Ϊ5����3
		lasa=max(lasa,nums[i].a);
    }
    ans=min(sum,ans)+maxn;
    cout<<ans<<endl;
    return 0;
}
