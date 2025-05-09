#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define N 100010
int n,num,c[N],vis[N];
long long ans,d;
const double eps=1e-9;
struct node{
    double ct;
    int id;
}p[N];
bool cmp(node x,node y){
    return x.ct-y.ct>eps;
}
int lowbit(int x){return x&(-x);}
void update(int p,int x){
    while(p<=2*n){
        c[p]+=x;
        p+=lowbit(p);
    }
}
long long query(int p){
    long long sum=0;
    while(p){
        sum+=c[p];
        p-=lowbit(p);
    }
    return sum;
}
int main(){
    //freopen("Cola.txt","r",stdin);
    scanf("%d%lld",&n,&d);
    long long a,b,c;
    for(int i=1;i<=n;i++){
        scanf("%lld%lld%lld",&a,&b,&c);
        //cin>>a>>b>>c;
        if(c*c<d*d*(a*a+b*b)){
            double tmp=a*a+b*b,tmp2=sqrt(d*d*tmp-c*c);
            double x1=(a*c+b*tmp2)/tmp;
            double x2=(a*c-b*tmp2)/tmp;
            double y1=(b*c-a*tmp2)/tmp;
            double y2=(b*c+a*tmp2)/tmp;
            p[++num].ct=atan2(y1,x1);p[num].id=i;
            p[++num].ct=atan2(y2,x2);p[num].id=i;
        }
    }
    sort(p+1,p+1+num,cmp);
    for(int i=1;i<=num;i++){
        if(vis[p[i].id]){
            ans+=query(i)-query(vis[p[i].id]);
            update(vis[p[i].id],-1);
        }
        else {
            vis[p[i].id]=i;
            update(i,1);
        }
    }
    printf("%lld",ans);
    return 0;
}