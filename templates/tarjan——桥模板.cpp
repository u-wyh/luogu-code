//P1656
// ����ʵ��tarjanû��ʲô�����ϵ�����  ����һ����
// �ŵ��жϷ����Ƕ���һ����  �������ĵ��low����������dfn  ˵������
// ����������ǻ��ݵ�  �ǲ���
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 155;
const int MAXM = 5005;

int n,m;
vector<pair<int,int>>bridges;

int dfn[MAXN];
int low[MAXN];
int dfncnt;

int cnt=1;
int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int weight[MAXM<<1];//��¼�����ߵı��

void addedge(int u,int v,int i){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=i;
    head[u]=cnt++;
}

void tarjan(int u,int id){
    //��ʾ��ǰ�����˵�u  ��ͨ����ʵ���id����������
    dfn[u]=low[u]=++dfncnt;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(!dfn[v]){
            tarjan(v,w);
            low[u]=min(low[u],low[v]);
            if(low[v]>dfn[u]){
                bridges.push_back({u,v});
            }
        }
        else if(w!=id){
            //�����߻�ͷ·
            low[u]=min(low[u],dfn[v]);
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v,i);
        addedge(v,u,i);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i,0);
        }
    }
    sort(bridges.begin(), bridges.end());
    for (auto &p : bridges) {
        cout << p.first << " " << p.second << endl;
    }
    return 0;
}