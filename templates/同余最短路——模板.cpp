// ��¥��
// һ����¥һ����h�㣬¥����1~h�������������ƶ���ʽ
// 1, �����ƶ�x��
// 2, �����ƶ�y��
// 3, �����ƶ�z��
// 4, �ص�1��
// ���������ڵ�1�㣬���ʴ�¥���ж���¥������Ե���
// 1 <= h <= 2^63 - 1
// 1 <= x��y��z <= 10^5
// �������� : https://www.luogu.com.cn/problem/P3403
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXM = 200001;
#define int long long

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;

int x,y,z;
int h;

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // ע�������Ǵ��ڣ���Ϊ������ҪС����
};
priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
//��ʼ������С����
bool vis[MAXN];
int dis[MAXN];//��¼���������������Ե���ĵ�λ��

void addEdge(int u, int v, int w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

//��֮ǰ�����Ѿ������еı߽����� ��ô����ֻ��Ҫ��һ�����·�㷨  ����dj
//Ȼ������ռ���������Ҫ�Ĵ�
void dijkstra() {
    heap.push({ 0, 0 });
    dis[0] = 0;
    int u;
    int w;
    while (!heap.empty()) {
        u=heap.top().first;
        w=heap.top().second;
        heap.pop();
        if (vis[u]) {
            continue;
        }
        vis[u] = true;
        for (int ei = head[u], v; ei > 0; ei = Next[ei]) {
            v = to[ei];
            if (!vis[v] && dis[v] > w + weight[ei]) {
                dis[v] = w + weight[ei];
                heap.push({ v, dis[v] });
            }
        }
    }
}

int compute(){
    dijkstra();
    int ans = 0;
    for (int i = 0; i < x; i++) {
        if (dis[i] <= h) {
            ans += (h - dis[i]) / x + 1;
        }
    }
    return ans;
}

signed main()
{
    cin>>h>>x>>y>>z;
    h-=1;
    for(int i=0;i<x;i++){
        dis[i]=LONG_MAX;
    }
    //��ʵͬ�����·�Ĺؼ������������
    for (int i = 0; i < x; i++) {
        addEdge(i, (i + y) % x, y);
        addEdge(i, (i + z) % x, z);
        //����ͼ
    }
    //��ʽǰ���ǽ�ͼ
    cout<<compute();
    return 0;
}
