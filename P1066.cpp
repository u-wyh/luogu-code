#include<iostream>
#include<cstdio>
#define rint register int
#define ini inline int 
using namespace std;
int a[30001][201],c[201],ans[201],k,w;
ini jia(int *a,int *b)
{
    int lenc=0,x=0;
    while (lenc<a[0] || lenc<b[0])
    {
        a[++lenc]=a[lenc]+b[lenc]+x;
        x=a[lenc]/10;
        a[lenc]%=10;    
    }
    if (x>0) a[++lenc]=x;
    a[0]=lenc;
}
int main()
{
    scanf("%d%d",&k,&w);
    int kk=w%k;int hh=w/k;
    int y=0;
    for (rint i=1;i<=kk;i++)
        y+=1<<(i-1);     //最高位最大是几
    int minn=(1<<k)-1;//第一位最大是多少
    if (hh==1 || (hh==2 && kk==0))
    {
        if (kk==0) y=minn;int tot=0;
        for (rint i=1;i<=y;i++)
            tot+=minn-i;
        cout<<tot;
        return 0;
    }//特判两位以内的情况
    for (rint i=1;i<=minn-1;i++)
    {
        a[i][1]=i;a[i][0]=1;
        jia(ans,a[i]);
    }//第二位是minn-1到1各有多少种可能
    for (rint i=3;i<=hh;i++)
        for (rint j=1;j<=minn-i+1;j++)
        {
            jia(a[j],a[j-1]);
            jia(ans,a[j]);
        }
//以下是单独处理最高位，因为最高位有限制
    for (rint j=1;j<=minn-hh;j++)
        jia(a[j],a[j-1]);
    for (rint j=minn-hh;j>=max(minn-hh-y+1,1);j--)
        jia(ans,a[j]);
//我们的前缀和是倒着存的
    for (rint i=ans[0];i>=1;i--)
        printf("%d",ans[i]);
}