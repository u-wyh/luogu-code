#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2505;
const int MAXM = 15005;

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // ע�������Ǵ��ڣ���Ϊ������ҪС����
};

priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
//��ʼ������С����
vector<vector<pair<int ,int >>>graph;
//�ڽӱ�ͼ
int edge[MAXM][3];
int Distance[MAXN];
//��¼��Դ�����С����
bool visit[MAXN];
//��¼������Ƿ񱻷��ʹ�
int n,m,s,en;

int main()
{
    cin>>n>>m>>s>>en;
    graph.resize(n+1);
    for(int i=1;i<=m;i++){
        cin>>edge[i][0]>>edge[i][1]>>edge[i][2];
        graph[edge[i][0]].push_back({edge[i][1],edge[i][2]});
        graph[edge[i][1]].push_back({edge[i][0],edge[i][2]});
    }
    //��ʼ����ͼ

    for(int i=1;i<=n;i++){
        Distance[i]=INT_MAX;
    }
    //�������ʼ��

    Distance[s]=0;
    //��s����ΪԴ�㴫���ź�
    heap.push({s,0});
    //С���Ѵ������ʽ��  �ڵ㡪��Ȩֵ  ��Ȩֵ����
    while(!heap.empty()){
        int u=heap.top().first;
        heap.pop();
        if(visit[u]){
            continue;
        }
        visit[u]=true;
        for(int i=0;i<graph[u].size();i++){
            int v=graph[u][i].first;
            int w=graph[u][i].second;
            if(!visit[v]&&(w+Distance[u])<Distance[v]){
                Distance[v]=w+Distance[u];
                heap.push({v,Distance[u]+w});
            }
        }
    }
    cout<<Distance[en];
    return 0;
}

