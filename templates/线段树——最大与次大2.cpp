//P4087
// �����Ŀʹ�����ֵ�ʹδ�ֵ֮��Ĺ�ϵ  ���Ժܷ����ͳ�ƴ�
// ��ʲôʱ��𰸻����
// 1.rk1�������仯�ˣ�ԭ����rk1��һ��rk1�ˣ�
// ��1��rk1������ͷţ�����Ǳ仯��
// ��2��rk1������ͷţ����ȻҪ����Ƭ����
// ��3��rk1������ࣨrk1�����ˣ��ͺ����ţ���У�
// 2.rk1������û�䣨ԭ����rk1����rk1��
// ��1��rk1����û�䣨���Ǳ仯��
// ��2��rk1�������ˣ������ţ����ֱ׷��Ҫ�����Ƭ�����Ա仯��
// �ܽ�һ�� �𰸱仯����Ҫô��һ����ţ�����  Ҫô��һ���ĸ�������һ��  ����ţ����
// ��Ϊÿ�����ֻ������һͷţ�Ĳ���
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,g;
struct node{
    int pos;
    int mmax;
    int maxnum;
    int mmin;
    int minnum;//��ʾ�������ֺʹδ������ �Լ���Ŀ
}tree[MAXN<<2];
struct node1{
    int t,pos,v;
}nums[MAXN];
int m=1;
int tmp[MAXN];

bool cmp(node1 a,node1 b){
    return a.t<b.t;
}

int getrank(int v){
    int l=1,r=m,ans=1;
    while(l<=r){
        int mid=(l+r)/2;
        if(tmp[mid]>=v){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

void up(int i){
    if(tree[i<<1].mmax>tree[i<<1|1].mmax){
        tree[i].pos=tree[i<<1].pos;
        tree[i].mmax=tree[i<<1].mmax;
        tree[i].maxnum=tree[i<<1].maxnum;
        if(tree[i<<1].mmin>tree[i<<1|1].mmax){
            tree[i].mmin=tree[i<<1].mmin;
            tree[i].minnum=tree[i<<1].minnum;
        }
        else if(tree[i<<1].mmin==tree[i<<1|1].mmax){
            tree[i].mmin=tree[i<<1].mmin;
            tree[i].minnum=tree[i<<1].minnum+tree[i<<1|1].maxnum;
        }
        else{
            tree[i].mmin=tree[i<<1|1].mmax;
            tree[i].minnum=tree[i<<1|1].maxnum;
        }
    }
    else if(tree[i<<1].mmax<tree[i<<1|1].mmax){
        tree[i].pos=tree[i<<1|1].pos;
        tree[i].mmax=tree[i<<1|1].mmax;
        tree[i].maxnum=tree[i<<1|1].maxnum;
        if(tree[i<<1|1].mmin>tree[i<<1].mmax){
            tree[i].mmin=tree[i<<1|1].mmin;
            tree[i].minnum=tree[i<<1|1].minnum;
        }
        else if(tree[i<<1|1].mmin==tree[i<<1].mmax){
            tree[i].mmin=tree[i<<1|1].mmin;
            tree[i].minnum=tree[i<<1|1].minnum+tree[i<<1].maxnum;
        }
        else{
            tree[i].mmin=tree[i<<1].mmax;
            tree[i].minnum=tree[i<<1].maxnum;
        }
    }
    else {
        tree[i].pos=tree[i<<1].pos;
        tree[i].mmax=tree[i<<1].mmax;
        tree[i].maxnum=tree[i<<1].maxnum+tree[i<<1|1].maxnum;
        if(tree[i<<1].mmin>tree[i<<1|1].mmin){
            tree[i].mmin=tree[i<<1].mmin;
            tree[i].minnum=tree[i<<1].minnum;
        }
        else if(tree[i<<1].mmin==tree[i<<1|1].mmin){
            tree[i].mmin=tree[i<<1].mmin;
            tree[i].minnum=tree[i<<1].minnum+tree[i<<1|1].minnum;
        }
        else{
            tree[i].mmin=tree[i<<1|1].mmin;
            tree[i].minnum=tree[i<<1|1].minnum;
        }
    }
}

void build(int l,int r,int i){
    if(l==r&&l==m+1){
        tree[i].pos=l;
        tree[i].mmax=g;
        tree[i].maxnum=1;
        tree[i].mmin=-1;
        tree[i].minnum=0;
        return ;
    }
    if(l==r){
        tree[i].pos=l;
        tree[i].mmax=g;
        tree[i].maxnum=1;
        tree[i].mmin=0;
        tree[i].minnum=0;
        return;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void add(int pos,int v,int l,int r,int i){
    if(l==r){
        tree[i].mmax+=v;
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            add(pos,v,l,mid,i<<1);
        }
        else{
            add(pos,v,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int main()
{
    cin>>n>>g;
    for(int i=1;i<=n;i++){
        cin>>nums[i].t>>nums[i].pos>>nums[i].v;
        tmp[i]=nums[i].pos;
    }
    sort(tmp+1,tmp+n+1);
    sort(nums+1,nums+n+1,cmp);
    // ��ɢ��
    for(int i=2;i<=n;i++){
        if(tmp[i]!=tmp[i-1]){
            tmp[++m]=tmp[i];
        }
    }
    for(int i=1;i<=n;i++){
        nums[i].pos=getrank(nums[i].pos);
    }
    m++;
    build(1,m,1);
    int ans=0,prenum=0,premax=0,prepos;
    for(int i=1;i<=n;i++){
        prepos=tree[1].pos;
        premax=tree[1].mmax;
        prenum=tree[1].maxnum;
        add(nums[i].pos,nums[i].v,1,m,1);
        if(prenum!=tree[1].maxnum){
            ans++;
        }
        else if(prenum==1&&prepos!=tree[1].pos){
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}
//�����Ǹ�ţ�Ĳ��������˱仯  �����������  ʵ�����ǲ����Ӵ𰸵�