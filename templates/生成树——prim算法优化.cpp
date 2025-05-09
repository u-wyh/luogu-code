// Prim�㷨�Ż�����ȣ�
// ��̬�ռ�ʵ��
// ʱ�临�Ӷ�O(n + m) + O((m+n) * log n)
// �������� : https://www.luogu.com.cn/problem/P3366
// ��ͬѧ����زο����´����й������롢����Ĵ���
// ���������������Ч�ʺܸߵ�д��
// �ύ�������д��룬���������ĳ�Main������ֱ��ͨ��
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5001;
const int MAXM = 400001;

int n, m;
int u, w;

// ��ʽǰ���ǽ�ͼ
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt=1;

// ��д�Ķѽṹ
//heap[i][0]��ʾ��i��λ�õĽڵ���
//heap[i][1]��ʾ��i��λ�õĽڵ����
int heap[MAXN][2];
// where[v] = -1����ʾv����ڵ㣬����û�н������
// where[v] = -2����ʾv����ڵ㣬�Ѿ���������
// where[v] = i(>=0)����ʾv����ڵ㣬�ڶ��ϵ�iλ��
int where[MAXN];
// �ѵĴ�С
int heapSize;
// �ҵ��Ľڵ����
int nodeCnt;

void addEdge(int u, int v, int w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

bool isEmpty() {
    return heapSize == 0;
}

// ���ϣ�iλ�õ���Ϣ �� jλ�õ���Ϣ ������
void swap(int i, int j) {
    int a = heap[i][0];
    int b = heap[j][0];
    where[a] = j;
    where[b] = i;
    swap(heap[i],heap[j]);
}

//������
void heapify(int i) {
    int l = i * 2 + 1;
    while (l < heapSize) {
        int best = l + 1 < heapSize && heap[l + 1][1] < heap[l][1] ? l + 1 : l;
        best = heap[best][1] < heap[i][1] ? best : i;
        if (best == i) {
            break;
        }
        swap(best, i);
        i = best;
        l = i * 2 + 1;
    }
}

void pop() {
    u = heap[0][0];
    w = heap[0][1];
    swap(0, --heapSize);
    heapify(0);
    where[u] = -2;
    nodeCnt++;
}

void heapInsert(int i) {
    while (heap[i][1] < heap[(i - 1) / 2][1]) {
        swap(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

// ��ǰ������Ǳ��Ϊei�ıߣ�
void addOrUpdateOrIgnore(int ei) {
    int v = to[ei];
    int w = weight[ei];
    // ȥ��v�㣬Ȩ��w
    if (where[v] == -1) {
        // v����㣬����û�н�����ѣ�
        heap[heapSize][0] = v;
        heap[heapSize][1] = w;
        where[v] = heapSize++;
        heapInsert(where[v]);
    } else if (where[v] >= 0) {
        // v�����ļ�¼���ڶ��ϵ�λ����where[v]
        heap[where[v]][1] = min(heap[where[v]][1], w);
        heapInsert(where[v]);
    }
}

int prim() {
    // 1�ڵ����
    nodeCnt = 1;
    where[1] = -2;//���ڵ�1ֱ����Ϊ�Ѿ���������
    for (int ei = head[1]; ei > 0; ei = Next[ei]) {
        //���Ƚ�1�ڵ���������߼������
        addOrUpdateOrIgnore(ei);
    }
    int ans = 0;
    while (!isEmpty()) {
        pop();
        ans += w;
        for (int ei = head[u]; ei > 0; ei = Next[ei]) {
            addOrUpdateOrIgnore(ei);
        }
    }
    return ans;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        where[i]=-1;
    }
    for (int i = 0, u, v, w; i < m; i++) {
        cin>>u>>v>>w;
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    int ans = prim();
    if(nodeCnt == n)
        cout<< ans ;
    else
        cout<<"orz"<<endl;
    return 0;
}
