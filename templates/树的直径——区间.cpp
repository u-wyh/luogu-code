// ����(�ݹ��)
// һ��n���ڵ㣬���1~n����n-1�������ӳ�һ������ÿ�������зǸ�Ȩֵ
// ����һ���Ǹ�����s����ʾ����������ѡ��һ�����Ȳ�����s��·��
// Ȼ��������·���ĵ��Ͻ�������վ��ÿ���������ȥ������·���ϵ��κ�����վ
// Ŀ�꣺������Զ�ľ����ߵ�����վ�ľ���ҲҪ������
// ������Զ�����ߵ�����վ����̾���
// �������� : https://www.luogu.com.cn/problem/P2491
// �ύ���µ�code���ύʱ��������ĳ�"Main"
// C++��ôд��ͨ����java����Ϊ�ݹ����̫�����ջ
// java��ͨ����д���ο����ڿ�Code05_FireFighting2�ļ�

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 300005;

int n,s;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;
// ֱ���Ŀ�ʼ��
int start;
// ֱ���Ľ�����
int en;
// ֱ������
int diameter;
// dist[i] : �ӹ涨��ͷ�ڵ�������ߵ�i�ľ���
int dist[MAXN];
// last[i] : �ӹ涨��ͷ�ڵ������i�ڵ����һ���ڵ�
int last[MAXN];
bool diameterPath[MAXN];
int maxDist[MAXN];
int pred[MAXN];
// pred[i] : i�ڵ���ֱ���ϣ���ǰһ����֮��ľ��룬��start����

void dfs(int u,int f,int w){
    last[u]=f;
    dist[u]=dist[f]+w;
    pred[u]=w;
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            dfs(to[i],u,weight[i]);
        }
    }
}

int maxDistanceExceptDiameter(int u, int f, int c) {
    int ans = c;
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (!diameterPath[v] && v != f) {
            ans = max(ans, maxDistanceExceptDiameter(v, u, c + weight[e]));
        }
    }
    return ans;
}
//��·���ϵĵ㲻��ֱ���ϵĵ���Ե�����Զ����

void distance() {
    for (int i = en; i != 0; i = last[i]) {
        diameterPath[i] = true;
    }
    for (int i = en; i != 0; i = last[i]) {
        maxDist[i] = maxDistanceExceptDiameter(i, 0, 0);
    }
}

void road() {
    dfs(1, 0, 0);
    //�������������  һ�㶼��1
    start = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[start]) {
            start = i;
        }
    }
    //ѡ�������������ĵ�  ��Ϊͷ���
    dfs(start, 0, 0);
    en = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[en]) {
            en = i;
        }
    }
    diameter = dist[en];
}
//���ε���dfs

int Queue[MAXN];

int compute() {
    int suml = 0, sumr = 0;
    // ��h��t��ʾ�������е�ͷ��β
    int h = 0, t = 0;
    int ans = INT_MAX;
    // ���ڷ�Χ[l,r)������ҿ���ֱ���ϵĴ���[l...r-1]
    // l�Ǵ�����˵㣬r�Ǵ����Ҷ˵������һ����
    // ����ͼ���Ǵ�start��end��ʵ���Ǵ�end��start��˼·û������
    for (int l = en, r = en; l != 0; l = last[l]) {
        while (r != 0 && sumr - suml + pred[r] <= s) {
            while (h < t && maxDist[Queue[t - 1]] <= maxDist[r]) {
                t--;
            }
            sumr += pred[r];
            Queue[t++] = r;
            r = last[r];
        }
        ans = min(ans, max(max(suml, maxDist[Queue[h]]), diameter - sumr));
        if (Queue[h] == l) {
            h++;
        }
        suml += pred[l];
    }
    return ans;
}

int main()
{
    cin>>n>>s;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;

        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        weight[cnt]=w;
        head[v]=cnt++;
    }
    road();
    distance();
    cout<<compute();
    return 0;
}
