#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#define ll long long
using namespace std;
ll a[200001],f[200001][21],t,D;
int n,m;
bool flag;
void change(int u){  //��change�����������޸�
    f[u][0]=a[u];
    for(int i=1;u-(1<<i)>=0;i++)
        f[u][i]=max(f[u][i-1],f[u-(1<<(i-1))][i-1]);
}
ll find(int x,int y){
    double t=log(y-x+1)/log(2);
    int K=t;
    return max(f[y][K],f[x+(1<<K)-1][K]);
}
int main(){
    memset(f,0,sizeof(f));
    scanf("%d%lld",&m,&D);
    for (int i=1;i<=m;i++){
        char c;
        cin>>c;
        ll x;
        if (c=='A'){  //��������Ĳ�����ע��ϸ�ڡ�
            scanf("%lld",&x);
            a[++n]=(x+t)%D;
            change(n);
        }else{
            int L; scanf("%d",&L);
            ll ans;
            if (L==1){
                printf("%lld\n",a[n]);
                t=a[n]; continue;
            }
            ans=find(n-L+1,n);
            printf("%lld\n",ans); t=ans;
        }
    }
    return 0;
}
