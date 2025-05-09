// Y�Ļ�ľ���ɳ־û���ƫ��ʵ�����Ž⣬C++��
// һ����n���������飬����ÿ������Ĵ�Сmi���Լ�ÿ�����������
// ÿ���������ѡ��ֻ��ѡһ�����֣��Ϳ����γ�n�����ֵ���ѡ����
// ������Щ�����У��������ۼӺ͵�1С�ķ�������2С�ķ�������3С�ķ���...
// ��ӡ���ۼӺ�ǰkС�ķ��������Ե��ۼӺͣ�Ҫ��ʵ��O(k * log k)�Ľ�
// 1 <= n��mi <= 100
// 1 <= k <= 10^4
// 1 <= ���� <= 100
// �������� : https://www.luogu.com.cn/problem/P2409
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������

#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 101;
const int MAXM = 10001;
const int MAXK = 10001;
const int MAXT = 1000001;
const int INF = 10000001;

int n, k;

int arr[MAXM];
int start[MAXN];
int boundary[MAXN];
// ��ƫ���������֮ǰ��ĳ�������������ж��Ŀ�����
// ��ƫ����ͷ�ʹ�����������ж���������Ϊh�Ľڵ���ͷ
// idx[h] : �����ж������ĸ�����
int idx[MAXT];
// jdx[h] : �����ж�Ҫ�滻��idx[h]������ʲôλ�õ���
int jdx[MAXT];
// cost[h] : ����֮ǰ��ĳ�������������ж������ۼӺ����Ӷ���
int cost[MAXT];
int ls[MAXT];
int rs[MAXT];
int dist[MAXT];
int pre[MAXT];
int cnt = 0;

int heap[MAXK];
int heapSize = 0;

int ans[MAXK];

int init(int i, int j) {
    idx[++cnt] = i;
    jdx[cnt] = j;
    cost[cnt] = (j + 1 < boundary[i]) ? (arr[j + 1] - arr[j]) : INF;
    ls[cnt] = rs[cnt] = dist[cnt] = 0;
    return cnt;
}

int clone(int i) {
    idx[++cnt] = idx[i];
    jdx[cnt] = jdx[i];
    cost[cnt] = cost[i];
    ls[cnt] = ls[i];
    rs[cnt] = rs[i];
    dist[cnt] = dist[i];
    return cnt;
}

int merge(int i, int j) {
    if (i == 0 || j == 0) return i + j;
    if (cost[i] > cost[j]) {
        swap(i, j);
    }
    int h = clone(i);
    rs[h] = merge(rs[h], j);
    if (dist[ls[h]] < dist[rs[h]]) {
        swap(ls[h], rs[h]);
    }
    dist[h] = dist[rs[h]] + 1;
    return h;
}

int pop(int i) {
    if (ls[i] == 0 && rs[i] == 0) return 0;
    if (ls[i] == 0 || rs[i] == 0) return clone(ls[i] + rs[i]);
    return merge(ls[i], rs[i]);
}

bool compare(int i, int j) {
    return pre[i] + cost[i] < pre[j] + cost[j];
}

void heapAdd(int i) {
    heap[++heapSize] = i;
    int cur = heapSize, up = cur / 2;
    while (cur > 1 && compare(heap[cur], heap[up])) {
        swap(heap[cur], heap[up]);
        cur = up;
        up = cur / 2;
    }
}

int heapPop() {
    int top = heap[1];
    heap[1] = heap[heapSize--];
    int cur = 1, l = 2, r = 3, best;
    while (l <= heapSize) {
        best = (r <= heapSize && compare(heap[r], heap[l])) ? r : l;
        best = compare(heap[best], heap[cur]) ? best : cur;
        if (best == cur) break;
        swap(heap[cur], heap[best]);
        cur = best;
        l = cur * 2;
        r = l + 1;
    }
    return top;
}

void compute() {
    int first = 0;
    for (int i = 1; i <= n; ++i) {
        sort(arr + start[i], arr + boundary[i]);
        first += arr[start[i]];
    }
    dist[0] = -1;
    int head = 0;
    for (int i = 1; i <= n; ++i) {
        head = merge(head, init(i, start[i]));
    }
    pre[head] = first;
    ans[1] = first;
    heapAdd(head);
    for (int ansi = 2, h1, h2; ansi <= k; ++ansi) {
        head = heapPop();
        ans[ansi] = pre[head] + cost[head];
        h1 = pop(head);
        if (h1 != 0) {
            pre[h1] = pre[head];
            heapAdd(h1);
        }
        if (jdx[head] + 1 < boundary[idx[head]]) {
            h2 = merge(h1, init(idx[head], jdx[head] + 1));
            pre[h2] = ans[ansi];
            heapAdd(h2);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    int ai = 0;
    for (int i = 1; i <= n; ++i) {
        int m;
        cin >> m;
        start[i] = ai + 1;
        for (int j = 1; j <= m; ++j) {
            cin >> arr[++ai];
        }
        boundary[i] = start[i] + m;
    }
    compute();
    for (int i = 1; i <= k; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
