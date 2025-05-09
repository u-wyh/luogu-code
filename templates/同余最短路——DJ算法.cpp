// īī�ĵ�ʽ(dijkstra�㷨)
// һ����n��������ÿ��������ѡ������������������Ǹ���
// ��ôһ����ĳЩ��ֵ��������Щ�����ۼӵõ�
// ������[l...r]��Χ�ϣ��ж��ٸ����ܱ��ۼӵõ�
// 0 <= n <= 12
// 0 <= ��ֵ��Χ <= 5 * 10^5
// 1 <= l <= r <= 10^12
// �������� : https://www.luogu.com.cn/problem/P2371
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
//dj�㷨�����ƾ��������Ƚϼ�  ��ʵ���ӶȱȲ��϶���תȦ��
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 5e6+5;

int n;
long l,r;
int x;
int head[MAXN];
int Next[MAXM];
int to[MAXM];
long weight[MAXM];
int cnt=1;
auto compare = [](const pair<int, long>& left, const pair<int, long>& right) {
    return left.second > right.second; // ע�������Ǵ��ڣ���Ϊ������ҪС����
};
priority_queue<pair<int, long>, vector<pair<int, long>>, decltype(compare)> heap(compare);
//��ʼ������С����
bool vis[MAXN];
long dis[MAXN];//��¼���������������Ե���ĵ�λ��

void addEdge(int u, int v, int w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void dijkstra() {
    heap.push({ 0, 0 });
    dis[0] = 0;
    int u;
    long w;
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

long compute(){
    dijkstra();
    long ans = 0;
    for (int i = 0; i < x; i++) {
        if (r >= dis[i]) {
            ans += (r - dis[i]) / x + 1;
        }
        if (l >= dis[i]) {
            ans -= (l - dis[i]) / x + 1;
        }
    }
    return ans;
}

int main()
{
    cin>>n>>l>>r;
    l--;
    cin>>x;
    for(int i=2,v;i<=n;i++){
        cin>>v;
        for (int j = 0; j < x; j++) {
            //ÿһ���ڵ㶼Ҫ��һ����
            addEdge(j, (j + v) % x, v);
            //����j�鵽��(j + v) % x��
        }
    }
    for(int i=0;i<x;i++){
        dis[i]=LONG_MAX;
    }
    cout<<compute();
    return 0;
}
