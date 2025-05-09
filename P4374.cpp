#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int LIMIT = 16;

int n,m,power;

int ans[MAXN];//��¼��
vector<pair<int,int>>vec[MAXN];//��ʼʱ�ı�  ��  �ߵı��

struct node{
    int u,v,w;
}nums[MAXN];//�½��ı�

int to[MAXN];//��������ڼ�¼������ﵱǰ�ڵ�  ʵ��������ת���Ǹ��ڵ�
int son[MAXN];//������ڼ�¼ÿ��ԭʼ�ı��нϵ͵Ľڵ�  ����ͳ�ƴ�

int deep[MAXN];
int st[MAXN][LIMIT];

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

bool cmp(node a,node b){
    return a.w<b.w;
}

void dfs(int u, int f) {
    deep[u] = deep[f] + 1;
    st[u][0] = f;
    for (int p = 1; p <= power; p++) {
        st[u][p] = st[st[u][p - 1]][p - 1];
    }
    //���u��deep  stjump
    for(int i=0;i<vec[u].size();i++){
        int v=vec[u][i].first;
        int id=vec[u][i].second;
        if(v==f){
            continue;
        }
        son[id]=v;//��ʾ������Ҫ�Ƕ���  ��ôҪ��¼����v����ڵ�Ĵ�
        dfs(v,u);
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

//�����ڲ��鼯�Ĺ���
int find(int x){
    return x==to[x]?x:to[x]=find(to[x]);
}

int main()
{
    n=read(),m=read();
    power=(int)log2(n);
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        vec[u].push_back({v,i});
        vec[v].push_back({u,i});
    }
    dfs(1,0);
    for(int i=1;i<=m;i++){
        nums[i].u=read();
        nums[i].v=read();
        nums[i].w=read();
    }
    sort(nums+1,nums+m+1,cmp);
    for(int i=1;i<=n;i++){
        to[i]=i;//��ʼʱ ÿ���ڵ�������Ķ����Լ�
        ans[i]=-1;
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=power;j++){
            cout<<st[i][j]<<' ';
        }
        cout<<endl;
    }
    for(int i=0;i<=n;i++){
        cout<<deep[i]<<' ';
    }
    cout<<endl;
    for(int i=1;i<=m;i++){
        int u=nums[i].u;
        int v=nums[i].v;
        int w=nums[i].w;
        int fa=lca(u,v);
        //cout<<u<<' '<<v<<' '<<w<<' '<<fa<<' '<<st[u][0]<<' '<<st[v][0]<<endl;
        //ʵ�������Ŀǰ��ֵӰ�쵽����  ��u��lca  ��  ��v��lca  ������lca
        for(int u=find(u);deep[u]>deep[fa];u=find(st[u][0])){
            //��ʾ���� ������u�ڵ� ʵ������ת��������
            //���θ���Ҫ������ڵ�Ĵ𰸸���  ԭ��һ����û�д𰸵�  ����д� һ�����ᵽ������ڵ�
            //����ڵ���� ��ô�Ժ󵽴�����ڵ�  һ����ֱ��ȥ����
            ans[u]=w;
            to[u]=st[u][0];
            cout<<' '<<u<<endl;
        }
        for(int v=find(v);deep[v]>deep[fa];v=find(st[v][0])){
            ans[v]=w;
            to[v]=st[v][0];
            cout<<' '<<v<<endl;
        }
    }
    for(int i=1;i<n;i++){
        cout<<ans[son[i]]<<endl;
    }
    return 0;
}
