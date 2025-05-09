// �ۻ����ÿ���˻ؼ������ʱ
// ����һ��n�����������Ȩ�����߹�����Ҫ���ѵ�ʱ��
// ����k���˷ֱ������ϵ���Щ�ڵ�
// ��k����ѡ����һ���ۻ�㣬���е��˶�ȥ���ۻ����оۻ�
// �ۻ�����������˶�����һ�����������ÿ�����ͻؼ�
// �������һ���˿ͣ�������Ҫ�ص��ۻ��
// ����ۻ����i�����ʴӾۻ�ص����ֱ�������һ���˻ؼң������ʱ����
// i = 1 ~ n����ӡ���еĴ�
// �������� : https://www.luogu.com.cn/problem/P6419
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ����������

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;

int n,k;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;
// people[i]: i�ڲ����ж��ٳ˿�Ҫ��
int people[MAXN];
// incost[i]: i�ڲ�����i�����������г˿ͻص�i�����ٴ���
long incost[MAXN];
// inner1[i]: i�ڲ�����i�����ͳ˿͵����
long inner1[MAXN];
// inner2[i]: i�ڲ�����i�����ͳ˿͵Ĵγ���
long inner2[MAXN];
// ע�� : inner1[i]��inner2[i]�����������һ��Ҫ����i�Ĳ�ͬ����
// choose[i]: �ͳ˿͵��������i���ĸ�����
int choose[MAXN];
// outcost[i]: i�ⲿ����i�����������г˿ͻص�i�����ٴ���
long outcost[MAXN];
// outer[i]: i�ⲿ����i�����ͳ˿͵����
long outer[MAXN];

void dfs1(int u, int f) {
    for (int e = head[u], v, w; e != 0; e = Next[e]) {
        v = to[e];
        w = weight[e];
        if (v != f) {
            dfs1(v, u);
            people[u] += people[v];
            if (people[v] > 0) {
                //ʵ������һ����֦����
                incost[u] += incost[v] + (long) w * 2;
                if (inner1[u] < inner1[v] + w) {
                    choose[u] = v;
                    inner2[u] = inner1[u];
                    inner1[u] = inner1[v] + w;
                } else if (inner2[u] < inner1[v] + w) {
                    inner2[u] = inner1[v] + w;
                }
            }
        }
    }
}

void dfs2(int u, int f) {
    for (int e = head[u], v, w; e != 0; e = Next[e]) {
        v = to[e];
        w = weight[e];
        if (v != f) {
            if (k - people[v] > 0) {
                if (people[v] == 0) {
                    outcost[v] = outcost[u] + incost[u] + (long) w * 2;
                } else {
                    outcost[v] = outcost[u] + incost[u] - incost[v];
                }
                if (v != choose[u]) {
                    outer[v] = max(outer[u], inner1[u]) + w;
                } else {
                    outer[v] = max(outer[u], inner2[u]) + w;
                }
            }
            dfs2(v, u);
        }
    }
}

int main()
{
    cin>>n>>k;
    for(int i=1,u,v,w;i<n;i++){
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
    for(int i=1,u;i<=k;i++){
        cin>>u;
        people[u]++;
    }
    dfs1(1,0);
    dfs2(1,0);
    for (int i = 1; i <= n; i++) {
        cout<<(incost[i] + outcost[i] - max(inner1[i], outer[i]))<<endl;
    }
    return 0;
}

