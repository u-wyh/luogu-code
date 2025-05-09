// ���пγ� III
// ����һ������ n ����ʾ�� n �ڿΣ��γ̱�Ŵ� 1 �� n
// ͬʱ����һ����ά�������� relations ��
// ���� relations[j] = [prevCoursej, nextCoursej]
// ��ʾ�γ� prevCoursej �����ڿγ� nextCoursej ֮ǰ ��ɣ����޿εĹ�ϵ��
// ͬʱ����һ���±�� 0 ��ʼ���������� time
// ���� time[i] ��ʾ��ɵ� (i+1) �ſγ���Ҫ���ѵ� �·� ����
// ����������¹������������пγ�����Ҫ�� ���� �·�����
// ���һ�ſε��������޿ζ��Ѿ���ɣ�������� ���� ʱ�俪ʼ���ſγ̡�
// ����� ͬʱ �� �����ſγ� �����㷵��������пγ�����Ҫ�� ���� �·�����
// ע�⣺�������ݱ�֤һ������������пγ̣�Ҳ�������޿εĹ�ϵ����һ�������޻�ͼ��
// �������� : https://leetcode.cn/problems/parallel-courses-iii/
#include<bits/stdc++.h>
using namespace std;
const int MAXM = 250000;
const int MAXN = 500;

int n,m;
vector<vector<int >>graph;
//ʹ���ڽӱ�ͼ
int edge[MAXM][2];
//����ı�����
int Time[MAXN];
//����İ�����ֵ
int indegree[MAXN];
//�����ڵ�����
int ans[MAXN];
//ÿ���ڵ�Ĵ�
queue<int>q;
int maxans=0;

int main()
{
    cin>>n>>m;
    graph.resize(n+1);//��ʼ����̬�����С
    for(int i=1;i<=m;i++){
        cin>>edge[i][0]>>edge[i][1];
    }
    for(int i=1;i<=n;i++){
        cin>>Time[i];
    }
    for(int i=1;i<=m;i++){
        graph[edge[i][0]].push_back(edge[i][1]);
        //��ͼ
        indegree[edge[i][1]]++;
        //�������
    }
    for(int i=1;i<=n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int cur=q.front();
        ans[cur]+=Time[cur];
        maxans=max(maxans,ans[cur]);
        q.pop();
        for(int i=0;i<graph[cur].size();i++){
            ans[graph[cur][i]]=max(ans[graph[cur][i]],ans[cur]);
            //�����������ȥ�Ľڵ����й��ܽ���
            indegree[graph[cur][i]]--;
            if(indegree[graph[cur][i]]==0){
                q.push(graph[cur][i]);
            }
        }
    }
    cout<<maxans;
    return 0;
}

