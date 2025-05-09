// ţȺ�ۼ�(�ݹ��)
// һ����n���ڵ㣬���1~n��ÿ������ţ������
// һ����n-1���߰����е���ͨ�����γ�һ������ÿ������Ȩֵ
// ������е�ţ�����һ�㣬ϣ���߹����ܾ�����С
// �����ܾ�����С�Ƕ���
// �������ĵ����ʣ�
// ���ϵı�Ȩ�����>=0�����ܱ�Ȩ��ô�ֲ������нڵ㶼�������ĵ��ܾ������С
// �������� : https://www.luogu.com.cn/problem/P2986
// �ύ���µ�code���ύʱ��������ĳ�"Main"
// C++��ôд��ͨ����java����Ϊ�ݹ����̫�����ջ
// java��ͨ����д���ο����ڿ�Code03_GreatCowGathering2�ļ�
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;
int cow[MAXN];
int n,cowSum=0;
int best=INT_MAX, center;
// size[i] : ��1�Žڵ㿪ʼdfs�Ĺ����У���iΪͷ��������ţ������
int sz[MAXN];
// path[i] : �����Ľڵ㿪ʼdfs�Ĺ����У������ĵ���i�ڵ㣬�����Ƕ���
int path[MAXN];

void setPath(int u, int f) {
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            path[v] = path[u] + weight[e];
            setPath(v, u);
        }
    }
}
//ȷ��pathֵ

void findCenter(int u, int f) {
    sz[u] = cow[u];
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            findCenter(v, u);
        }
    }
    // ���´����Ǳ�����ɺ�����ͳ�ƹ���
    // ���д����֮ǰ���߼���һ���ģ�ΪʲôҪ��д��
    // Ϊ�˺����ĵ����淽��
    int maxsub = 0;
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            sz[u] += sz[v];
            maxsub = max(maxsub, sz[v]);
        }
    }
    maxsub = max(maxsub, cowSum - sz[u]);
    if (maxsub < best) {
        best = maxsub;
        center = u;
    }
}
//Ѱ�����Ĳ���

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>cow[i];
        cowSum+=cow[i];
    }
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
    findCenter(1,0);
    //cout<<center<<endl;
    path[center] = 0;
    setPath(center, 0);
    long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += (long) cow[i] * path[i];
    }
    cout<< ans;
    return 0;
}
//�б�Ȩ�͵�Ȩ��ͼ������   ʵ���ϱ�Ȩû��ʲô����
//ֻ�е�Ȩ������Ӱ��  ������sz������
