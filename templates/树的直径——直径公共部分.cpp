// ����ֱ���Ĺ�������(�ݹ��)
// ����һ��������Ȩ��Ϊ��
// ��ӡֱ�����ȡ�����ֱ���Ĺ��������м�����
// �������� : https://www.luogu.com.cn/problem/P3304
// �ύ���µ�code���ύʱ��������ĳ�"Main"
// C++��ôд��ͨ����java����Ϊ�ݹ����̫�����ջ
// java��ͨ����д���ο����ڿ�Code02_DiameterAndCommonEdges2�ļ�
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200005;

int n;

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
long diameter;
// dist[i] : �ӹ涨��ͷ�ڵ�������ߵ�i�ľ���
long dist[MAXN];
// last[i] : �ӹ涨��ͷ�ڵ������i�ڵ����һ���ڵ�
int last[MAXN];
//�Ƿ���ֱ���ϵĵ�(ֻ��һ��ֱ���ϸ�Ϊtrue����)
bool diameterPath[MAXN];
//��������
int commonEdges;

void dfs(int u,int f,long w){
    last[u]=f;
    dist[u]=dist[f]+w;
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            dfs(to[i],u,weight[i]);
        }
    }
}

//���ε���dfs   �ҵ�ֱ����С
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

//��·���ϵĵ㲻��ֱ���ϵĵ���Ե�����Զ����
long maxDistanceExceptDiameter(int u, int f, long c) {
    long ans = c;
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (!diameterPath[v] && v != f) {
            ans = max(ans, maxDistanceExceptDiameter(v, u, c + weight[e]));
        }
    }
    return ans;
}

//�������ֵ����ұߵ�� maxDistanceExceptDiameter  һ�����ڵ�ֱ��end�ľ���  ��end��ʼ��  ���һ�����������Ĳ���
//�������ֵ�����ߵ�� maxDistanceExceptDiameter  һ�����ڵ�ֱ��start�ľ���  ��end��ʼ��  ��һ�����������Ĳ���
//��������ߵ�һ�����ұߵ����
void compute() {
    road();//�ҵ�ֱ���������յ�
    for (int i = en; i != 0; i = last[i]) {
        diameterPath[i] = true;
        //��ʾ������һ��ֱ���ϵĵ�
    }
    int l = start;
    int r = en;
    long maxDist;
    for (int i = last[en]; i != start; i = last[i]) {
        maxDist = maxDistanceExceptDiameter(i, 0, 0);
        if (maxDist == diameter - dist[i]) {
            //��ʾ����������ֱ���ϵĵ����͵�����ľ���һ��
            //˵��������Ƕ���ֱ���Ĺ�����
            r = i;
        }
        //���һ�������������Ҷ˵�
        if (maxDist == dist[i] && l == start) {
            l = i;
        }
        //��һ�����������ĵ�  �Ժ�Ĳ������l==start
    }
    if (l == r) {
        commonEdges = 0;
    } else {
        commonEdges = 1;
        for (int i = last[r]; i != l; i = last[i]) {
            commonEdges++;
        }
    }
}

int main()
{
    cin>>n;
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
    //��ͼ
    compute();
    cout<<diameter<<endl<<commonEdges;
    return 0;
}

