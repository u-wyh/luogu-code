// �����׶��������ͺ�
// ����һ�� n ���ڵ������һ��������ͨ���޻�ͼ��
// ÿ���ڵ��ʾһ�����У���Ŵ� 0 �� n - 1 ����ǡ���� n - 1 ��·
// 0 ���׶�������һ����ά�������� roads
// ���� roads[i] = [ai, bi] ����ʾ���� ai �� bi ֮����һ�� ˫��·
// ÿ����������һ���������Ƕ�Ҫȥ�׶��μ�һ������
// ÿ����������һ����������һ������ seats ��ʾÿ����������λ����Ŀ
// ������Ĵ������ѡ��������ڳ��еĳ������߳����������еĳ�
// ���ڳ���֮��һ�������ͺ���һ������
// ���㷵�ص����׶�������Ҫ����������
// �������� : https://leetcode.cn/problems/minimum-fuel-cost-to-report-to-the-capital/

#include<bits/stdc++.h>
using namespace std;
const int MAXN =100005;

vector<vector<int >>graph;
int sz[MAXN];
//��ʾ���ﵱǰλ��ʱһ���ж�����
int cost[MAXN];
//��ʾ���ﵱǰλ��ʱһ�����˶�����
int n,seats;
//n��ʾһ����n��·  seats��ʾ��λ��Ŀ

void f(int u, int p) {
    sz[u] = 1;
    for (int i=0;i<graph[u].size();i++) {
        int v=graph[u][i];
        if (v != p) {
            f(v,u);//���µݹ�
            sz[u] += sz[v];
            cost[u] += cost[v];
            // a/b����ȡ��������д��(a+b-1)/b
            // (size[v]+seats-1) / seats = size[v] / seats ����ȡ��
            cost[u] += (sz[v] + seats - 1) / seats;
            //����ط��ӵ����ӽڵ㵽����ط����ͺ�
        }
    }
}
//��������һ���ǵ�ǰ�ڵ�  һ�������ĸ��ڵ�

int main()
{
    cin>>n>>seats;
    graph.resize(n+1);
    for(int i=1,u,v;i<=n;i++){
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        //�����ｨ��˫��ͼ����Ϊ���ǲ�֪���ĸ������ǶԵ�
        //�����������ͨ����¼���ڵ��������ظ�
        //�����л�  �����ǶԵ�
    }
    f(0,-1);//������Ϊ0�ĸ��ڵ���-1
    cout<<cost[0];
    return 0;
}
