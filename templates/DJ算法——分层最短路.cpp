// �綯���γ���
// С���ĵ綯����������ʱ����ʻ����Ϊ cnt��ÿ��ʻ 1 ��λ�������� 1 ��λ�������һ��� 1 ��λʱ��
// С����ѡ��綯����Ϊ�������ߡ���ͼ�Ϲ��� N �����㣬������Ϊ 0 ~ N-1
// ������ͼ��Ϣ�� [���� A ���,���� B ���,�����м����] ��ʽ�������ڶ�ά���� paths��
// ��ʾ���� A��B �����˫��ͨ·��
// ��ʼ״̬���綯������Ϊ 0��ÿ�����ж����г��׮��
// charge[i] ��ʾ�� i ������ÿ�� 1 ��λ������Ҫ���ѵĵ�λʱ�䡣
// �뷵��С��������Ҫ���Ѷ��ٵ�λʱ��������� start �ִ��յ���� end
// �������� : https://leetcode.cn/problems/DFPeFJ/
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 205;
const int MAXCNT = 105;

struct Range {
    int cur,power,cost;
};
// �ȽϺ���������С���ѣ��� l ֵ���ʱ������ͨ����Ӷ���ıȽ��������ȶ���
bool compare(const Range& a, const Range& b) {
    return a.cost > b.cost; // ע�������Ǵ��ںţ���Ϊ����Ҫʹ�� greater<> �����С����
}
priority_queue<Range, vector<Range>, decltype(&compare)> heap(compare);
//����С����
// cur : ��ǰ��
// power : ������ǰ��ĵ���
// cost : ����ʱ��
int n,m;
int edge[MAXM][3];
vector<vector<pair<int ,int >>>graph;
//����ͼ  ����ͼ
int st,en,cnt;
int charge[MAXN];
int dis[MAXN][MAXCNT];
bool visited[MAXN][MAXCNT];
//�жϵ�ǰλ��  ��ǰ״̬�Ƿ񱻷��ʹ�

int main()
{
    cin>>n>>m>>st>>en>>cnt;
    //���������Ŀ  ��·��Ŀ  ��ʼ�Լ�����λ��  ��������ݻ�
    graph.resize(n);
    for(int i=1;i<=m;i++){
        cin>>edge[i][0]>>edge[i][1]>>edge[i][2];
        graph[edge[i][0]].push_back({edge[i][1],edge[i][2]});
        graph[edge[i][1]].push_back({edge[i][0],edge[i][2]});
    }
    //��������ͼ
    for(int i=0;i<n;i++){
        cin>>charge[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= cnt; j++) {
            dis[i][j] = INT_MAX;
        }
    }
    //��ʼ��dis����

    dis[st][0] = 0;
    heap.push({ st, 0, 0 });
    //����ʼ��ѹ�����
    while (!heap.empty()) {
        Range record = heap.top();
        heap.pop();
        int cur = record.cur;
        int power = record.power;
        int cost = record.cost;
        if (visited[cur][power]) {
            continue;
        }
        visited[cur][power] = true;
        if (cur == en) {
            // ������֦
            // �����յ�ֱ�ӷ���
            // ���õȶ�����
            cout<<cost;
            return 0;
        }
        if (power < cnt) {
            // ��һ���
            // cur, power+1
            if (!visited[cur][power + 1] && cost + charge[cur] < dis[cur][power + 1]) {
                dis[cur][power + 1] = cost + charge[cur];
                heap.push({ cur, power + 1, cost + charge[cur] });
            }
        }
        for (int i=0;i<graph[cur].size();i++) {
        // �����ȥ��ĳ���
            int nextCity = graph[cur][i].first;
            int restPower = power - graph[cur][i].second;
            int nextCost = cost + graph[cur][i].second;
            if (restPower >= 0 && !visited[nextCity][restPower] && nextCost < dis[nextCity][restPower]) {
                //�����������֧�ŵ�����һ������  ������һ�����е����״̬û�б����ʹ�   �����õ������ڵ�ǰ  �ſ���
                dis[nextCity][restPower] = nextCost;
                heap.push({ nextCity, restPower, nextCost });
            }
        }
    }
    cout<<-1;
    return 0;
}
