#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int t,n,m,k;
int arr[MAXN],Sort[MAXN],tree[MAXN];

inline int lowbit(int x){
    return x&-x;
}

inline void add(int i, int v) {
    while (i <= m) {
        tree[i] += v;
        i += lowbit(i);
    }
}

// 1~i��Χ���ۼӺ�
inline int sum(int i) {
    int ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= lowbit(i);
    }
    return ans;
}

// ����ԭʼֵv
// ��������ֵ(���򲿷�1~m�е��±�)
inline int Rank(int v) {
	int l = 1, r = m, mid;
    int ans = 0;
    while (l <= r) {
        mid = (l + r) / 2;
        if (Sort[mid] >= v) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

inline bool check(long long  limit){
    int h=1;
    int i=m,R=m;
    long long  cnt=0;
    while(i>0){
        if(cnt+sum(arr[i]-1)<=limit){
            cnt+=sum(arr[i]-1);
            add(arr[i],1);
        }else{
            for(int j=i+1;j<=R;j++)
                add(arr[j],-1);
            R=i;
            h++;
            cnt=0;
            add(arr[i],1);
        }
        i--;
        if(h>k){
            return false;
        }
    }
    return true;
}

int main()
{
    cin>>t;
    while(t--){
        //memset(arr,0,sizeof(arr));
        memset(Sort,0,sizeof(Sort));
        //memset(tree,0,sizeof(tree));
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            cin>>arr[i];
            Sort[i]=arr[i];
        }
        sort(Sort+ 1,Sort+ n + 1);
        m = 1;
        for (int i = 2; i <= n; i++) {
            if (Sort[m] != Sort[i]) {
                Sort[++m] = Sort[i];
            }
        }
        //������ȥ��
        for (int i = 1; i <= n; i++) {
            arr[i] = Rank(arr[i]);
            //��ԭ�������ֵ��Ϊ�����������еĴ�С����  ԭ�е����ݱ�����û��ʲô��
            //���������������  �Լ���Լ�ռ�
        }
        long long  ans=1e10,l=0,r=1e10;
        while(l<=r){
            long long mid=l+(r-l)/2;
            if(check(mid)){
                ans=mid;
                r=mid-1;
                memset(tree,0,sizeof(tree));
            }else{
                l=mid+1;
                memset(tree,0,sizeof(tree));
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
