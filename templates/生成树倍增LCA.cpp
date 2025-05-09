//https://www.lanqiao.cn/problems/3506/learning/
//�����ʮ�ֵľ���
//�������ݷ�Χ����  �����㷨������
//��������ʹ����  ���� ��С������ lca ���鼯 �ڽӱ���㷨����
//
//����Ҫ����һ����  Ϊ�˽�������lca����
//��ô���Ǳ���Ҫ��һ����  ����С������  �����������ȷ������ʽ
//����֮�� ��Ҫע�����  ���ܵõ��Ĳ���һ����  ���ڵ�֮�䲢����һ����ͨ��
//���ǵ�fa���������������������  ����֮�� û�а���Ҳ���Ǻ��治���õ���
//��kruskal����֮�� ���ǵ���Ҳ�ͽ�������
//�ߵ���Ϣ�洢���ڽӱ���
//
//׼������st��
//st[i][j]�����洢�ڵ�i�ĵ� 2��j�η� �ĸ��׽ڵ���ʲô�ڵ�
//val[i][j]�����洢   �ڵ�i  ��  (�ڵ�i �ĵ� 2��j�η� �ĸ��׽ڵ�)֮����С��ֵ��ʲô(����������ܻ�����������ֵ  ����������� )
//
//deep�����������������ڵ����� ������lca
//vis���������ڽ�����ܻ��ж����  �����ж�һ������ڵ���û�б��������� û�еĻ���Ҫ�½�һ����
//ʣ�µ�Сϸ��ȫ�ڴ�������
//
//ΪʲôҪ��ô��
//��Ϊ����̫�� ������Ҫʹ�ñ���
//��������Ҫ�õ����Ǹ��׽ڵ����Ϣ  ����������ǵõ����׽ڵ�ı��  ���ǲ�����
//�������ǻ�Ҫ�õ�val����
//��ô��ʹ���  ���ǻ���Ҫ����һ����a��b��·��  ����·��������^  ������״��  ���Ϻ����͵�  ��ת��
//����ֻ�����ϵĸ�����Ϣ  û�����µ�  ���ǲ������  ����lcaҲ�ͺ�֮������

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 3e5+5;
const int LIMIT = 17;

int n,m,q;
struct node{
    int u,v,w;
}edge[MAXM];//һ��ʼ���бߵ���Ϣ
int fa[MAXN];//���ڽ�����
bool vis[MAXN];
int st[MAXN][LIMIT+1];
int val[MAXN][LIMIT+1];//����Ҫע�������limit  ��ô��������оͲ��ܷ���val[i][limit] Խ����
int deep[MAXN];
vector<pair<int,int>>path[MAXN];

bool cmp(node a,node b){
    return a.w>b.w;
}
//��������

int find(int i){
    if (i != fa[i]){
        fa[i] = find(fa[i]);
    }
    return fa[i];
}

bool issame(int x,int y){
    return find(x)==find(y);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
    }
}
//��������������Ϊ���������Ĳ��鼯����

void kruskal(){
    for(int i=1;i<=m;i++){
        int u=edge[i].u;
        int v=edge[i].v;
        int w=edge[i].w;
        if(!issame(u,v)){
            un(u,v);
            path[u].push_back({v,w});
            path[v].push_back({u,w});
        }
    }
}
//������

void dfs(int u,int f){
    vis[u]=true;
    st[u][0]=f;
    deep[u]=deep[f]+1;
    for(int i=1;i<=LIMIT;i++){
        //���ѭ�����Է��������ӽڵ�dfs֮��  ������Ҫ�ı�һ�����
        if(st[u][i-1]>0){
            st[u][i]=st[st[u][i-1]][i-1];
            val[u][i]=min(val[st[u][i-1]][i-1],val[u][i-1]);
        }
    }
    for(int i=0;i<path[u].size();i++){
        int v=path[u][i].first;
        int w=path[u][i].second;
        if(v!=f){
            val[v][0]=w;
            dfs(v,u);
        }
    }
}
//��ɱ��������Ϣ��д

int lca(int a, int b) {
    int ans=INT_MAX;
    if (deep[a] < deep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    //ȷ����С��ϵ  ��a��Զ��Ϊ��ȸ���ĵ�(��b���)  ����������Ϊ�˷������
    for (int p = LIMIT ;p >= 0; p--) {
        if (deep[st[a][p]] >= deep[b]) {
            ans=min(ans,val[a][p]);
            a = st[a][p];
            //ע�������д���  ��Ҫ��λ�� ��Ȼa�����ı�  �õ���ans����������Ҫ��
        }
    }
    //���Ƚ����߱�Ϊͬһ�߶�
    if (a == b) {
        return ans;
    }
    //�����ͬ˵���������ȹ�ϵ  �����ȹ�ϵֱ�ӷ���ans�Ϳ�����
    //��������Ļ�  ��ϸ����val���������ĺ���
    for (int p = LIMIT; p >= 0; p--) {
        if (st[a][p] != st[b][p]) {
            ans=min(ans,min(val[a][p],val[b][p]));
            a = st[a][p];
            b = st[b][p];
        }
        //�ж�������Ƿ���Ϲ���
    }
    //�ܵ�������  ��ôfa[a][0]��fa[b][0]��һ����  �������ǵ�����
    //����Ļ�����ѧһ��lca
    ans = min(ans,min(val[a][0],val[b][0]));
    return ans;
}

int main()
{
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        cin>>edge[i].u>>edge[i].v>>edge[i].w;
    }
    sort(edge+1,edge+m+1,cmp);
    kruskal();
    //����
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            dfs(i,0);
        }
    }
    for(int i=1;i<=q;i++){
        int u,v;
        cin>>u>>v;
        if(find(u)!=find(v)){
            //�������ͨ�Ļ� ֱ�ӷ���-1
            cout<<-1<<endl;
        }
        else{
            cout<<lca(u,v)<<endl;
        }
    }
    return 0;
}
/*
5 4 3
1 2 5
2 3 6
3 4 1
4 5 10
1 4
3 4
1 3
*/
