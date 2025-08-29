#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n;
int dfn[MAXN];
int val[MAXN];

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

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        int u=read();
        dfn[u]=i;
    }
    for(int i=1;i<=n;i++){
        int u=read();
        val[i]=dfn[u];
    }
    // for(int i=1;i<=n;i++){
    //     cout<<val[i]<<' ';
    // }
    // cout<<endl;
    double ans=2;
    for(int i=2;i<n;i++){
        if(val[i]+1==val[i+1]){
            ans+=0.5;
        }
        else if(val[i]+1>val[i+1]){
            ans+=1;
        }
    }
    printf("%.3lf",ans);
    return 0;
}