#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e6+5;

int n,m;
int cnt;
int pos[MAXN];//��¼����Ҫ���ˮ��λ��
int dis[MAXN];//��¼��ʼʱĿ��ˮ����Ŀ���ľ���
int tot;
int ans[MAXN];//��¼���˳��
int del[MAXN];//��¼��Ŀ���ˮ��λ��


//�߶�������
int tree[MAXN<<2];//��¼�����������Խ�����λ������ľ���
int tag[MAXN<<2];

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

void up(int i){
    tree[i]=min(tree[i<<1],tree[i<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=dis[l];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void lazy(int i,int v){
    tree[i]-=v;
    tag[i]+=v;
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void update(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            update(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            update(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int l,int r,int i){
    if(l==r){
        tree[i]=1e9;//��ʾ��Ҳ����ѡ����
        return l;
    }
    else{
        int mid=(l+r)/2;
        down(i);
        int ans=0;
        if(!tree[i<<1|1]){
            //���Һ������Ŀ��λ�õ�
            ans=query(mid+1,r,i<<1|1);
        }
        else{
            ans=query(l,mid,i<<1);
        }
        up(i);//��Ϊ������һ���ڵ�
        return ans;
    }
}

int main()
{
    int p=1,sum=0;//p�ǵ�ǰ��ǰ������Ŀ���λ��  sumֻ���������del��������
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        int v=read();
        if((p<<1)==i){
            p=i;
        }
        if(v==m){
            //����Ҫ���
            pos[++cnt]=i;
            dis[cnt]=i-p;//�¼�һ������Ҫ���ˮ��
        }
        else{
            del[++sum]=i;
        }
    }
    build(1,cnt,1);
    sum=0;
    for(int i=1;i<=cnt;i++){
        //ÿ��һ�������һ��Ŀ��  ����cnt�ξ�һ������
        if(tree[1]){
            tag[1]+=tree[1];//������Ǹ�������tree[1]  ˵��һ��������һ����ô���
            //��ôһ���Ὣ��ǰ��ķ�Ŀ��ˮ���Ƴ� ��Ϊ���ǰ�治�Ƿ�Ŀ��  ��ô�������0
            for(int j=1;j<=tree[1];j++){
                ans[++tot]=del[++sum];
            }
            tree[1]=0;
        }
        int x=query(1,cnt,1);
        ans[++tot]=pos[x];
        if(x<cnt){
            //��ʾ������ڵ����Ľڵ�ǰ��һ��
            update(x+1,cnt,1,1,cnt,1);
        }
    }
    cout<<tot<<endl;
    for(int i=1;i<=tot;i++){
        cout<<ans[i]<<' ';
    }
    cout<<endl;
    return 0;
}
