//P5268
//��������õ��˲��  ����Ҫ����ʽ�����
//������Ҫ����� 1��l  �����ϵ����ִ�Ƶ  �� 1��r  ��������Ӧ���ִ�Ƶ�ĳ˻�֮��
//��ô����ⲻ���� l��r  �����ϵ����ִ�Ƶ  ���Բ�ʹ��һ���ģ��  ��Ҫ�Լ���д
//���ÿ����һ����  ��ô�Դ𰸵Ĺ��׾����ұ���Ӧ���ֵĴ�Ƶ
//û����һ������  �Դ𰸵�Ӱ������ұ���Ӧ���ֵĴ�Ƶ
//���Ǹ��ݴ˽���Ī��
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e4+5;

int n,m;
struct node{
    int l,r,id,op;
}nums[MAXN<<2];
int cnt=0;
int arr[MAXN];
int pos[MAXN];
int cntl[MAXN],cntr[MAXN];
int res;
int ans[MAXN];

//��ż�������Ż�
bool cmp(node a,node b) {
	return (pos[a.l] ^ pos[b.l]) ? pos[a.l] < pos[b.l] : ((pos[a.l] & 1) ? a.r < b.r : a.r > b.r);
}
//������˵���ͬһ����������䣬�Ҷ˵㰴�������У���֮�����������Ҳ�ǿ���û�ã���ʵ��Ч��������

void Add(int op,int n){
    //��һ�����ּ���  �����㹱��
    if(op==1){
        //�ж�����߼��뻹���ұ߼���
        cntl[arr[n]]++;
        res+=cntr[arr[n]];
    }
    else{
        cntr[arr[n]]++;
        res+=cntl[arr[n]];
    }
}

void Sub(int op,int n){
    //��ȥһ������   ������Ӱ��
    if(op==1){
        cntl[arr[n]]--;
        res-=cntr[arr[n]];
    }
    else{
        cntr[arr[n]]--;
        res-=cntl[arr[n]];
    }
}

signed main()
{
    cin>>n;
    int siz=sqrt(n);
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        pos[i]=i/siz;
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        int l1,r1,l2,r2;
        cin>>l1>>r1>>l2>>r2;
        nums[++cnt]={r1,r2,i,1};
        nums[++cnt]={r1,l2-1,i,-1};
        nums[++cnt]={l1-1,r2,i,-1};
        nums[++cnt]={l1-1,l2-1,i,1};
    }
    for(int i=1;i<=cnt;i++){
        if(nums[i].l>nums[i].r){
            int temp=nums[i].l;
            nums[i].l=nums[i].r;
            nums[i].r=temp;
        }
    }
    sort(nums+1,nums+cnt+1,cmp);
    int l=0,r=0;
    for(int i=1;i<=cnt;i++){
        while(nums[i].l<l) Sub(1,l--);
        while(nums[i].r>r) Add(-1,++r);
        while(nums[i].l>l) Add(1,++l);
        while(nums[i].r<r) Sub(-1,r--);
        //ע�����������䲻��l��r  ����1��l��1��r  ����������������
        //ƥ������  �õ���
        if(nums[i].op==1){
            ans[nums[i].id]+=res;
        }
        else{
            ans[nums[i].id]-=res;
        }
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}