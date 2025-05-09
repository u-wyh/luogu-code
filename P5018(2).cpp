#include<cstdio>
#include<iostream>
#define N 1000005
using namespace std;
struct node{
    int s[N];
}a,siz,l1,l2;
int n;
int l[N],r[N];
int date[N];
void manacher(node &x,node &len){
    int mx=0,po=0;
    for(int i=1;i<=n;i++){
        if(mx>i)
        len.s[i]=min(mx-i,len.s[2*po-i]);
        else len.s[i]=1;
        while(x.s[i-len.s[i]]==x.s[i+len.s[i]])
        len.s[i]++;
        if(i+len.s[i]>mx)
        mx=i+len.s[i],po=i;
    }
}
int cnt=0;
int rak[N];
void dfs(int u){
    if(u==-1)return;
    dfs(l[u]);
    a.s[++cnt]=date[u];
    rak[u]=cnt;
    int ct=cnt;
    dfs(r[u]);
    siz.s[ct]=siz.s[rak[max(0,l[u])]]+siz.s[rak[max(0,r[u])]]+1;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    scanf("%d",&date[i]);
    fill(a.s,a.s+N,1e9);
    fill(siz.s+1,siz.s+N,-1);
    for(int i=1;i<=n;i++)
    scanf("%d%d",&l[i],&r[i]);
    dfs(1);
    manacher(a,l1);
    manacher(siz,l2);
    int ans=0;
    for(int i=1;i<=n;i++)
    if(l1.s[i]*2-1>=siz.s[i]&&l2.s[i]*2-1==siz.s[i])
    ans=max(ans,siz.s[i]);
    printf("%d",ans);
    return 0;
}
