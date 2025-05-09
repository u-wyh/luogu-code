#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int LIMIT = 18;

int n,power;
int arr[MAXN];//��¼�߶�
long long dp[MAXN];//��ʾ���i��Ϊ���  ������Ծ  ֻ��ȥ�����Լ�С�ĵ� ��Զ����
int fa[MAXN];
//��ʾ�����ͨ���еĴ���ڵ�  Ҳ������ߵĽڵ�
//��ΪҪȥѡ������ڵ�ķ���  ���������Ҫô�� Ҫô���ߣ���ס��
//��������ڵ�Ҫô��ס  Ҫôȥ��֮���ٶ�ס  ��ô����ѡ�����
int st[MAXN][LIMIT];
int deep[MAXN];

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

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

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u, int f) {
    deep[u] = deep[f] + 1;
    st[u][0] = f;
    for (int p = 1; p <= power; p++) {
        st[u][p] = st[st[u][p - 1]][p - 1];
    }
    //���u��deep  stjump
    for (int e = head[u]; e != 0; e = Next[e]) {
        if (to[e] != f) {
            dfs(to[e], u);
        }
        //���µݹ�
    }
}


int lca(int a, int b) {
    if (deep[a] < deep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    //ȷ����С��ϵ
    for (int p = power; p >= 0; p--) {
        if (deep[st[a][p]] >= deep[b]) {
            a = st[a][p];
        }
    }
    //���Ƚ����߱�Ϊͬһ�߶�
    if (a == b) {
        return a;
    }
    //�����ͬ˵���������ȹ�ϵ
    for (int p = power; p >= 0; p--) {
        if (st[a][p] != st[b][p]) {
            a = st[a][p];
            b = st[b][p];
        }
        //�ж�������Ƿ���Ϲ���
    }
    return st[a][0];
    //���ǽ�ͷ������������Ϊ0  ʵ����û��0
}

int dis(int u,int v){
    return deep[u]+deep[v]-2*deep[lca(u,v)];
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

int main()
{
    n=read();
    power=log2(n);
    for(int i=1;i<=n;i++){
        fa[i]=i;
        arr[i]=read();
    }
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        u=arr[u],v=arr[v];//���ݸ�����ĸ߶Ƚ�ͼ
        addedge(u,v),addedge(v,u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++){
        //��ʱֻ��i�Լ�С��i�ĵ��ǿ��Ե����
        for(int j=head[i];j;j=Next[j]){
            int v=find(to[j]);
            if(v<i){
                //��ʵ����ڵ�ֻҪ������  ��һ�����Ե���
                //��ʾ����ڵ���Ե���
                fa[v]=i;
                dp[i]=max(dp[i],dp[v]+dis(i,v));
                //�����ʽ����˼��  ���Ҫȥv�������  ��ôһ����ȥ�����ͨ������ĵط�
            }
        }
    }
    cout<<dp[n]<<endl;
    return 0;
}
