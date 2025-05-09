//P8099
//�����Ŀ��һ���ǳ��õ���Ŀ  �õ�����״���� �߶��� ���������
//��ɢ������Ҳ�Ǻܶ��ص� ��ʹ��ֵ��ͬ ����λ�ò�ͬ  Ч����ͬ
//���� �Oai??aj?�O>K �����޷������������������������λ���ǹ̶��ġ�����֮�������� i<j ����ô ai? ʼ�ջ��� aj? ǰ�档
//�������������� (i,j) �����ǽ� i �� j ��һ������ߣ�������ĿҪ�����������򼴿ɡ�
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,k;

int arr[MAXN];//ԭʼ����
int val[MAXN];//��������
int in[MAXN];//�������

map<int,int>vis;//��������ڼ�¼�����˶��ٴ�  ������ɢ��

//�߶�������
pair<int,int>tree[MAXN<<2];//��һ�������� �ڶ�����������ʱ�����
int tag[MAXN<<2];//���������

//��״���鲿��
int bit[MAXN];//���ڴ������

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

//��״����
int lowbit(int x){
    return x&(-x);
}

void add(int x,int v){
    while(x<=n){
        bit[x]+=v;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=bit[x];
        x-=lowbit(x);
    }
    return ans;
}

//�߶�������
void up(int i){
    if(tree[i<<1].second<tree[i<<1|1].second){
        tree[i]=tree[i<<1];
    }
    else if(tree[i<<1].second>tree[i<<1|1].second){
        tree[i]=tree[i<<1|1];
    }
    else{
        tree[i].second=tree[i<<1].second;//��������һ����
        tree[i].first=min(tree[i<<1].first,tree[i<<1|1].first);
        //�������һ��  ��ôѡ���Ž�С��  ��Ϊ���С��һ���ȴ������
    }
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]={l,in[l]};
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void lazy(int i,int v){
    tag[i]+=v;
    tree[i].second+=v;
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobr<jobl){
        return ;
    }
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv);
        return ;
    }
    else{
        down(i);
        int mid=(l+r)/2;
        if(jobl<=mid)
            update(jobl,jobr,jobv,l,mid,i<<1);
        if(jobr>mid)
            update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        up(i);
    }
}

int main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
        val[i]=arr[i];
    }

    //��ɢ��  ��ʹ��ȵ�  ҲҪ��ɲ�ͬ���  �����õ��˼�������
    sort(arr+1,arr+n+1);
    for(int i=1;i<=n;i++){
        vis[val[i]]++;
        val[i]=lower_bound(arr+1,arr+n+1,val[i])-arr+vis[val[i]]-1;
        //��ʱ��val[i]�ǰ��մ�С���� �������һ���� λ��С�ı��С
    }

    //������ɢ��������Ŷ�Ӧ�ĵ�����
    //��һ����������  ��״����
    for(int i=1;i<=n;i++){
        int x = lower_bound(arr + 1, arr + n + 1, arr[val[i]] - k) - arr - 1;
        int y = lower_bound(arr + 1, arr + n + 1, arr[val[i]] + k + 1) - arr - 1;
        //x y �Լ������ڵ�����  ���Ƿ��ϵ�ǰ�ڵ�ķ�Χ
        in[val[i]]=(i-1)-(query(y)-query(x));
        //������ȼ��㹫ʽ��  ǰ������(i-1)������  (query(y)-query(x))��ʾ���Ƿ���Ҫ����ж���
        //��ôʣ�µľ��ǻ�ָ��ýڵ�����ָ���
        add(val[i],1);
        //cout<<x<<' '<<y<<' '<<in[val[i]]<<endl;
    }

    //��������
    build(1,n,1);//��������ڵ�������ɢ����ı��

    for(int i=1;i<=n;i++){
        int u=tree[1].first;
        cout<<arr[u]<<endl;

        int x = lower_bound(arr + 1, arr + n + 1, arr[u] - k) - arr - 1;
        int y = lower_bound(arr + 1, arr + n + 1, arr[u] + k + 1) - arr - 1;

        update(1,x,-1,1,n,1);
        update(y+1,n,-1,1,n,1);//�����������ָ��Ľڵ������һ  ��Ϊ���Լ�λ��֮ǰ���Ѿ�ȫ�������
        //�������ǲ������ٴ����  ���Կ��Խ����е�ֻҪ��ֵ���Լ��������ߵķ�Χ�ڵĵ�ȫ��������һ

        update(u,u,n,1,n,1);//��Ϊÿ��������һ������ ����Ϊn  ��һ�������������
    }
    return 0;
}