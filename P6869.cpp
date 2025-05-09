#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int LIMIT = 18;
#define int long long

struct node{
    int u,v;
}edge[MAXN];

struct ro{
    int w,w1,w2;
}nums[MAXN];

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int road[MAXN<<1];
int cnt=1;
//��ʽǰ���ǽ�ͼ
int deep[MAXN],stjump[MAXN][LIMIT];
//�����㷨
int power;
int n;
int num[MAXN];

void dfs1(int u, int f) {
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;
    for (int p = 1; p <= power; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    //���u��deep  stjump
    for (int e = head[u]; e != 0; e = Next[e]) {
        if (to[e] != f) {
            dfs1(to[e], u);
        }
        //���µݹ�
    }
}
//��������������ǽ���deep  st����Ϣ
//Ϊ�˷��������ѯlca

int lca(int a, int b) {
    if (deep[a] < deep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    //ȷ����С��ϵ
    for (int p = power; p >= 0; p--) {
        if (deep[stjump[a][p]] >= deep[b]) {
            a = stjump[a][p];
        }
    }
    //���Ƚ����߱�Ϊͬһ�߶�
    if (a == b) {
        return a;
    }
    //�����ͬ˵���������ȹ�ϵ
    for (int p = power; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            a = stjump[a][p];
            b = stjump[b][p];
        }
        //�ж�������Ƿ���Ϲ���
    }
    return stjump[a][0];
    //���ǽ�ͷ������������Ϊ0  ʵ����û��0
}

void dfs(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs(v,u);
        }
    }
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        int id=road[i];
        if(v!=f){
            nums[id].w+=num[v];
            num[u]+=num[v];
        }
    }
}

signed main()
{
    cin>>n;
    power=log2(n);
    for(int i=1;i<n;i++){
        cin>>edge[i].u>>edge[i].v>>nums[i].w1>>nums[i].w2;
        nums[i].w=0;

        Next[cnt]=head[edge[i].u];
        to[cnt]=edge[i].v;
        road[cnt]=i;
        head[edge[i].u]=cnt++;

        Next[cnt]=head[edge[i].v];
        to[cnt]=edge[i].u;
        road[cnt]=i;
        head[edge[i].v]=cnt++;
    }
    dfs1(1,0);
    for(int i=1;i<n;i++){
        int Lca;
        Lca=lca(i,i+1);
        num[i]++;
        num[i+1]++;
        num[Lca]-=2;
    }
    dfs(1,0);
    long long ans=0;
    for(int i=1;i<n;i++){
        long long temp1=nums[i].w*nums[i].w1;
        long long temp2=nums[i].w2;
        ans+=min(temp1,temp2);
    }
    cout<<ans<<endl;
    return 0;
}
