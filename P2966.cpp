//P2966
//Floyd��G[i][j]ʵ������һ���������飬������DP������G[k][i][j]��
//����k�ǽ׶�.G[k][i][j]��ʾֻ����1~k��Щ�ڵ㣬i��j����̾���
//����⿼��ľ��������������
//���ǽ���Ȩ����Ȩֵ��С����  ��ô�����Ȩ����Ϳ�����i j k��Ȩֵ��С��������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 255;
const int MAXM = 1e4+5;
const int INF = 1e9;

int n,m,k;
struct node{
    int val,sub;
}nums[MAXN];
int dis[MAXN][MAXN];
int ans[MAXN][MAXN];

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

bool cmp(node a,node b){
    return a.val<b.val;
}

void floyd(){
    for(int k=1;k<=n;k++){
        //��ʾֻ����1��k��Щ�ڵ���Ϊ�м�ڵ�����
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                int u=nums[i].sub,v=nums[j].sub,w=nums[k].sub;
                dis[u][v]=min(dis[u][v],dis[u][w]+dis[w][v]);
                ans[u][v]=min(ans[u][v],dis[u][v]+max(nums[i].val,max(nums[j].val,nums[k].val)));
            }
        }
    }
}

int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=n;i++){
        nums[i].sub=i;
        cin>>nums[i].val;
    }
    sort(nums+1,nums+n+1,cmp);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j)
                dis[i][j]=0;
            else
                dis[i][j]=INF;
            ans[i][j]=INF;
        }
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        dis[u][v]=dis[v][u]=min(dis[u][v],w);
    }
    floyd();
    for(int i=1;i<=k;i++){
        int u,v;
        cin>>u>>v;
        cout<<ans[u][v]<<endl;
    }
    return 0;
}