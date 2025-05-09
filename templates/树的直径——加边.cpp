// Ѳ��
// һ��n���ڵ㣬���1~n���ṹ��һ������ÿ���߶���˫���
// �������1�ŵ㣬����ÿ���1�ŵ������һ��Ҫ�߹��������еıߣ����ص�1�ŵ�
// ����Ϊ�˼��پ����ߵ�������������½�k���ߣ���������������ֱ������
// ����ÿ�쾯�����뾭���½��ĵ�·����һ��
// �������ѵ��½���·�ķ���������Ѳ���߱���������Сֵ
// �������� : https://www.luogu.com.cn/problem/P3629
// 1 <= n <= 10^5
// 1 <= k <= 2
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ����������
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int n,k;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
// ֱ���Ŀ�ʼ��
int start;
// ֱ���Ľ�����
int en;
// ֱ������
int diameter1,diameter2;
// dist[i] : �ӹ涨��ͷ�ڵ�������ߵ�i�ľ���
int dist[MAXN];
// last[i] : �ӹ涨��ͷ�ڵ������i�ڵ����һ���ڵ�
int last[MAXN];
bool diameterPath[MAXN];

void dfs(int u,int f,int w){
    last[u]=f;
    dist[u]=dist[f]+w;
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            dfs(to[i],u,1);
        }
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
    diameter1 = dist[en];
}
//���ε���dfs

void dp(int u, int f) {
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            dp(v, u);
        }
    }
    for (int e = head[u], v, w; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            w = diameterPath[u] && diameterPath[v] ? -1 : 1;
            //����������ڵ㶼��true  ��ô����·��Ȩֵ����-1
            diameter2 = max(diameter2, dist[u] + dist[v] + w);
            dist[u] = max(dist[u], dist[v] + w);
        }
    }
}

int main()
{
    cin>>n>>k;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;
    }
    road();
    //�������ֻ�����diameter1�Ĵ�С����
    if(k==1){
        //ֻ��һ���ߵ����
        //ֻ���Լ����ֱ���ϵĽڵ����
        cout<<2*(n-1)-diameter1+1;
    }else{
        for(int i=en;i!=0;i=last[i]){
            diameterPath[i]=true;
        }
        //��ֱ���ϵĽڵ���Ϊtrue
        for(int i=1;i<=n;i++){
            dist[i]=0;
        }
        //ȫ����ɳ�ʼ��
        dp(1,0);
        //�õ�diameter2�Ĵ�С  ����diameter2�ǳ�ȥ��ֱ���Ĺ����ߵĽ�����
        cout<<2*(n-1)-diameter1-diameter2+2;
    }
    return 0;
}
