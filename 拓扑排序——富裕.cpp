// ���ֺ͸���
// �� 0 �� n - 1 ��ţ�����ÿ���˶��в�ͬ��Ŀ��Ǯ���Լ���ͬ�̶ȵİ���ֵ
// ����һ������richer������richer[i] = [ai, bi] ��ʾ 
// person ai �� person bi ����Ǯ
// ����һ���������� quiet ������ quiet[i] �� person i �İ���ֵ
// richer �������������� �߼���Ǣ
// Ҳ����˵���� person x �� person y ����Ǯ��ͬʱ���������
// person y �� person x ����Ǯ�����
// ���ڣ�����һ���������� answer ��Ϊ�𰸣����� answer[x] = y ��ǰ����,
// ������ӵ�е�Ǯ�϶������� person x �����У�
// person y ��������ˣ�Ҳ���ǰ���ֵ quiet[y] ��С���ˣ���
// �������� : https://leetcode.cn/problems/loud-and-rich/
#include<bits/stdc++.h>
using namespace std;
const int MAXM = 250000;
const int MAXN = 500;

int n,m;
vector<vector<int >>graph;
//ʹ���ڽӱ�ͼ
int edge[MAXM][2];
//����ı�����
int quiet[MAXN];
//����İ�����ֵ
int indegree[MAXN];
//�����ڵ�����
int ans[MAXN];
//ÿ���ڵ�Ĵ�
queue<int>q;

int main()
{
    cin>>n>>m;
    graph.resize(n);//��ʼ����̬�����С
    for(int i=1;i<=m;i++){
        cin>>edge[i][0]>>edge[i][1];
    }
    for(int i=0;i<n;i++){
        cin>>quiet[i];
    }
    for(int i=1;i<=m;i++){
        graph[edge[i][0]].push_back(edge[i][1]);
        //��ͼ
        indegree[edge[i][1]]++;
        //�������
    }
    for(int i=0;i<n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    for(int i=0;i<n;i++){
        ans[i]=i;
        //���Ƚ�ÿ���ڵ�𰸳�ʼ��Ϊ����
    }
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        for(int i=0;i<graph[cur].size();i++){
            //�����������ȥ�Ľڵ����й��ܽ���
            if(quiet[ans[graph[cur][i]]]>quiet[ans[cur]]){
                //����ָ��Ľڵ�һ�������Լ���Ǯ �����Լ��ܷ�������Ĵ�
                ans[graph[cur][i]]=ans[cur];
            }
            indegree[graph[cur][i]]--;
            if(indegree[graph[cur][i]]==0){
                q.push(graph[cur][i]);
            }
        }
    }
    for(int i=0;i<n;i++){
        printf("%3d",ans[i]);
    }
    return 0;
}
