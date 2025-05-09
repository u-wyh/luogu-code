//P1491
//�����ĿҪ����Ǵζ�··���ĳ��� ���Ҳ���������ͬ�ı�  ��ʹ�������ܻ����
//����ж������· ��ôֱ��������·����
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;
const int MAXM = 20005;

int n,m;
struct node{
    int x,y;
}nums[MAXN];
double dis[MAXN];
bool vis[MAXN];
//pre[i]��¼����ڵ�ǰ��Ľڵ����ĸ�  �������Ǹ��ڵ�ת�Ƶ�
int pre[MAXN];

int cnt=1;
int head[MAXN];
int Next[MAXM];
int to[MAXM];
double weight[MAXM];

struct Compare {
    bool operator()(const std::pair<double, int>& a, const std::pair<double, int>& b) {
        return a.first > b.first; // С���ѣ��� double ֵ��������
    }
};
priority_queue<std::pair<double, int>, vector<std::pair<double, int>>, Compare> heap;

void addedge(int u,int v,double w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dijkstra(int x,int y){
    //��ʾ������������ı������dj�в�����
    for(int i=1;i<=n;i++){
        dis[i]=1e9;
        vis[i]=0;
    }
    dis[1]=0;
    heap.push({0,1});
    while(!heap.empty()){
        int u=heap.top().second;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=head[u];i;i=Next[i]){
            int v=to[i];
            double w=weight[i];
            if((u==x&&y==v)||(u==y&&v==x)){
                continue;
            }
            if(!vis[v]&&w+dis[u]<dis[v]){
                dis[v]=w+dis[u];
                heap.push({dis[v],v});
                if(x==0&&y==0){
                    //ֻ���ڵ�һ�������·��ʱ�� ��¼��ǰ�ڵ�ǰ��ת�ƵĽڵ�
                    pre[v]=u;
                }
            }
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>nums[i].x>>nums[i].y;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        double w=sqrt(pow(abs(nums[u].x-nums[v].x),2)+pow(abs(nums[u].y-nums[v].y),2));
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dijkstra(0,0);//�������һ�����·���� �����pre���� 
    double ans=1e9;
    for(int i=n;i!=1;i=pre[i]){
        //ö�����·�����еı� 
        //ͬʱ����ж������· ��ô����һ���ߺ�  Ҳһ������һ��һ���Ĵ�
        dijkstra(pre[i],i);
        ans=min(ans,dis[n]);
    }
    if(ans>=1e9){
        cout<<-1<<endl;
    }
    else{
        printf("%.2lf",ans);
    }
    return 0;
}
