//P4644
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 90000;
const int MAXM = 10005;

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
int n,st,en;

signed main()
{
    cin>>n>>st>>en;
    en++;
    int over=en;
    graph.resize(90005);
    for(int i=st;i<=en;i++){
        graph[i+1].push_back({i,0});
        //����ǳ���  �������еĵ�����  Ҳ����Ӱ��Ȩֵ
    }
    for(int i=1;i<=n;i++){
        cin>>edge[i][0]>>edge[i][1]>>edge[i][2];
        edge[i][1]++;
        over=max(over,edge[i][1]);
        graph[edge[i][0]].push_back({edge[i][1],edge[i][2]});

        if(edge[i][0]<st&&edge[i][1]>=st){
            graph[st].push_back({edge[i][0],0});
        }
        if(edge[i][1]>en&&edge[i][0]<en){
            graph[edge[i][1]].push_back({en,0});
        }
    }

    for(int i=0;i<=over;i++){
        Distance[i]=LLONG_MAX;
    }
    //�������ʼ��

    Distance[st]=0;
    //��s����ΪԴ�㴫���ź�
    heap.push({st,0});
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

    if(Distance[en]==LLONG_MAX){
        cout<<-1<<endl;
        return 0;
    }
    cout<<Distance[en];
    return 0;
}

