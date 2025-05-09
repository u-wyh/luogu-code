#include<bits/stdc++.h>
using namespace std;
#define MAXN 100005
int n,m,q;
int dx[MAXN],dy[MAXN];//������״����
int ax[MAXN],ay[MAXN];//����Ĵ�ţ������޸ģ�
int lowbit(int x)
{
    return x&(x^(x-1));
}
void gai(int *c,int x,int y)//�����޸�
{
    while(x <= *c)
    {
        *(c+x) += y;
        x += lowbit(x);
    }
}
int qiu(int *c,int x)//������ֵ
{
    int ans = 0;
    while(x >= 1)
    {
        ans += *(c+x);
        x -= lowbit(x);
    }
    return ans;
}
void huan(int x,int y)
{
    if(ax[x] == 1)
    {
        ax[x] = 0;
        gai(dx,x,-1);
    }
    else
    {
        ax[x] = 1;
        gai(dx,x,1);
    }
    if(ay[y] == 1)
    {
        ay[y] = 0;
        gai(dy,y,-1);
    }
    else
    {
        ay[y] = 1;
        gai(dy,y,1);
    }
}
long long suan(int x1,int y1,int x2,int y2)//�����к���ĵط�
{
    int s1 = qiu(dx,x2) - qiu(dx,x1 - 1);
    int s2 = qiu(dy,y2) - qiu(dy,y1 - 1);
    long long ans = (long long)s1*(y2-y1+1) + (long long)s2*(x2-x1+1) - s1*s2*2;
    return ans;
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    int cmd,x,y,x2,y2;
    dx[0] = n;
    dy[0] = m;
    for(int i = 1; i <= q; i ++)
    {
        scanf("%d",&cmd);
        if(cmd == 1)
        {
            scanf("%d%d",&x,&y);
            huan(x,y);
        }
        else
        {
            scanf("%d%d%d%d",&x,&y,&x2,&y2);
            cout<<suan(x,y,x2,y2)<<endl;
        }
    }
    return 0;
 }
