#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int help[MAXN];//ֻ��Ҫ��x�±���ɢ��
struct node{
    int x,y;
}nums[MAXN];

int tree1[MAXN];//�ϰ벿�ֵ��±��x��ص���״����
int tree2[MAXN];//�°벿�ֵ��±��x��ص���״����

bool cmp(node a,node b){
    return a.y<b.y;
}

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int lowbit(int x){
    return x&(-x);
}

inline int find(int val){
    int l=1,r=m,ans=m;
    while(l<=r){
        int mid=(l+r)/2;
        if(help[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

void add(int *tree,int x,int val){
    while(x<=m){
        tree[x]+=val;
        x+=lowbit(x);
    }
}

int query(int *tree,int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

bool check(int limit){
    for(int i=1;i<=m;i++){
        tree1[i]=tree2[i]=0;
    }
    for(int i=1;i<=n;i++){
        //�����ʾ����һ��ʼ���еĶ����ϰ벿��
        add(tree1,nums[i].x,1);
    }
    int cnt1=n,cnt2=0;//cnt1��ʾ�����ж��ٸ�  cnt2��ʾ����
    int x1=1,x2=n;//��ʾö������������x
    for(int i=1,j=1;i<=n;i=j){
        //ö��ÿһ��y  ͨ��ţ��y����  j��ʾ��һ���͵�ǰö�ٵ���ţy�±겻һ����
        while(nums[i].y==nums[j].y){
            //��ʾ�����з���Ҫ����±��ţ������ɾȥ
            add(tree1,nums[j].x,-1),add(tree2,nums[j].x,1);
            j++;
            cnt1--,cnt2++;
        }
        //�ҵ���һ��xʹ�����Ͽ�������Ҫ��
        while(x1<=n&&query(tree1,x1)<=limit){
            x1++;
        }
        x1--;//Ҫ����һ��
        //�ҵ���һ��xʹ�����¿�������Ҫ��
        while(x2&&query(tree2,x2)>limit){
            x2--;
        }
        //����Ҫ�ر�ע��һ��Ϊʲôx1 x2�ı仯��һ�� һ���Ӵ�С һ����С����
        //��Ϊyһֱ��������  �ϲ���һ���𽥼��� ���ϲ���Ҳ����� ����x��С����  �Ӷ�ά�����ϲ����������ȶ�
        //���²���������  ���x���Ǵ�С���� ��ô����x��Ҫ����  ��Ϊ�²�������������ر�� ����x�ڸ�С��ʱ��Ϳ���

        int x=min(x1,x2);
        if(cnt1-query(tree1,x)<=limit&&cnt2-query(tree2,x)<=limit)
            return true;
    }
    return false;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i].x=read(),nums[i].y=read();
        help[i]=nums[i].x;
    }
    sort(nums+1,nums+n+1,cmp);
    sort(help+1,help+n+1);
    for(int i=1;i<=n;i++){
        if(help[i]!=help[i-1]){
            help[++m]=help[i];
        }
    }
    for(int i=1;i<=n;i++){
        nums[i].x=find(nums[i].x);
    }
    int l=n/4,r=n,ans=n;
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    cout<<ans<<endl;
    return 0;
}