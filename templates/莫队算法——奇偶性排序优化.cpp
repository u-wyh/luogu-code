//P2709
//�������Ī���㷨��ģ����  ��������ż�������Ż�
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;

int n,m,k;
struct node{
    int l,r,sub;
}nums[MAXN];
int arr[MAXN];
int pos[MAXN],cnt[MAXN];
long long ans[MAXN];
long long res;//�������  Ҳ���Ǵ�

//��ż�������Ż�
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

void Add(int n){
    //��һ�����ּ���  �����㹱��
    cnt[arr[n]]++;
    res+=(cnt[arr[n]]*cnt[arr[n]]-(cnt[arr[n]]-1)*(cnt[arr[n]]-1));
}

void Sub(int n){
    //��ȥһ������   ������Ӱ��
    cnt[arr[n]]--;
    res-=((cnt[arr[n]]+1)*(cnt[arr[n]]+1)-cnt[arr[n]]*cnt[arr[n]]);
}

int main()
{
    cin>>n>>m>>k;
    int siz=sqrt(n);//ȷ����Ĵ�С
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        pos[i]=i/siz;//ȷ��������Ϣ
    }
    for(int i=1;i<=m;i++){
        cin>>nums[i].l>>nums[i].r;
        nums[i].sub=i;
    }
    sort(nums+1,nums+m+1,cmp);
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
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
