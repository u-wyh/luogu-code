//P7261
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int MAXM = 1e4+5;
const int MAXC = 1e4+5;

int n,m,c;
struct node{
    int l,r,id,k;
}nums[MAXM];
int arr[MAXN];
int pos[MAXN];
int cnt[MAXC];
int ans[MAXM];

//��ż�������Ż�
bool cmp(node a,node b) {
	return (pos[a.l] ^ pos[b.l]) ? pos[a.l] < pos[b.l] : ((pos[a.l] & 1) ? a.r < b.r : a.r > b.r);
}
//������˵���ͬһ����������䣬�Ҷ˵㰴�������У���֮�����������Ҳ�ǿ���û�ã���ʵ��Ч��������

int main()
{
    cin>>n>>c;
    int siz=sqrt(n);
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        pos[i]=i/siz;
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>nums[i].l>>nums[i].r;
        nums[i].k=nums[i].r-nums[i].l+1;
        nums[i].id=i;
    }
    sort(nums+1,nums+m+1,cmp);
    int l=1,r=0;
    for(int i=1;i<=m;i++){
        while(nums[i].l<l) cnt[arr[--l]]++;
        while(nums[i].r>r) cnt[arr[++r]]++;
        while(nums[i].l>l) cnt[arr[l++]]--;
        while(nums[i].r<r) cnt[arr[r--]]--;
        int k=nums[i].k/2+1;
        for(int j=1;j<=c;j++){
            if(cnt[j]>=k){
                ans[nums[i].id]=j;
                break;
            }
        }
    }
    for(int i=1;i<=m;i++){
        if(ans[i]){
            cout<<"yes "<<ans[i]<<endl;
        }
        else{
            cout<<"no"<<endl;
        }
    }
    return 0;
}
