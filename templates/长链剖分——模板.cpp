// ����k�����ȣ�C++��
// һ����n���ڵ㣬���1~n������һ������Ϊn������arr����ʾ������ϵ
// ���arr[i] = j����ʾi�Žڵ�ĸ��ڵ���j�����arr[i] == 0����ʾi�Žڵ�����ͷ
// һ����m����ѯ��ÿ����ѯ x k : ��ӡx������k�������Ƚڵ���
// ��ĿҪ��Ԥ�����ʱ�临�Ӷ�O(n * log n)������ÿ����ѯ��ʱ�临�Ӷ�O(1)
// ��ĿҪ��ǿ�����ߣ����밴˳����ÿ����ѯ����εõ�ÿ����ѯ����Σ���򿪲������Ӳ鿴
// 1 <= n <= 5 * 10^5
// 1 <= m <= 5 * 10^6
// �������� : https://www.luogu.com.cn/problem/P5903
// ����ʵ����C++�İ汾��C++�汾��java�汾�߼���ȫһ��
// �ύ���´��룬����ͨ�����в�������
#include <bits/stdc++.h>
#define ui unsigned int
using namespace std;
const int MAXN = 500001;
const int MAXH = 20;

int n, m;
ui s;//��ĿҪ������������
int root;

// ��ʽǰ���ǣ�ע��������ͼ�����Աߵ���������Ҫ����
int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg = 0;

// ������ + �����ʷ�
int stjump[MAXN][MAXH];//������
int dep[MAXN];//��ȱ�
int len[MAXN];//���ȱ�
int son[MAXN];//������
int top[MAXN];
int dfn[MAXN];
int cntd = 0;

// ��ѯ����Ҫ
int high[MAXN];//high[i]��¼����i�Ķ��������λ��Ӧ�������Ƕ���  ��˼��i>=2^high[i]&&i<2^(high[i]+1)
int up[MAXN];//��¼�ڵ�i������1 2 3 �����Ǹ��ڵ�  ֻ�г�����ͷ���ſ�����
//����ֻ������Ӵ�С�ĸ���   ��ʹ�����߻����ڸ�Զ��  Ҳ������
int down[MAXN];//���������һ��  ��¼���������߼���  ÿ���ڵ�ֻ���Լ������Ӵ�С������λ��

// ��Ŀ�涨��εõ��������ݵĺ���  ǿ������Ҫ��
ui get(ui x) {
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    s = x;
    return x;
}

//����u����ڵ�������i�� �ﵽv�ڵ�  uһ����ĳ��������ͷ���
void setUp(int u, int i, int v) {
    up[dfn[u] + i] = v;
}

//��ѯu�ڵ�������i�������Ǹ��ڵ�  uһ����ĳ��������ͷ���
int getUp(int u, int i) {
    return up[dfn[u] + i];
}

//����u����ڵ�������i�� �ﵽv�ڵ�  uһ����ĳ��������ͷ���
void setDown(int u, int i, int v) {
    down[dfn[u] + i] = v;
}

//��ѯu�ڵ�������i�������Ǹ��ڵ�  uһ����ĳ��������ͷ���
int getDown(int u, int i) {
    return down[dfn[u] + i];
}

void addEdge(int u, int v) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

void dfs1(int u, int f) {
    stjump[u][0] = f;//û��fa���� ��Ϊ���������ֱ�Ӳ�ѯ
    for (int p = 1; p < MAXH; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    dep[u] = dep[f] + 1;
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != f) {
            dfs1(v, u);
        }
    }
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != f) {
            if (son[u] == 0 || len[son[u]] < len[v]) {
                son[u] = v;
            }
        }
    }
    len[u] = len[son[u]] + 1;//ÿ���ڵ�Ĵ�С���Լ������Ӽ�һ
}

void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++cntd;
    if (son[u] == 0) return;
    dfs2(son[u], t);
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != stjump[u][0] && v != son[u]) {
            dfs2(v, v);
        }
    }
}

void prepare() {
    dfs1(root, 0);
    dfs2(root, root);
    high[0] = -1;
    for (int i = 1; i <= n; i++) {
        high[i] = high[i / 2] + 1;
    }
    for (int u = 1; u <= n; u++) {
        if (top[u] == u) {
            //�������ڵ��ǳ�����ͷ��� ��ô����up��down����
            for (int i = 0, a = u, b = u; i < len[u]; i++, a = stjump[a][0], b = son[b]) {
                //ֻ������len��λ��
                setUp(u, i, a);
                setDown(u, i, b);
            }
        }
    }
}

//��ѯx�ڵ�������k���ܵ�����
int query(int x, int k) {
    if (k == 0) {
        //�����0��  ��ôֱ�Ӿ�������ڵ�
        return x;
    }
    if (k == (1 << high[k])) {
        //������k������2��ĳ�η�  ��ôֱ��st���ѯ����
        return stjump[x][high[k]];
    }
    //����  �����Ƚ������λ��1��st���ѯ  �ҵ�һ���м�ڵ�
    x = stjump[x][high[k]];
    //Ȼ��k��ȥ�������λ
    k -= (1 << high[k]);
    //kʣ�µ��ⲿ�־�ͨ���������м�ڵ������ͷ����ѯ
    k -= dep[x] - dep[top[x]];
    x = top[x];
    return (k >= 0) ? getUp(x, k) : getDown(x, -k);
    //���kС��0  ��ô˵������������top[x]  ��ô������һ��ͺ�
    //���k����0  ��ô˵��top[x]Ҳ���� ��ô������һ��ͺ�
    //���ҿ��Կ϶�����  top[x]һ�����Խ��
    //��Ϊ��Ȼ��ʼ�ڵ�����k�����λ�ľ����������м�ڵ�   ��������k/2
    //��ô˵������м�ڵ��ͷ�����������Ҫ����k/2
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s;
    for (int i = 1, father; i <= n; i++) {
        cin >> father;
        if (father == 0) {
            root = i;
        } else {
            addEdge(father, i);
        }
    }
    prepare();
    long long ans = 0;
    for (int i = 1, x, k, lastAns = 0; i <= m; i++) {
        x = (get(s) ^ lastAns) % n + 1;
        k = (get(s) ^ lastAns) % dep[x];
        lastAns = query(x, k);
        ans ^= (long long) i * lastAns;
    }
    cout << ans << '\n';
    return 0;
}