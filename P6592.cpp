#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 5e5+5;
const int MAXT = MAXM*32;

int n,m,k,op;
int u[MAXM],v[MAXM];//����ⲻ��Ҫ���������ıߵ���Ϣ �����ý�ͼ
int cnt=0;
int tree[MAXT];//�ɳ־û��߶���  ����ֻ�и�������Ϣ�������õ�
int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int val[MAXN];//��ʾ�ڵ�i���ڵ�1�����еݼ�·������СȨֵ�����ֵ�Ƕ���
//����val[1]��ʼ��Ϊ���ֵ ���඼����Сֵ
int res,ans;//res����ͳ�ƴ�֮��

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

int build(int l,int r){
    int rt=++cnt;
    if(l==r){
        tree[rt]=val[l];//��ʼ��
    }
    else{
        int mid=(l+r)/2;
        ls[rt]=build(l,mid);
        rs[rt]=build(mid+1,r);
    }
    return rt;
}

int insert(int jobi, int l, int r, int i) {
    int rt = ++cnt;
    ls[rt] = ls[i];
    rs[rt] = rs[i];
    if(l==r){
        tree[rt]=val[l];
    }
    else{
        int mid = (l + r) / 2;
        if (jobi <= mid) {
            ls[rt] = insert(jobi, l, mid, ls[rt]);
        } else {
            rs[rt] = insert(jobi, mid + 1, r, rs[rt]);
        }
    }
    return rt;
}

int query(int pos,int l,int r,int i){
    if(l==r){
        return tree[i];
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            return query(pos,l,mid,ls[i]);
        }
        else{
            return query(pos,mid+1,r,rs[i]);
        }
    }
}

int main()
{
    n=read(),m=read(),k=read(),op=read();
    for(int i=1;i<=m;i++){
        u[i]=read(),v[i]=read();
    }
    for(int i=1;i<=n;i++){
        val[i]=INT_MIN;
    }
    val[1]=INT_MAX;
    root[0]=build(1,n);
    for(int i=1;i<=m;i++){
        val[u[i]]=max(val[u[i]],min(i,val[v[i]]));
        //��仰�ĺ����� ��������һ����  ��u[i]��v[i]  ��Ȩ��i
        //�����ߵ����ӿ��ܻᵼ��val[u[i]]�����˱仯 Ҳ���ܲ��仯
        //��ôҪô��v��ǰ��1��ͨ��  �Ӷ�����u����һ����1��·  �����ᵼ�±仯
        //Ҳ�п�����vû����ͨ ��ô����INT_MIN  ����Ӱ���  ���������߶Դ�û��Ӱ��
        //֮����i��val[v[i]]Ҫ�Ƚ� ����Ϊ����v��1
        root[i]=insert(u[i],1,n,root[i-1]);
    }
    for(int i=1;i<=k;i++){
        int x,l,r;
        x=read(),l=read(),r=read();
        x^=(res*op),l^=(res*op),r^=(res*op);
        ans=(query(x,1,n,root[r])>=l)?1:0;
        cout<<ans<<endl;
        res+=ans;
    }
    return 0;
}
