// Prim�㷨ģ�棨��ȣ�
// ��̬�ռ�ʵ��
// �������� : https://www.luogu.com.cn/problem/P3366
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ�������д��룬���������ĳ�Main������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5001;
const int MAXM = 200005;

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // ע�������Ǵ��ڣ���Ϊ������ҪС����
};

priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
//��ʼ������С����
vector<vector<pair<int ,int >>>graph;
//�����Ȩͼ  �����õ���pair
int n,m;
bool Set[MAXN];
//��¼��ǰ�ڵ��Ƿ񱻷���

int main()
{
    cin>>n>>m;
    graph.resize(n+1);
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v>>w;
        graph[u].push_back({v,w});
        graph[v].push_back({u,w});
    }
    //��ʼ����ͼ
    for(int i=0;i<graph[1].size();i++){
        heap.push(graph[1][i]);
    }
    Set[1]=true;
    //����ѡ��һ�����  ����ѡ�����1
    int nodecnt=1;
    int ans=0;
    //nodecnt��¼�ж��ٵ㱻��¼  ans���ڼ�¼���մ�
    while(!heap.empty()){
        int Next=heap.top().first;
        int cost=heap.top().second;
        //next����һ���ڵ�  cost�������ߵ�Ȩֵ
        heap.pop();
        if (!Set[Next]) {
            //�������ڵ�û�б�����  ����
            nodecnt++;
            Set[Next] = true;
            ans += cost;
            for (int i=0;i<graph[Next].size();i++) {
                heap.push(graph[Next][i]);
            }
            //���������б߼���С����
        }
    }

    if(nodecnt==n){
        cout<<ans;
    }else{
        cout<<"orz";
    }
    return 0;
}

