#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m;

int arr[MAXN];
struct node{
    int l,r,id;
}nums[MAXN];

int last[MAXN];//��¼�ϴ���ɫ���ֵ�λ��
int pre[MAXN];//��¼��ǰ�ڵ�i����ɫ������������  ����Ǳ��� ����Ϊ0
//����  1 2 2 3 2 1  ��0 0 2 0 3 1
int ans[MAXN];//���ڼ�¼��

//�߶�������
//ע�⣺���Ҷ�ӽ��ܿط�Χ��0~n  ��׼ȷ����˵��0~n-1  ��ʾ����pre������iλ�ý����ĵ�ĸ���
int tree[MAXN<<2];

//��ѯ������Сֵ  �߶���
int segtree[MAXN<<2];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

//���²�����������Сֵ�߶����Ĳ���
void upmin(int i){
    segtree[i]=min(segtree[i<<1],segtree[i<<1|1]);
}

void update(int pos,int v,int l,int r,int i){
    if(l==r){
        segtree[i]=v;
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            update(pos,v,l,mid,i<<1);
        }
        else{
            update(pos,v,mid+1,r,i<<1|1);
        }
        upmin(i);
    }
}

int querymin(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return segtree[i];
    }
    else{
        int ans=INT_MAX;
        int mid=(l+r)/2;
        if(jobl<=mid){
            ans=min(ans,querymin(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=min(ans,querymin(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

//����ѯ���鰴���Ҷ˵�����
bool cmp(node a,node b){
    return a.r<b.r;
}

//���º������߶����Ĳ���
void up(int i){
    tree[i]=tree[i<<1]+tree[i<<1|1];
}

void add(int pos,int v,int l,int r,int i){
    if(l==r){
        tree[i]+=v;
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

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)/2;
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans;
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
        update(i,arr[i],1,n,1);
        if(last[arr[i]]==0){
            //�����һ����ɫ������ ��ô����0
            pre[i]=0;
        }
        else{
            if(querymin(last[arr[i]]+1,i,1,n,1)<arr[i]){
                //��ʾ�м���ڱ�����ɫ��С��
                pre[i]=0;
            }
            else{
                pre[i]=last[arr[i]];
            }
        }
        last[arr[i]]=i;
    }
    for(int i=1;i<=m;i++){
        nums[i].l=read(),nums[i].r=read();
        nums[i].id=i;
    }
    sort(nums+1,nums+m+1,cmp);
    int r=0;//��ʾ�����ƶ���������
    for(int i=1;i<=m;i++){
        while(r<nums[i].r){
            r++;
            add(pre[r],1,0,n,1);
        }
        int tmp=query(0,nums[i].l-1,0,n,1);
        ans[nums[i].id]=tmp-(nums[i].l-1);
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
