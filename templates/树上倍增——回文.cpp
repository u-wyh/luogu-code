// ����������ڵ���·���Ƿ��ǻ���
// һ��������n���ڵ㣬���1~n
// ��������Ϊn������parent, parent[i]��ʾ�ڵ�i�ĸ��ڵ���
// ��������Ϊn������s, s[i]��ʾ�ڵ�i����ʲô�ַ�
// �ӽڵ�a���ڵ�b�����ڵ����ٵ�·������a��b��·��
// һ����m����ѯ��ÿ����ѯ(a,b)��a��b��·���ַ����Ƿ��ǻ���
// �ǻ��Ĵ�ӡ"YES"�����ǻ��Ĵ�ӡ"NO"
// 1 <= n <= 10^5
// 1 <= m <= 10^5
// parent[1] = 0������������ͷ�ڵ�һ����1�Žڵ�
// ÿ���ڵ��ϵ��ַ�һ����Сд��ĸa~z
// �������� : https://ac.nowcoder.com/acm/contest/78807/G
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ֱ��ͨ��

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int LIMIT = 17;
const long K = 499;

int power;
int s[MAXN];
int head[MAXN];
int to[MAXN << 1];
int Next[MAXN << 1];
int cnt=1;
int deep[MAXN];
int jump[MAXN][LIMIT];
// kpow[i] = k��i�η�
long kpow[MAXN];
long stup[MAXN][LIMIT];
long stdown[MAXN][LIMIT];

void build(int n) {
    power = log2(n);
    kpow[0] = 1;
    for (int i = 1; i <= n; i++) {
        kpow[i] = kpow[i - 1] * K;
    }
}

int lca(int a, int b) {
    if (deep[a] < deep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    for (int p = power; p >= 0; p--) {
        if (deep[jump[a][p]] >= deep[b]) {
            a = jump[a][p];
        }
    }
    if (a == b) {
        return a;
    }
    for (int p = power; p >= 0; p--) {
        if (jump[a][p] != jump[b][p]) {
            a = jump[a][p];
            b = jump[b][p];
        }
    }
    return jump[a][0];
}

long ha(int from, int lca, int to) {
    // up������hashֵ
    long up = s[from];
    for (int p = power; p >= 0; p--) {
        if (deep[jump[from][p]] >= deep[lca]) {
            up = up * kpow[1 << p] + stup[from][p];
            from = jump[from][p];
        }
    }
    if (to == lca) {
        return up;
    }
    // down������hashֵ
    long down = s[to];
    // height��Ŀǰ���µ��ܸ߶�
    int height = 1;
    for (int p = power; p >= 0; p--) {
        if (deep[jump[to][p]] > deep[lca]) {
            down = stdown[to][p] * kpow[height] + down;
            height += 1 << p;
            to = jump[to][p];
        }
    }
    return up * kpow[height] + down;
}


void dfs(int u, int f) {
    deep[u] = deep[f] + 1;
    jump[u][0] = f;
    stup[u][0] = stdown[u][0] = s[f];
    for (int p = 1, v; p <= power; p++) {
        v = jump[u][p - 1];
        jump[u][p] = jump[v][p - 1];
        stup[u][p] = stup[u][p - 1] * kpow[1 << (p - 1)] + stup[v][p - 1];
        stdown[u][p] = stdown[v][p - 1] * kpow[1 << (p - 1)] + stdown[u][p - 1];
    }
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            dfs(v, u);
        }
    }
}

bool isPalindrome(int a, int b) {
    int Lca = lca(a, b);
    long hash1 = ha(a, Lca, b);
    long hash2 = ha(b, Lca, a);
    return hash1 == hash2;
}

void addEdge(int u, int v) {
    Next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

int main()
{
    int n,m;
    cin>>n;
    build(n);
    for(int i=1;i<=n;i++){
        char ch;
        cin>>ch;
        s[i]=ch-'a'+1;
    }
    for (int u = 1, v; u <= n; u++) {
        cin>>v;
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs(1, 0);
    cin>>m;
    for (int i = 1, a, b; i <= m; i++) {
        cin>>a>>b;
        if(isPalindrome(a, b))
            cout<<"YES\n" ;
        else
            cout<< "NO\n";
    }
    return 0;
}
