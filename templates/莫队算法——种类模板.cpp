//P3901   ������
//Ī���㷨����������  ������cnt��Ƶͳ������
//�����Ƶ��0��1  ���� ��1��0 ���ǻ�Ӱ���
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m,k;
struct node{
    int l,r,k,sub;
}nums[MAXN];
int arr[MAXN];
int pos[MAXN],cnt[MAXN];
int ans[MAXN];
int res;//�������  Ҳ���Ǵ�

//��ż�������Ż�
//������˵���ͬһ����������䣬�Ҷ˵㰴�������У���֮�����������Ҳ�ǿ���û�ã���ʵ��Ч��������
bool cmp2(node a,node b) {
	return (pos[a.l] ^ pos[b.l]) ? pos[a.l] < pos[b.l] : ((pos[a.l] & 1) ? a.r < b.r : a.r > b.r);
}

bool cmp(node a,node b){
    if(pos[a.l]==pos[b.l]){
        return a.r<b.r;
    }
    else{
        return pos[a.l]<pos[b.l];
    }
}

bool cmp1(node a,node b){
    return a.sub<b.sub;
}

void Add(int n){
    //��һ�����ּ���  �����㹱��
    cnt[arr[n]]++;
    if(cnt[arr[n]]==1){
        res++;
    }
}

void Sub(int n){
    //��ȥһ������   ������Ӱ��
    cnt[arr[n]]--;
    if(cnt[arr[n]]==0){
        res--;
    }
}

int main()
{
    cin>>n>>m;
    int siz=sqrt(n);//ȷ����Ĵ�С
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        pos[i]=i/siz;//ȷ��������Ϣ
    }
    for(int i=1;i<=m;i++){
        cin>>nums[i].l>>nums[i].r;
        nums[i].k=nums[i].r-nums[i].l+1;
        nums[i].sub=i;
    }
    sort(nums+1,nums+m+1,cmp2);
    //����������
    //���������ͬ  �����Ҷ˵�����  ���������С����
    int l=1,r=0;
    for(int i=1;i<=m;i++){
        while(nums[i].l<l) Add(--l);
        while(nums[i].r>r) Add(++r);
        while(nums[i].l>l) Sub(l++);
        while(nums[i].r<r) Sub(r--);
        //ƥ������  �õ���
        ans[nums[i].sub]=res;
    }
    sort(nums+1,nums+m+1,cmp1);
    for(int i=1;i<=m;i++){
        if(ans[i]==nums[i].k){
            cout<<"Yes"<<endl;
        }
        else{
            cout<<"No"<<endl;
        }
    }
    return 0;
}