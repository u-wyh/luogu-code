// k��·���⣬�ɳ־û���ƫ��ʵ�����Ž⣬C++��
// ��n������1~n����m���ߣ�ÿ���߶���������Ȩ����������Ȩͼ
// ��1�ŵ��ߵ�n�ŵ㣬����Ϊ��һ������
// һ�������У��߲����ظ�ѡ��������ظ����������������n�ŵ㣬��ô��������ֹͣ
// ��1�ŵ��ߵ�n�ŵ㣬���кܶ�ͨ·������ͨ·������·��Ϊѡ��ߵı�Ȩ�ۼӺ�
// ��Ȼÿ�����ж��Ǵ�1�ŵ㵽n�ŵ㣬������ϣ��ÿ�����е�ͨ·�������ǲ�ͬ��
// �κ��������У�ֻҪѡ��ı����в�ͬ������Ϊ�ǲ�ͬ��ͨ·����
// ���Ǯ��Ϊmoney������֧��·�ѣ���ӡ��һ���ܽ��м�������
// �������� : https://www.luogu.com.cn/problem/P2483
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50001;//��ĸ���
const int MAXM = 200001;//�ߵĸ���
const int MAXT = 1000001;//�ɳ־û���ƫ���Ľڵ����
const int MAXH = 4200001;
const double INF = 1e18;

int n, m;
double money;

// ��������ͼ��һ���ǳ�ֵ��ע��ĵط�
// �����ͼ�У�a��b�ıߣ����Ϊx
// ��ô��ͼ�У�b��a�ıߣ����Ҳ��x
// ��Ϊÿһ���ߣ���ͼ������ͬʱ����ͼҲͬ������
// ��������ͼ�������߷���ı��Ҳ��һ����
// ��ͼ
int headg[MAXN];
int tog[MAXM];
int nextg[MAXM];
double weightg[MAXM];
int cntg = 0;

// ��ͼ
int headr[MAXN];
int tor[MAXM];
int nextr[MAXM];
double weightr[MAXM];
int cntr = 0;

// ��ƫ���������֮ǰ��ͨ·������ѡ������ߵĿ�����
// ��ƫ����ͷ�ʹ������ŵ�ѡ�񣬼�����Ϊh�Ľڵ���ͷ
// to[h] : ѡ�����ŷ����ߣ��������������ͼ��ָ���ĸ��ڵ�
int to[MAXT];
// cost[h] : ����֮ǰ��ͨ·����������ѡ�����·�����Ӷ���
double cost[MAXT];
int ls[MAXT];
int rs[MAXT];
int dist[MAXT];
int cntt = 0;

// rt[u] : �����·���ϣ��ڵ�u�����������Ƚڵ㣬��ӵ�е�ȫ�������ߣ���ɵ���ƫ��
int rt[MAXN];

// heap�Ǿ����С���ѣ����źܶ�(key, val)���ݣ�����val����֯С����
//key val�����ڴ洢����  heap�����Ǳ��  cntd�����ݴ�С cnth�ǶѴ�С
int key[MAXH];
double val[MAXH];
int heap[MAXH];
int cntd, cnth;

// dijkstra�㷨��Ҫ�����ݷ�ͼ��dijkstra�����ɴӽڵ�n��ʼ�����·��
// vis[u] : �ڵ�u���ڵ�n����̾��룬�Ƿ��Ѿ��������
bool vis[MAXN];
// path[u] : ���·���ϣ�����ڵ�u�����ߣ������ʲô��Ҳ������ͼ�ϣ�����Ӧ�ı�
int path[MAXN];
// dis[u] : ���·���ϣ��ڵ�n���ڵ�u����̾���
double dis[MAXN];

void addEdgeG(int u, int v, double w){
    nextg[++cntg] = headg[u];
    tog[cntg] = v;
    weightg[cntg] = w;
    headg[u] = cntg;
}

void addEdgeR(int u, int v, double w){
    nextr[++cntr] = headr[u];
    tor[cntr] = v;
    weightr[cntr] = w;
    headr[u] = cntr;
}

int init(int t, double v){
    to[++cntt] = t;
    cost[cntt] = v;
    ls[cntt] = rs[cntt] = dist[cntt] = 0;
    return cntt;
}

int clone(int i){
    to[++cntt] = to[i];
    cost[cntt] = cost[i];
    ls[cntt] = ls[i];
    rs[cntt] = rs[i];
    dist[cntt] = dist[i];
    return cntt;
}

int merge(int i, int j){
    if(i == 0 || j == 0){
        return i + j;
    }
    if(cost[i] > cost[j]){
        swap(i, j);
    }
    int h = clone(i);
    rs[h] = merge(rs[h], j);
    if(dist[ls[h]] < dist[rs[h]]){
        swap(ls[h], rs[h]);
    }
    dist[h] = dist[rs[h]] + 1;
    return h;
}

// (k, v)���һ�����ݣ��ŵ����ϣ�����v����֯С����
void heapAdd(int k, double v){
    key[++cntd] = k;
    val[cntd] = v;
    heap[++cnth] = cntd;
    int cur = cnth, father = cur / 2;
    while(cur > 1 && val[heap[father]] > val[heap[cur]]){
        swap(heap[father], heap[cur]);
        cur = father;
        father = cur / 2;
    }
}

// С�����ϣ��Ѷ�������(k, v)�������������������ڵ��±�ans
// ���ݷ���ֵans��key[ans]�õ�k��val[ans]�õ�v
int heapPop(){
    int ans = heap[1];
    heap[1] = heap[cnth--];
    int cur = 1, l = cur * 2, r = l + 1, best;
    while(l <= cnth){
        best = r <= cnth && val[heap[r]] < val[heap[l]] ? r : l;
        best = val[heap[best]] < val[heap[cur]] ? best : cur;
        if(best == cur) {
            break;
        }
        swap(heap[best], heap[cur]);
        cur = best;
        l = cur * 2;
        r = l + 1;
    }
    return ans;
}

bool heapEmpty(){
    return cnth == 0;
}

// ���ݷ�ͼ��dijkstra�㷨
// �õ��ӽڵ�n���������·����ÿ���ڵ㵽�ڵ�n����̾�����Ϣ
// ���·������ж�����ҵ��κ�һ������
void dijkstra(){
    fill(dis, dis + MAXN, INF);
    dis[n] = 0;
    cntd = cnth = 0;
    heapAdd(n, 0.0);//�൱��heap.push({n,0})
    while(!heapEmpty()){
        int top = heapPop();
        int u = key[top];
        double w = val[top];
        if(!vis[u]){
            vis[u] = true;
            for(int e = headr[u], v; e != 0; e = nextr[e]){
                v = tor[e];
                if(dis[v] > w + weightr[e]){
                    dis[v] = w + weightr[e];
                    path[v] = e;//���ϸ��� ֱ���޷��仯�ľ�����ȷ��
                    heapAdd(v, dis[v]);
                }
            }
        }
    }
}

// �����·���ϵ�ÿ���ڵ㣬�����Լ�����ƫ��
// �ڵ�u����ƫ�� = �ڵ�u�Լ��ķ�������ƫ�� + �ڵ�u�����·���ϵĸ��׵���ƫ��
// �����ص��������ô��������
//��Ϊÿ���½��ýڵ����ƫ��ʱ��  �����ڵ�Ҫ�Ѿ�����
//���Խ�����ƫ����˳�����Ҫ �������ǿ��Ը��ݵ�n�ľ���������
void mergeRoad(){
    cntd = cnth = 0;//�����д��
    for(int i = 1; i <= n; i++){
        heapAdd(i, dis[i]);
    }
    dist[0] = -1;
    while(!heapEmpty()){
        int top = heapPop();
        int u = key[top];
        for(int e = headg[u], v; e != 0; e = nextg[e]){
            // path[u]���Ǳ��ڷ�ͼ�еı�ţ�Ҳ�Ǳ�����ͼ�еı��
            // ��Ϊ����ͼͬ���������ߵ���ͼ��� == �ߵķ�ͼ���
            v = tog[e];
            if(e != path[u]){
                rt[u] = merge(rt[u], init(v, weightg[e] + dis[v] - dis[u]));
                //�½���Ϣ���� to �� Ӱ��
            }
        }
        if(path[u] != 0){
            rt[u] = merge(rt[u], rt[tog[path[u]]]);//���Լ������Ⱥϲ�
        }
    }
}

// ��·�ѵ�1С�ķ�����ʼ�����ҵ���2С����3С...
// ����money�ܹ����Ǽ������У��������еĴ���
int expand(){
    int ans = 0;
    money -= dis[1];
    if(money >= 0){
        //˵�����ٿ��������һ�εĻ���  ��ô����
        ans++;
        cntd = cnth = 0;//��ʼ�����������
        if(rt[1] != 0){
            // ��ʼ�׶�
            // 1�Žڵ���ƫ���ĶѶ����������Ӵ�����С�ķ����ߣ�������߶�
			// Ŀǰ·ͨ������·�ѣ�ͬ������
            heapAdd(rt[1], dis[1] + cost[rt[1]]);
        }
        while(!heapEmpty()){
            int top = heapPop();
            int h = key[top];
            double w = val[top];
            money -= w;
            if(money < 0){
                break;
            }
            ans++;
            // ��ǰѡ��ķ����ߣ�����ƫ���ϵ�������滻
            if(ls[h] != 0){
                heapAdd(ls[h], w - cost[h] + cost[ls[h]]);
            }
            // ��ǰѡ��ķ����ߣ�����ƫ���ϵ��Ҷ����滻
            if(rs[h] != 0){
                heapAdd(rs[h], w - cost[h] + cost[rs[h]]);
            }
            // ��ǰѡ��ķ����ߣ�ָ��ڵ�to[h]����ô��to[h]����ƫ�������һ�����ŵķ�����
            if(to[h] != 0 && rt[to[h]] != 0){
                heapAdd(rt[to[h]], w + cost[rt[to[h]]]);
            }
        }
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m >> money;
    int u, v;
    double w;
    for(int i = 1; i <= m; i++){
        cin >> u >> v >> w;
        // ��Ŀ˵�ˣ�һ������ڵ�n����������ֹͣ
        // ���Դӽڵ�n�����ıߣ�һ�ɺ���
        if(u != n){
            addEdgeG(u, v, w);//����ͼ
            addEdgeR(v, u, w);//����ͼ
        }
    }
    dijkstra();//��ͼ����dj�㷨
    mergeRoad();
    int ans = expand();
    cout << ans << endl;
    return 0;
}
