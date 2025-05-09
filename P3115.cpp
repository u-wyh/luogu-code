#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005, MAXM = 4950005; //��������������
const long long INF = 4557430888798830399; //��ʼ��һ������ֵ������Ҫ��long long

int st, fi, n, idx; //��㣬�յ㣬����������ߵ����� 
long long dis[MAXN][2], head[MAXN]; //dis[i][0]Ϊ��㵽��i���ٷ��ã�dis[i][1]Ϊ���ٷ����µ����·�� 
struct Edge{int nxt, to, w, c;}edge[MAXM]; //��һ���ߣ�����ĵ㣬���ã�·������ 
struct Node{long long x, w;}; //��ţ����ٻ��� 
bool operator < (const Node &a, const Node &b) {return a.w > b.w;} //��С�������� 
bool vis[MAXN];
priority_queue <Node> q;

void add (int from, int to, int w, int c) //���� 
{
    edge[++idx].nxt = head[from];edge[idx].to = to;edge[idx].w = w;edge[idx].c = c;
    head[from] = idx;
}

void init ()
{
    memset (head, -1, sizeof (head));
    memset (dis, 0x3f, sizeof (dis));
    scanf ("%d%d%d", &st, &fi, &n);
    for (int i = 1; i <= n; i++)
    {
        int k, w;
        long long v[105];
        scanf ("%d%d", &w, &k);
        for (int j = 1; j <= k; j++)    scanf ("%lld", &v[j]);
        //��ǰ���󽨱� 
        for (int x = 1; x <= k; x++)
        for (int y = x + 1; y <= k; y++)    add (v[x], v[y], w, y - x); //��һ������v[x]��v[y]����Ϊw·����Ϊy - x�ı� 
    }
}

//���Ż�dijkstra
void dijkstar (int s)
{
    dis[s][0] = dis[s][1] = 0;
    q.push (Node {s, 0});
    while (!q.empty ())
    {
        Node cur = q.top ();
        q.pop ();
        if (vis[cur.x]) continue;
        vis[cur.x] = 1;
        for (int i = head[cur.x]; i != -1; i = edge[i].nxt)
        {
            int to = edge[i].to;
            if (dis[to][0] > dis[cur.x][0] + edge[i].w) //���и�С�Ļ��ѣ������ 
            {
                dis[to][0] = dis[cur.x][0] + edge[i].w;
                dis[to][1] = dis[cur.x][1] + edge[i].c;
                if (vis[to])    continue;
                q.push (Node {to, dis[to][0]}); //��������źͻ��� 
            }
            if (dis[to][0] == dis[cur.x][0] + edge[i].w) //�ǵ����з��õ��ڵ���� 
            {
                dis[to][1] = min (dis[to][1], dis[cur.x][1] + edge[i].c);//���õ���ȡ·������С�� 
                if (vis[to])    continue;
                q.push (Node {to, dis[to][0]});
            }
        }
    }
}

void output ()
{
    if (dis[fi][0] == INF)  printf ("-1 -1"); //���ܵ��� 
    else                    printf ("%lld %lld", dis[fi][0], dis[fi][1]);
}

int main ()
{
    init ();        //���� 
    dijkstar (st);  //���· 
    output ();      //��� 
    return 0;
}