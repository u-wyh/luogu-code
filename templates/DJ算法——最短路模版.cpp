// Dijkstra�㷨ģ�棨��ȣ�
// ��̬�ռ�ʵ�� : ��ʽǰ���� + ����������
// �������� : https://www.luogu.com.cn/problem/P4779
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ�������д��룬���������ĳ�Main������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 5005;

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
int n,m,s;

int main()
{
    cin>>n>>m>>s;
    graph.resize(n+1);
    for(int i=1;i<=m;i++){
        cin>>edge[i][0]>>edge[i][1]>>edge[i][2];
        graph[edge[i][0]].push_back({edge[i][1],edge[i][2]});
    }
    //��ʼ����ͼ

    for(int i=1;i<=n;i++){
        Distance[i]=1e9;
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

    int ans=0;
    for(int i=1;i<=n;i++){
        if(Distance[i]==1e9){
            //��ʾ�޷�����
            cout<<-1;
            return 0;
        }
        ans=max(ans,Distance[i]);
        //ȡ���ֵ  ��ʾ��Զ����ĵ����
    }
    cout<<ans;
    return 0;
}

