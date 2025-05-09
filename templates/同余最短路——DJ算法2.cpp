// ţ��Χ��
// ����һ������Ϊn������arr, arr[i]�����i��ľ���ĳ��ȣ�ÿ��ľ����������
// ����һ������m����ʾ����԰��κ�һ��ľ����ȥ���m�ĳ��ȣ�ͬһ��ľ��������ȥ��ͬ�ĳ���
// ���������ƴ��ľ���γ�һ�����ȣ����ز���ƴ�����ĳ����У����ֵ�Ƕ���
// ��������ƴ�����еĳ��ȣ�����-1
// �������ƴ�����ĳ���������࣬����-1
// 1 <= n <= 100
// 1 <= arr[i] <= 3000
// 1 <= m <= 3000
// �������� : https://www.luogu.com.cn/problem/P2662
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 101;
const int MAXV = 3001;
const int MAXM = 30001;

int head[MAXV];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;

int n,m,x;
int arr[MAXN];
bool Set[MAXV];

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // ע�������Ǵ��ڣ���Ϊ������ҪС����
};
priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
//��ʼ������С����
bool vis[MAXV];
int dis[MAXV];//��¼���������������Ե���ĵ�λ��

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

int compute() {
    int ans = 0;
    if (x == 1) {
        ans = -1;
    } else {
        for (int i = 1; i <= n; i++) {
            for (int j = max(1, arr[i] - m); j <= arr[i]; j++) {
                //ö��ÿ��ľ�����Եĳ���  ������������ǰ���ù� �Ǿ�û�б�Ҫ�ٴ�������
                if (!Set[j]) {
                    Set[j] = true;
                    for (int k = 0; k < x; k++) {
                        addEdge(k, (k + j) % x, j);
                    }
                }
            }
        }
        //���б����ú� ��һ��dj�㷨����
        dijkstra();
        for (int i = 1; i < x; i++) {
            if (dis[i] == INT_MAX) {
                ans = -1;
                break;
            }
            ans = max(ans, dis[i] - x);
        }
    }
    return ans;
}

int main()
{
    cin>>n>>m;
    x = INT_MAX;
    for (int i = 1; i <= n; i++) {
        cin>>arr[i];
        x = min(x, max(1, arr[i] - m));
        //����С��������Ϊ���ǵĻ�׼��
    }
    for(int i=0;i<=x;i++){
        dis[i]=INT_MAX;
    }
    cout<<compute();
    return 0;
}
